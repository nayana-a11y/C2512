#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

void client(int read_fd, int write_fd) {
    char buffer[1024];
    while (true) {
        // Read message from server
        read(read_fd, buffer, sizeof(buffer));
        std::cout << "Server: " << buffer << std::endl;

        // Get input from client
        std::cout << "Client: ";
        std::cin.getline(buffer, sizeof(buffer));

        // Write message to server
        write(write_fd, buffer, strlen(buffer) + 1);

        if (strcmp(buffer, "exit") == 0) break; // Exit condition
    }
}

void server(int read_fd, int write_fd) {
    char buffer[1024];
    while (true) {
        // Get input from server
        std::cout << "Server: ";
        std::cin.getline(buffer, sizeof(buffer));

        // Write message to client
        write(write_fd, buffer, strlen(buffer) + 1);

        if (strcmp(buffer, "exit") == 0) break; // Exit condition

        // Read message from client
        read(read_fd, buffer, sizeof(buffer));
        std::cout << "Client: " << buffer << std::endl;
    }
}

int main() {
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process (Client)
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2
        client(pipe1[0], pipe2[1]);
        close(pipe1[0]);
        close(pipe2[1]);
    } else { // Parent process (Server)
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2
        server(pipe2[0], pipe1[1]);
        close(pipe1[1]);
        close(pipe2[0]);
        wait(nullptr); // Wait for child process to finish
    }

    return 0;
}
