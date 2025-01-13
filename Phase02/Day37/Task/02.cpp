#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric> 

void calculateSum(const std::vector<int>& vec, int& result) {
    result = std::accumulate(vec.begin(), vec.end(), 0); 
}
void findMinimum(const std::vector<int>& vec, int& result) {
    result = *std::min_element(vec.begin(), vec.end()); // Find minimum
}

int main() {
 
    std::vector<int> numbers = {5, 2, 8, 1, 10, -3, 4};

    int sumResult = 0;
    int minResult =0;

    std::thread threadSum(calculateSum, std::cref(numbers), std::ref(sumResult));
    std::thread threadMin(findMinimum, std::cref(numbers), std::ref(minResult));

    threadSum.join();
    threadMin.join();

    std::cout << "Sum of elements: " << sumResult << std::endl;
    std::cout << "Minimum value: " << minResult << std::endl;
    return 0;
}
