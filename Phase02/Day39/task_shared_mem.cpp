#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <cstring>
#include <string>

using namespace std;

class Prescription {
private:
    string Prescription_id;
    int Dosage;
public:
    Prescription(string p_id, int p_dosage) : Prescription_id(p_id), Dosage(p_dosage) {}

    int getDosage() 
    { 
        return Dosage; 
    }
};

void client(int* shared_mem, int* shared_mem_size, int* shared_mem_sum) {
    vector<Prescription> prescriptions = {
        Prescription("01", 4), 
        Prescription("02", 5), 
        Prescription("03", 6), 
        Prescription("04", 7), 
        Prescription("05", 1)
    };

    int size = prescriptions.size();
    int* dosages = shared_mem;

    for (int i = 0; i < size; i++) {
        dosages[i] = prescriptions[i].getDosage();
    }

    *shared_mem_size = size;

    cout << "Client sending dosages: ";
    for (int i = 0; i < size; ++i) {
        cout << dosages[i] << " ";
    }
    cout << endl;

    while (*shared_mem_sum == -1);

    cout << "Client received sum from server: " << *shared_mem_sum << endl;
}

void server(int* shared_mem, int* shared_mem_size, int* shared_mem_sum) {
    while (*shared_mem_size == 0);

    int size = *shared_mem_size;
    int* dosages = shared_mem;
    int sum = 0;

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << dosages[i] << " ";
        sum += dosages[i];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    *shared_mem_sum = sum;
}

int main() {
    const int SHARED_MEM_KEY = 1234;
    const int SHARED_MEM_SIZE = 4096;

    int shmid = shmget(SHARED_MEM_KEY, SHARED_MEM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("Shared memory creation failed");
        return 1;
    }

    void* mem = shmat(shmid, nullptr, 0);
    if (mem == (void*)-1) {
        perror("Shared memory attachment failed");
        return 1;
    }

    int* shared_mem = static_cast<int*>(mem);
    int* shared_mem_size = shared_mem + 100; // Pointer for storing the size of the array
    int* shared_mem_sum = shared_mem + 101; // Pointer for storing the sum

    *shared_mem_size = 0;
    *shared_mem_sum = -1;

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  
        client(shared_mem, shared_mem_size, shared_mem_sum);
        exit(0);
    } else {  /
        server(shared_mem, shared_mem_size, shared_mem_sum);
        wait(nullptr);

        shmdt(mem);
        shmctl(shmid, IPC_RMID, nullptr);
    }

    return 0;
}
