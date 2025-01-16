
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

class Prescription {
private:
    string Prescription_id;
    double Dosage;
public:
    Prescription(string p_id, double p_dosage) : Prescription_id(p_id), Dosage(p_dosage) {}

    double getDosage() { 
        return Dosage; 
    }
};

void server(int server_fd) {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int buffer[100];
    int size;
    int sum = 0;

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Server accept failed");
        exit(1);
    }

    read(client_fd, &size, sizeof(size));
    read(client_fd, buffer, sizeof(int) * size);

    cout << "Server received dosages: ";
    for (int i = 0; i < size; i++) {
        cout << buffer[i] << " ";
        sum += buffer[i];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    write(client_fd, &sum, sizeof(sum));

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  
    server_addr.sin_addr.s_addr = INADDR_ANY;  

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Server bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Server listen failed");
        return 1;
    }

    cout << "Server is listening on port 8080..." << endl;

    server(server_fd);

    close(server_fd);

    return 0;
}
