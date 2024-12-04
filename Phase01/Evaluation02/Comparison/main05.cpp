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
        bool LessThan(const Prescription& other);
        //constructor
        Prescription(string p_PrescriptionID, int p_Dosage);
};


//"************"Main.cpp"************
int main() {
    Prescription Prescription[] = {Prescription pres1("RX001", 500), Prescription pres2("RX002", 400)};

    std::cout << std::boolalpha;
    std::cout << "LessThan: " << Prescription[0].LessThan(Prescription[1]) << std::endl;   // Output: false

    return 0;
}
//behaviours
bool Prescription::LessThan(const Prescription& other);
{
    return (Dosage < other.Dosage);
}
//constructor
Prescription::Prescription(string p_PrescriptionID, int p_Dosage)
{
    PrescriptionID = p_PrescriptionID;
    Dosage = p_Dosage;
}
