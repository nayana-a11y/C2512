#include <iostream>

#include <unistd.h>
#include <cstring>

#include <string>
#include <sstream>

#include <cstdlib>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<thread>
#include<vector>
#include<mutex>

#define BUFFER_SIZE 1024
#define MAX_CONNS 5
std::mutex cout_mutex; // For synchronized console output

void server(int port);
void serveClient(int&);
void client(std::string server_ip, int port);
void requestServer(int&);

void server(int port) {
    int server_socket_fd;
    // Create socket
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address; //struct sockaddr_in
    
    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_socket_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket_fd, MAX_CONNS) < 0) { 
        perror("Listen failed");
        close(server_socket_fd);
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    std::vector<std::thread> threads;

    while (true) {
        int client_socket_fd;
        sockaddr_in client_address;
        socklen_t addrlen = sizeof(client_address);

        // Accept a connection
        if ((client_socket_fd = accept(server_socket_fd, (sockaddr*)&client_address, &addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        // Create a new thread to handle the client
        threads.emplace_back(std::thread(serveClient, std::ref(client_socket_fd)));
    }
    // Clean up threads
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Close server socket
    close(server_socket_fd);
}

void serveClient(int& client_socket_fd) {
    char buffer[BUFFER_SIZE];

    long first;
    long second;
    // receive first number
    read(client_socket_fd, buffer, BUFFER_SIZE);
    first = atol(buffer);
    // receive second number 
    read(client_socket_fd, buffer, BUFFER_SIZE);
    second = atol(buffer);
    // process numbers
    long sum = first + second;

    {
        //std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "process:" << first << " + " 
                                << second << " = " 
                                << sum << " done." << std::endl;
    }
    // send response
    std::string sumStr = std::to_string(sum);
    strcpy(buffer, sumStr.c_str()); buffer[sumStr.size()] = '\0';
    send(client_socket_fd, buffer, strlen(buffer)+1, 0);

    {
        //std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\tresponse sent to client" << std::endl;
    }

    // release client // Close client socket
    close(client_socket_fd);
}

void client(std::string server_ip, int port) {
    int client_socket_fd = 0;  
    // create socket
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    // specify server address
    sockaddr_in server_address; //struct sockaddr_in
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // request the server 
    requestServer(client_socket_fd);

    // close client socket
    close(client_socket_fd);
}

void requestServer(int& client_socket_fd) {
    char buffer[BUFFER_SIZE];

    long first;
    long second;
    std::cout << "First Number:"; std::cin >> first;
    std::cout << "Second Number:"; std::cin >> second;
    // send numbers
    std::string firstStr = std::to_string(first);
    std::string secondStr = std::to_string(second);

    strcpy(buffer, firstStr.c_str()); buffer[firstStr.size()] = '\0';
    send(client_socket_fd, buffer, strlen(buffer)+1, 0);

    strcpy(buffer, secondStr.c_str()); buffer[secondStr.size()] = '\0';
    send(client_socket_fd, buffer, strlen(buffer)+1, 0);
    // receive response
   
    read(client_socket_fd, buffer, BUFFER_SIZE);
    //
    long sum = atol(buffer);
    std::cout << "So," << first << " + " 
                            << second << " = " 
                            << sum << std::endl;
    std::cout << "I am thankful to my sum calculator server!!!" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc <= 1) {
        std::cout << "App is not running..." << std::endl;
        return EXIT_FAILURE;
    }

    if(!(
       (strcmp(argv[1], "client") == 0 && argc == 4) || 
       (strcmp(argv[1], "server") == 0 && argc == 3)
       )) {
        std::cout << "usage:\n\t./sumCalculatorApp.out server 8080" << std::endl;
        std::cout << "\t./sumCalculatorApp.out client 127.0.0.1 8080" << std::endl;
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "client") == 0) {
        std::cout << "Client [to server `" << argv[2] << ":" << argv[3] << "`]" << std::endl;      
        client(argv[2], atoi(argv[3]));  
    }
    if(strcmp(argv[1], "server") == 0) {
        std::cout << "Server [port:`" << argv[2] << "`]" <<std::endl;
        server(atoi(argv[2]));
    }
    
    return EXIT_SUCCESS;
}
