
#include <iostream>
#include <thread>
#include <vector>
#include <string>

int min = 1000;
int max = 0;

class Prescription {
private:
    std::string prescriptionId;
    int dosage;

public:
    Prescription(std::string p_id, int p_dosage) : prescriptionId(p_id), dosage(p_dosage) {}

    friend double findSum(const std::vector<double>& pres);
    friend void findMinInFirstHalf(const std::vector<double>& pres);
    friend void findMaxInSecondHalf(const std::vector<double>& pres);
};

 double findSum(const std::vector<double>& pres) {
    double sum = 0;
    for (double p_dosage : pres) {
        sum += p_dosage;
    }
    return sum;
    
}

void findMinInFirstHalf(const std::vector<double>& pres) {

    for (int i = 1; i <= ((pres.size()-1) / 2) ; i++) {
        if (pres[i] < min) {
            min = pres[i];
        }
    }
    
}

void findMaxInSecondHalf(const std::vector<double>& pres) {
    for (int i = ((pres.size() - 1) / 2); i < pres.size(); i++) {
        if (pres[i] > max) {
            max = pres[i];
        }
    }
    
}

int main() {
    std::string p_id;
    int p_dosage;
    int sum;

    std::vector<double> pres = {3, 2, 7, 4, 5};

    Prescription prescription(p_id, p_dosage);
    
    sum = prescription.findSum(pres);
    std::cout << "The total sum is: " << sum << std::endl;

    prescription.findMinInFirstHalf(pres);
    std::cout << "The minimum is " << min << std::endl;

    prescription.findMaxInSecondHalf(pres);
    std::cout << "The maximum is: " << max << std::endl;

    return 0;
}
