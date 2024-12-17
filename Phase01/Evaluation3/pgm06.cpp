// 2.1
//     change the crud ops with HospitalStay from array of HospitalStay called `stays`
//     to vector<HospitalStay> stays.
//  2.2 vector -> deque 


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class PrescriptionManager {
private:
    vector<string> PrescriptionIDs; 
    vector<int> Dosages;            

public:
    int findIndexById(const string& id);
    void create();
    void displayAll();
    void editById();
    void deleteById();
};

void printMenu();

int main() {
    PrescriptionManager manager;

    int choice;

    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.create();       break;
            case 2: manager.displayAll();   break;
            case 3: manager.editById();     break;
            case 4: manager.deleteById();   break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

void PrescriptionManager::create() {
    string prescriptionID;
    int dosage;

    cout << "Enter Prescription ID: ";
    cin >> prescriptionID;

    if (findIndexById(prescriptionID) != -1) {
        cout << "Error: Prescription ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter Dosage: ";
    cin >> dosage;

    PrescriptionIDs.push_back(prescriptionID);
    Dosages.push_back(dosage);

    cout << "Prescription created successfully.\n";
}

void PrescriptionManager::displayAll() {
    if (PrescriptionIDs.empty()) {
        cout << "No prescriptions available to display.\n";
        return;
    }

    cout << "-----------------------------------------\n";
    cout << "| Prescription ID   | Dosage            |\n";
    cout << "-----------------------------------------\n";

    for (size_t i = 0; i < PrescriptionIDs.size(); i++) {
        cout << "| " << setw(17) << PrescriptionIDs[i] << " | "
             << setw(16) << Dosages[i] << " |\n";
    }

    cout << "-----------------------------------------\n";
}

int PrescriptionManager::findIndexById(const string& id) {
    auto iter = find(PrescriptionIDs.begin(), PrescriptionIDs.end(), id);
    if (iter != PrescriptionIDs.end()) {
        return distance(PrescriptionIDs.begin(), iter);
    }
    return -1;
}

void PrescriptionManager::editById() {
    string prescriptionID;
    cout << "Enter Prescription ID to edit: ";
    cin >> prescriptionID;

    int index = findIndexById(prescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    cout << "Current Dosage: " << Dosages[index] << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> Dosages[index];

    cout << "Dosage updated successfully.\n";
}

void PrescriptionManager::deleteById() {
    string prescriptionID;
    cout << "Enter Prescription ID to delete: ";
    cin >> prescriptionID;

    int index = findIndexById(prescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    PrescriptionIDs.erase(PrescriptionIDs.begin() + index);
    Dosages.erase(Dosages.begin() + index);

    cout << "Prescription deleted successfully.\n";
}

void printMenu() {
    cout << "\n=== Prescription Management System ===\n";
    cout << "1. Create Prescription\n";
    cout << "2. Display All Prescriptions\n";
    cout << "3. Edit Prescription\n";
    cout << "4. Delete Prescription\n";
    cout << "5. Exit\n";
}
