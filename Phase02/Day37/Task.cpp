#include <iostream>
#include <thread>
#include <vector>

// two threads
void findSum(std::vector<int> &vec);
void findMin(std::vector<int> &vec);

int main()
{
    std::vector<int> numbers = {3, 5, 2, 6, 1, 9, 10, 7};

    std::thread threadSum(findSum, std::ref(numbers));
    std::thread threadMin(findMin, std::ref(numbers));

    threadSum.join();
    threadMin.join();

    return 0;
}

void findSum(std::vector<int> &vec)
{
    int sum = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum+=vec[i];
    }
    std::cout << "The sum of values of the vector is: " << sum << std::endl;
}

void findMin(std::vector<int> &vec)
{
    int min = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < min)
        {
            min = vec[i];
        }
    }
    std::cout << "The minimum value from the values of the vector is: " << min << std::endl;
}
