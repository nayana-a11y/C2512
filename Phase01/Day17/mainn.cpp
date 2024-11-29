
#include <iostream>
#include <iomanip>
#include "prescription.h"

#include <string>

using std::string;

class Prescription
{
    private:
        string PrescriptionID;
        int Dosage;
    public:
        //behaviours
        bool Equals(const Prescription& other);
        bool NotEquals(const Prescription& other);
        bool GreaterThan(const Prescription& other);
        bool GreaterThanEquals(const Prescription& other);
        bool LessThan(const Prescription& other);
        bool LessThanEquals(const Prescription& other);
        //constructor
        Prescription(string p_PrescriptionID, int p_Dosage);
};

int main() {
    Prescription pres1("RX001", 500);
    Prescription pres2("RX002", 400);

    std::cout << std::boolalpha;
    std::cout << "Equals: " << pres1.Equals(pres2) << std::endl;          // Output: false
    std::cout << "GreaterThan: " << pres1.GreaterThan(pres2) << std::endl;       // Output: true
    std::cout << "LessThanEquals: " << pres1.LessThanEquals(pres2) << std::endl;   // Output: false

    return 0;
}


//behaviours
bool Prescription::Equals(const Prescription& other)
{
    return (Dosage == other.Dosage);
}

bool Prescription::NotEquals(const Prescription& other)
{
    return (Dosage != other.Dosage);
}

bool Prescription::GreaterThan(const Prescription& other)
{
    return (Dosage > other.Dosage);
}

bool Prescription::GreaterThanEquals(const Prescription& other)
{
    return (Dosage >= other.Dosage);
}

bool Prescription::LessThan(const Prescription& other)
{
    return (Dosage < other.Dosage);
}

bool Prescription::LessThanEquals(const Prescription& other)
{
    return (Dosage <= other.Dosage);
}

//constructor
Prescription::Prescription(string p_PrescriptionID, int p_Dosage)
{
    PrescriptionID = p_PrescriptionID;
    Dosage = p_Dosage;
}

