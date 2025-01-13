#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// Function to calculate the sum of a vector
void calculateSum(const std::vector<int>& vec, std::promise<int> sumPromise) {
    int sum = 0;
    for (int num : vec) {
        sum += num;
    }
    sumPromise.set_value(sum); // Pass the result via promise
}

// Function to find the minimum element of a vector
void findMin(const std::vector<int>& vec, std::promise<int> minPromise) {
    int minVal = *std::min_element(vec.begin(), vec.end());
    minPromise.set_value(minVal); // Pass the result via promise
}

// Function for server process
void server(int port) {
    const char* shmName = "/shared_memory";
    const size_t shmSize = 1024;

    // Create shared memory
    int shmFd = shm_open(shmName, O_CREAT | O_RDWR, 0666);
    if (shmFd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    // Set the size of shared memory
    if (ftruncate(shmFd, shmSize) == -1) {
        perror("ftruncate failed");
        close(shmFd);
        shm_unlink(shmName);
        exit(EXIT_FAILURE);
    }

    // Map shared memory
    void* shmPtr = mmap(0, shmSize, PROT_WRITE, MAP_SHARED, shmFd, 0);
    if (shmPtr == MAP_FAILED) {
        perror("mmap failed");
        close(shmFd);
        shm_unlink(shmName);
        exit(EXIT_FAILURE);
    }

    // Prepare the vector
    std::vector<int> numbers = {10, 20, 5, 15, 25};

    // Promises and futures for sum and minimum
    std::promise<int> sumPromise, minPromise;
    std::future<int> sumFuture = sumPromise.get_future();
    std::future<int> minFuture = minPromise.get_future();

    // Create threads
    std::thread sumThread(calculateSum, std::ref(numbers), std::move(sumPromise));
    std::thread minThread(findMin, std::ref(numbers), std::move(minPromise));

    // Join threads
    sumThread.join();
    minThread.join();

    // Get the results
    int sum = sumFuture.get();
    int minVal = minFuture.get();

    std::cout << "Server: Sum = " << sum << ", Min = " << minVal << std::endl;

    // Write results to shared memory
    std::string data = "Sum: " + std::to_string(sum) + ", Min: " + std::to_string(minVal);
    std::copy(data.begin(), data.end(), static_cast<char*>(shmPtr));

    // Unlink shared memory
    shm_unlink(shmName);
}

// Function for client process
void client() {
    const char* shmName = "/shared_memory";

    // Open shared memory
    int shmFd = shm_open(shmName, O_RDONLY, 0666);
    if (shmFd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    // Map shared memory
    void* shmPtr = mmap(0, 1024, PROT_READ, MAP_SHARED, shmFd, 0);
    if (shmPtr == MAP_FAILED) {
        perror("mmap failed");
        close(shmFd);
        exit(EXIT_FAILURE);
    }

    // Read and print data from shared memory
    std::cout << "Client received: " << static_cast<char*>(shmPtr) << std::endl;

    // Close shared memory
    close(shmFd);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "\t./program server <port>\n"
                  << "\t./program client\n";
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "server") == 0) {
        if (argc != 3) {
            std::cerr << "Usage: ./program server <port>\n";
            return EXIT_FAILURE;
        }
        int port = std::stoi(argv[2]);
        server(port);
    } else if (strcmp(argv[1], "client") == 0) {
        client();
    } else {
        std::cerr << "Invalid mode. Use 'server' or 'client'.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
