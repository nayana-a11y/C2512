#include <iostream>
#include <thread>
#include <vector>
#include <string>

int min;
int max;

void findSum(const std::vector<int>& dosages, int& sum) {
    sum = 0;
    for (int dosage : dosages) {
        sum += dosage;
    }
}

void findMinInFirstHalf(const std::vector<int>& dosages) {
    min = dosages[0]; 
    for (size_t i = 0; i < dosages.size() / 2; ++i) {
        if (dosages[i] < min) {
            min = dosages[i];
        }
    }
}

void findMaxInSecondHalf(const std::vector<int>& dosages) {
    max = dosages[dosages.size() / 2]; 
    for (size_t i = dosages.size() / 2; i < dosages.size(); ++i) {
        if (dosages[i] > max) {
            max = dosages[i];
        }
    }
}

int main() {
    std::vector<int> dosages = {2, 9, 7, 4, 8};

    int sum = 0;

    std::thread threadSum(findSum, std::ref(dosages), std::ref(sum));
    std::thread threadMin(findMinInFirstHalf, std::ref(dosages));
    std::thread threadMax(findMaxInSecondHalf, std::ref(dosages));

    threadSum.join();
    threadMin.join();
    threadMax.join();

    std::cout << "The total sum is: " << sum << std::endl;
    std::cout << "The minimum is: " << min << std::endl;
    std::cout << "The maximum is: " << max << std::endl;

    return 0;
}
