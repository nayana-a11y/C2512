
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <string>

using namespace std;

class Prescription {
private:
    string Prescription_id;
    int Dosage;
public:
    Prescription(string p_id, int p_dosage) : Prescription_id(p_id), Dosage(p_dosage) {}

    string getPrescription_id(){ 
        return Prescription_id; 
    }
    int getDosage() 
    { 
        return Dosage; 
    }
};

//write_to_server read_fd
//read_from_server write_fd 

void client(int read_fd, int write_fd) {
    vector<Prescription> prescriptions = {
        Prescription("01", 4), 
        Prescription("02", 5), 
        Prescription("03", 6), 
        Prescription("04", 7), 
        Prescription("05", 1)
    };

    int size = prescriptions.size();
    int arr[100];

    for (int i = 0; i < size; i++){
        arr[i] = prescriptions[i].getDosage();
    }

    cout << "Client sending dosages: ";
    for (int i = 0; i < size; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;

    write(read_fd, &size, sizeof(size));
    write(read_fd, arr, sizeof(int)* size);

    int sum;
    read(write_fd, &sum, sizeof(sum));
    cout << "Client received sum from server: " << sum << endl;

    close(read_fd);
    close(write_fd);
}
//read_from_client read_fd
//write_to_client write_fd
void server(int read_fd, int write_fd) {
    int buffer[100];
    int size;
    int sum = 0;

    read(read_fd, &size, sizeof(size));
    read(read_fd, buffer, sizeof(int)* size);

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << buffer[i] << " ";
        sum += buffer[i];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    write(write_fd, &sum, sizeof(sum));

    close(read_fd);
    close(write_fd);
}

int main() {
    int pipe_clienttoserver[2], pipe_servertoclient[2];

    if (pipe(pipe_clienttoserver) == -1 || pipe(pipe_servertoclient) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process (Client)
        close(pipe_servertoclient[1]); //
        close(pipe_clienttoserver[0]); //read end 
        client(pipe_clienttoserver[1], pipe_servertoclient[0]);
        exit(0);
    } else {  // Server
        close(pipe_clienttoserver[1]);
        close(pipe_servertoclient[0]);
        server(pipe_clienttoserver[0], pipe_servertoclient[1]);
        //wait(nullptr); 
    }

    return 0;
}
