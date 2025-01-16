
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

    friend void findSum(const std::vector<int>& dosages);
    friend void findMinInFirstHalf(const std::vector<int>& dosages);
    friend void findMaxInSecondHalf(const std::vector<int>& dosages);
};

void findSum(const std::vector<int>& dosages) {
    int sum = 0;
    for (double p_dosage : dosages) {
        sum += p_dosage;
    }
}

void findMinInFirstHalf(const std::vector<int>& dosages) {

    for (int i = 1; i <= ((dosages.size()-1) / 2) ; i++) {
        if (dosages[i] < min) {
            min = dosages[i];
        }
    }
}

void findMaxInSecondHalf(const std::vector<int>& dosages) {
    for (int i = ((pres.size() - 1) / 2); i < dosages.size(); i++) {
        if (dosages[i] > max) {
            max = dosages[i];
        }
    }
}

int main() {
    std::string p_id;
    int p_dosage;

    std::vector<int> dosages = {3, 2, 7, 4, 5};

    Prescription prescription(p_id, p_dosage);
    
    
    prescription.findSum(dosages);
    std::cout << "The total sum is: " << sum << std::endl;

    prescription.findMinInFirstHalf(dosages);
    std::cout << "The minimum is " << min << std::endl;

    prescription.findMaxInSecondHalf(dosages);
    std::cout << "The maximum is: " << max << std::endl;

    return 0;
}
