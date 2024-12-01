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
int main() {
    Prescription pres1("RX001", 500);
    Prescription pres2("RX002", 400);

    std::cout << std::boolalpha;
    std::cout << "LessThan: " << pres1.LessThan(pres2) << std::endl;   // Output: false

    return 0;
}
//behaviours
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

