//two processing - concurrent programming
//IPC (inter process communication) via shared mem
#include<iostream>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<cstring>

#define SHM_KEY 1234

void client(int& shmid) { //child 1
    char* text = (char*)shmat(shmid, nullptr, 0);   
    std::cout << "shared mem:" << text << std::endl;
    shmdt(text);
}

void server(int& shmid) { //child 2
    char* text = (char*)shmat(shmid, nullptr, 0);
    strcpy(text, "hello");
    std::cout << "Message is written in shared memory" << std::endl;
    shmdt(text);
}

int main() { 
    int shmid = shmget(SHM_KEY, sizeof(char)*1024 , 0666 | IPC_CREAT);   
    
    pid_t pid = -1;
    {   //child 1
        pid = fork();
        if(0 == pid) {            
            server(shmid);   
            sleep(3);   
            shmctl(shmid, IPC_RMID, nullptr);
            return 0;
        }
    }

    {   //child 2
        pid = fork();
        if(0 == pid) {
            sleep(1);
            client(shmid);
            return 0;
        }
    }

    // no parent process
    wait(nullptr);
    
    return 0;
}
