// mix 
// array of doctors
// findSum, findMinInFirstHalf, findMaxInSecondHalf
//    +
// array of doctors
// multi-threaded "findSum, findMinInFirstHalf, findMaxInSecondHalf"

// driver code: array of doctors, EXECUTION_POLICY = 1 (SEQ), 2 (PAR)

#include <climits>

#include <iostream>

#include <string>
#include <vector>
#include <tuple>

#define EXECUTION_POLICY 1 //= 1 (SEQ), 2 (PAR)
#if EXECUTION_POLICY == 2
#include <thread>
#endif

using identity_t = std::string;
using years_t = short;

class Doctor {
    private:
        identity_t id;
        years_t yearsOfExperience;
    public: 
        Doctor(identity_t id, years_t yearsOfExperience) : id(id), yearsOfExperience(yearsOfExperience) { }
        years_t getYearsOfExperience() { return this->yearsOfExperience; }
};

years_t findSum(std::vector<Doctor>& doctors) {
    years_t sum = 0;
    for(auto doctor : doctors) {
        sum += doctor.getYearsOfExperience();
    }
    return sum;
}

years_t findMinInFirstHalf(std::vector<Doctor>& doctors) {
    years_t min = SHRT_MAX;
    int half = doctors.size() / 2;
    for(int I =0 ; I < half; I++) {
        if(doctors[I].getYearsOfExperience() < min) {
            min = doctors[I].getYearsOfExperience();
        }
    }
    return min;
}

years_t findMaxInSecondHalf(std::vector<Doctor>& doctors) {
    years_t max = SHRT_MIN;
    int half = doctors.size() / 2;
    for(int I =half ; I < doctors.size(); I++) {
        if(doctors[I].getYearsOfExperience() > max) {
            max = doctors[I].getYearsOfExperience();
        }
    }
    return max;
}

std::tuple<years_t, years_t, years_t>  compute(std::vector<Doctor>& doctors) {
    years_t sum;
    years_t min; 
    years_t max; 

#if EXECUTION_POLICY == 1
    sum = findSum(doctors);
    min = findMinInFirstHalf(doctors);
    max = findMaxInSecondHalf(doctors);
#elif EXECUTION_POLICY == 2
    std::thread thrSum([](std::vector<Doctor>& doctors, years_t& sum) -> void 
        { 
            sum = findSum(doctors);
        }, std::ref(doctors), std::ref(sum));
    std::thread thrMin([](std::vector<Doctor>& doctors, years_t& min) -> void 
        { 
            min = findMinInFirstHalf(doctors);
        }, std::ref(doctors), std::ref(min));
    std::thread thrMax([](std::vector<Doctor>& doctors, years_t& max) -> void 
        { 
            max = findMaxInSecondHalf(doctors);
        }, std::ref(doctors), std::ref(max));
    thrSum.join();
    thrMax.join();
    thrMin.join();
#endif

    return {sum, min, max};
}

int main() {
    std::vector<Doctor> doctors {        
        Doctor("D001", 5),
        Doctor("D002", 4),
        Doctor("D003", 3),
        Doctor("D004", 2),
        Doctor("D005", 1)
    };

    auto [sum, min, max] = compute(doctors);

    std::cout << "Sum = " << sum << std::endl;
    std::cout << "Min = " << min << std::endl;
    std::cout << "Max = " << max << std::endl;

    return 0;
}
