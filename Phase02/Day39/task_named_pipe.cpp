#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <string>

using namespace std;

class Prescription {
private:
    string Prescription_id;
    int Dosage;
public:
    Prescription(string p_id, int p_dosage) : Prescription_id(p_id), Dosage(p_dosage) {}

    int getDosage() { 
        return Dosage; 
    }
};

void client(const char* write_fifo, const char* read_fifo) {
    vector<Prescription> prescriptions = {
        Prescription("01", 4), 
        Prescription("02", 5), 
        Prescription("03", 6), 
        Prescription("04", 7), 
        Prescription("05", 1)
    };

    int size = prescriptions.size();
    int dosages[100];

    for (int i = 0; i < size; i++){
        dosages[i] = prescriptions[i].getDosage();
    }

    cout << "Client sending dosages: ";
    for (int i = 0; i < size; ++i){
        cout << dosages[i] << " ";
    }
    cout << endl;

    int write_fd = open(write_fifo, O_WRONLY);
    write(write_fd, &size, sizeof(size));
    write(write_fd, dosages, sizeof(int) * size);
    close(write_fd);

    int read_fd = open(read_fifo, O_RDONLY);
    int sum;
    read(read_fd, &sum, sizeof(sum));
    cout << "Client received sum from server: " << sum << endl;
    close(read_fd);
}

void server(const char* read_fifo, const char* write_fifo) {
    int buffer[100];
    int size;
    int sum = 0;

    int read_fd = open(read_fifo, O_RDONLY);
    read(read_fd, &size, sizeof(size));
    read(read_fd, buffer, sizeof(int) * size);
    close(read_fd);

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << buffer[i] << " ";
        sum += buffer[i];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    int write_fd = open(write_fifo, O_WRONLY);
    write(write_fd, &sum, sizeof(sum));
    close(write_fd);
}

int main() {
    const char* fifo_client_to_server = "fifo_client_to_server";
    const char* fifo_server_to_client = "fifo_server_to_client";

    if (mkfifo(fifo_client_to_server, 0666) == -1 && errno != EEXIST) {
        perror("Error creating FIFO for client to server communication");
        return 1;
    }
    if (mkfifo(fifo_server_to_client, 0666) == -1 && errno != EEXIST) {
        perror("Error creating FIFO for server to client communication");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  
        client(fifo_client_to_server, fifo_server_to_client);
        exit(0);
    } else {  
        server(fifo_client_to_server, fifo_server_to_client);
        wait(nullptr);

        // Remove the named pipes
        unlink(fifo_client_to_server);
        unlink(fifo_server_to_client);
    }

    return 0;
}
