#include <iostream>
#include <iomanip>
#include <string>
//
using std::string;
//"************"HospitalStay.h"************
class HospitalStay {
    private:
        string StayID;
        int NumberOfDays;
    public:
        //behaviours
        bool LessThan(const HospitalStay& other);
        //constructor
        HospitalStay(string p_StayID, int p_NumberOfDays);
};
//"************"Main.cpp"************
int main() {
    HospitalStay hs1("HS001", 5); HospitalStay hs2("HS002", 7);

    std::cout << std::boolalpha;
    std::cout << "LessThan: " << hs1.LessThan(hs2) << std::endl; // Output: true
    return 0;
}
//************"HospitalStay.cpp"************
//behaviours
bool HospitalStay::LessThan(const HospitalStay& other) {
    return (NumberOfDays < other.NumberOfDays);
}
//constructor
HospitalStay::HospitalStay(string p_StayID, int p_NumberOfDays) {
    StayID = p_StayID;
    NumberOfDays = p_NumberOfDays;
}
