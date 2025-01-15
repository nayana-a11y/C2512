#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <atomic>

std::atomic<int> totalSum(0);

void findSum(const std::vector<int>& prescriptions, int start, int end) {
    //int sum = 0;
    for (int i = start; i <= end ; i++)  {
        sum += prescriptions[i];
    }
    totalSum.fetch_add(sum);
}
void findSum2(const std::vector<int>& prescriptions, int start, int end) {
    //int sum = 0;
    for (int i = ((prescriptions.size() - 1) / 2); i < prescriptions.size(); i++) {
        sum += prescriptions[i];
    }
    totalSum.fetch_add(sum);
}
int main() {
    std::vector<int> prescriptions = {2, 9, 7, 4, 8};

    int mid = prescriptions.size()/2;

    std::thread threadSum1(findSum, std::ref(prescriptions), 0, mid);
    std::thread threadSum2(findSum, std::ref(prescriptions), mid, prescriptions.size() );

    threadSum1.join();
    threadSum2.join();

    std::cout << "The total sum is: " << totalSum.load() << std::endl;

    return 0;
}
