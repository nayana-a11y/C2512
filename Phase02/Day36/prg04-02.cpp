//two processing - concurrent programming
//IPC (inter process communication) via shm
// N salaries (client) + N revised salaries(server)
// salary of double=8 x N=10 = 80 + 80 + 4 = 160 + 4 (after pad= 168)
#include<iostream>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<cstring>

#define MAX_SIZE 200

#define SHM_KEY 1234
struct Payroll { 
    double salaries[MAX_SIZE];
    double revisedSalaries[MAX_SIZE];
    int size;
    int status; // 0-not read, 1-read, 2-processed, 3-used processed salaries
};

void client(int& shmid) { //child 1
    Payroll* payroll = (Payroll*)shmat(shmid, nullptr, 0);   
    std::cout << "Number of salaries:"; std::cin >> payroll->size;
    std::cout << "Enter salaries one by one:" << std::endl;
    
    for(int I = 0; I < payroll->size; I++) {
        std::cin >> payroll->salaries[I];
    }
    payroll->status = 1;
    while(2 != payroll->status) { } // wait till payroll is processed

    std::cout << "Processed Salaries" << std::endl;
    for(int I = 0; I < payroll->size; I++) {
        std::cout << payroll->salaries[I] << " is hiked as " 
                  << payroll->revisedSalaries[I] << std::endl;
    }
    payroll->status = 3;
    shmdt(payroll);
}

void server(int& shmid) { //child 2
    Payroll* payroll = (Payroll*)shmat(shmid, nullptr, 0); 
    for(int I = 0; I < payroll->size; I++) {
        payroll->revisedSalaries[I] = payroll->salaries[I] * 1.1;
    }
    payroll->status = 2;
    shmdt(payroll);
}

int main() {    
    int shmid = shmget(SHM_KEY, sizeof(Payroll), 0666 | IPC_CREAT);   
    Payroll* payroll = (Payroll*)shmat(shmid, nullptr, 0); 
    payroll->status = 0;
    pid_t pid = -1;
    {   //child 1
        pid = fork();
        if(0 == pid) {            
            client(shmid);               
            return 0;
        }
    }

    {   //child 2
        pid = fork();
        if(0 == pid) {
            while(1 != payroll->status) { } // wait till salaries read
            server(shmid);
            while(3 != payroll->status) { } // wait till processed salaries read   
            shmctl(shmid, IPC_RMID, nullptr);
            return 0;
        }
    }

    // no parent process
    wait(nullptr);
    
    return 0;
}
