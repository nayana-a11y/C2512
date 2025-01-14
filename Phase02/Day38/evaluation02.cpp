#include <iostream>
#include <thread>
#include <vector>
#include <string>

// Global variables for min and max
int min;
int max;

// Function to calculate the sum of dosages
void findSum(const std::vector<int>& dosages, int& sum) {
    sum = 0;
    for (int dosage : dosages) {
        sum += dosage;
    }
}

// Function to find the minimum value in the first half
void findMinInFirstHalf(const std::vector<int>& dosages) {
    min = dosages[0]; // Initialize min with the first element
    for (size_t i = 0; i < dosages.size() / 2; ++i) {
        if (dosages[i] < min) {
            min = dosages[i];
        }
    }
}

// Function to find the maximum value in the second half
void findMaxInSecondHalf(const std::vector<int>& dosages) {
    max = dosages[dosages.size() / 2]; // Initialize max with the first element of the second half
    for (size_t i = dosages.size() / 2; i < dosages.size(); ++i) {
        if (dosages[i] > max) {
            max = dosages[i];
        }
    }
}

int main() {
    // Create a vector of dosages
    std::vector<int> dosages = {3, 2, 7, 4, 5};

    int sum = 0;

    // Create threads for each task
    std::thread threadSum(findSum, std::ref(dosages), std::ref(sum));
    std::thread threadMin(findMinInFirstHalf, std::ref(dosages));
    std::thread threadMax(findMaxInSecondHalf, std::ref(dosages));

    // Wait for all threads to complete
    threadSum.join();
    threadMin.join();
    threadMax.join();

    // Display the results
    std::cout << "The total sum is: " << sum << std::endl;
    std::cout << "The minimum value in the first half is: " << min << std::endl;
    std::cout << "The maximum value in the second half is: " << max << std::endl;

    return 0;
}
