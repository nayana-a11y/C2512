#include <iostream>
#include <iomanip>
#include <string>

using std::string;

class Prescription {
    private:
        string PrescriptionID;
        int Dosage;
    public:
        //constructor
        Prescription(string p_PrescriptionID, int p_Dosage);
        //friends
        friend class Comparisons;
};

class Comparisons {
    public:
        static bool LessThan(const Prescription& first, const Prescription& second);
}
//"************"Main.cpp"************
int main() {
    Prescription pres1("RX001", 500);
    Prescription pres2("RX002", 400);

    std::cout << std::boolalpha;
    std::cout << "LessThan: " << pres1.LessThan(pres2) << std::endl;   // Output: false

    return 0;
}
//behaviours
bool Comparisons::LessThan(const Prescription& first, const Prescription& second);
{
    return (first.Dosage < second.Dosage);
}
//constructor
Prescription::Prescription(string p_PrescriptionID, int p_Dosage)
{
    PrescriptionID = p_PrescriptionID;
    Dosage = p_Dosage;
}
