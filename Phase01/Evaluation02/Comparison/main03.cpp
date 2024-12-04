#include <iostream>
#include <iomanip>
#include <string>

using std::string;

class Prescription {
    private:
        string PrescriptionID;
        int Dosage;
    public:
        //behaviours
        friend bool LessThan(const Prescription& first, const Prescription& second);
        //constructor
        Prescription(string p_PrescriptionID, int p_Dosage);
};

 bool LessThan(const Prescription& first, const Prescription& second);

//"************"Main.cpp"************
class HospitalStay {
    private:
        string StayID;
        int NumberOfDays;
    public:
        //constructor
        HospitalStay(string p_StayID, int p_NumberOfDays);
        //friends
        friend bool LessThan(const HospitalStay& first, const HospitalStay& second);
};
bool LessThan(const HospitalStay& first, const HospitalStay& second);

int main() {
    Prescription pres1("RX001", 500);
    Prescription pres2("RX002", 400);
    HospitalStay hs1("HS001", 5); 
    HospitalStay hs2("HS002", 7);
    
    std::cout << std::boolalpha;
    std::cout << "Presription LessThan: " << pres1.LessThan(pres2) << std::endl;   // Output: false
     std::cout << "HospitalStay LessThan: " << LessThan(hs1, hs2) << std::endl; // Output: true
    return 0;
}

//behaviours
bool LessThan(const HospitalStay& first, const HospitalStay& second) {
    return (first.NumberOfDays < second.NumberOfDays);
}
bool LessThan(const Prescription& first, const Prescription& second);
{
    return (first.Dosage < second.Dosage);
}
//constructor
Prescription::Prescription(string p_PrescriptionID, int p_Dosage)
{
    PrescriptionID = p_PrescriptionID;
    Dosage = p_Dosage;
}
HospitalStay::HospitalStay(string p_StayID, int p_NumberOfDays) {
    StayID = p_StayID;
    NumberOfDays = p_NumberOfDays;
}
