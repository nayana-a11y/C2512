
//two processing - concurrent programming
//IPC (inter process communication) via msg queue
#include<iostream>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<cstring>

#define MSG_KEY 1234
struct msgbuf_t {
    long mtype;
    char mtext[6];
};

void client(int& msgid) { //child 1
    msgbuf_t message;
    if(msgrcv(msgid, &message, sizeof(message.mtext), 0, 0) == -1) {
        perror("msg receive error");
        exit(1);
    }
    std::cout << "Received text:" << message.mtext << std::endl;
}

void server(int& msgid) { //child 2
    msgbuf_t message;
    //message.mtype = 1;
    strcpy(message.mtext, "hello"); //5
    if(msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }
    std::cout << "message sent successfully." << std::endl;
}
int main() { 
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);   
    
    pid_t pid = -1;
    {   //child 1
        pid = fork();
        if(0 == pid) {            
            server(msgid);   
            sleep(3);         
            msgctl(msgid, IPC_RMID, nullptr);
            return 0;
        }
    }

    {   //child 2
        pid = fork();
        if(0 == pid) {
            sleep(1);
            client(msgid);
            return 0;
        }
    }

    // no parent process
    wait(nullptr);
    return 0;
}
