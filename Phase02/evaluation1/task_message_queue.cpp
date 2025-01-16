#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <cstring>

struct Message {
    long messageType;
    char messageText[100];
};

void calculateSum(const std::vector<int>& dosages, int msgid) {
    int sum = 0;
    for (int dosage : dosages) {
        sum += dosage;
    }

    Message msg;
    msg.messageType = 1;
    snprintf(msg.messageText, sizeof(msg.messageText), "Sum: %d", sum);

    msgsnd(msgid, &msg, sizeof(msg.messageText), 0);
}

void calculateMin(const std::vector<int>& dosages, int msgid) {
    int min = dosages[0];
    for (size_t i = 0; i < dosages.size() / 2; ++i) {
        if (dosages[i] < min) {
            min = dosages[i];
        }
    }

    Message msg;
    msg.messageType = 2;
    snprintf(msg.messageText, sizeof(msg.messageText), "Min: %d", min);

    msgsnd(msgid, &msg, sizeof(msg.messageText), 0);
}

void calculateMax(const std::vector<int>& dosages, int msgid) {
    int max = dosages[dosages.size() / 2];
    for (size_t i = dosages.size() / 2; i < dosages.size(); ++i) {
        if (dosages[i] > max) {
            max = dosages[i];
        }
    }

    Message msg;
    msg.messageType = 3;
    snprintf(msg.messageText, sizeof(msg.messageText), "Max: %d", max);

    msgsnd(msgid, &msg, sizeof(msg.messageText), 0);
}

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        std::cerr << "Error creating message queue" << std::endl;
        return 1;
    }

    std::vector<int> dosages = {3, 2, 7, 4, 5};

    if (fork() == 0) {
        calculateSum(dosages, msgid);
        exit(0);
    }

    if (fork() == 0) {
        calculateMin(dosages, msgid);
        exit(0);
    }

    if (fork() == 0) {
        calculateMax(dosages, msgid);
        exit(0);
    }

    for (int i = 0; i < 3; ++i) {
        Message msg;
        msgrcv(msgid, &msg, sizeof(msg.messageText), 0, 0);
        std::cout << msg.messageText << std::endl;
    }

    msgctl(msgid, IPC_RMID, nullptr);
    return 0;
}
