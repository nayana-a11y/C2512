#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

// Constants
const int MAX_Dosages = 100;

class Prescription {
    friend class PrescriptionManager;
    private:
        string PrescriptionID;
        int Dosage;
};

class PrescriptionManager {
    private:
        deque<Prescription> Prescriptions;
    public:
        int findIndexById(const string& PrescriptionID);
        void create();
        void displayAll();
        void editById();
        void deleteById();
        PrescriptionManager();
};

void printMenu();

int main() {
    PrescriptionManager manager;

    int choice; // User's menu choice

    do {
        printMenu(); // Display menu
        cout << "Enter your choice: ";
        cin >> choice;

        // Menu-driven functionality
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
    if (Prescriptions.size() >= MAX_Dosages) {
        cout << "Error: Maximum limit reached.\n";
        return;
    }

    string PrescriptionID; 
    int Dosage;

    cout << "Enter Prescription ID: ";
    cin >> PrescriptionID;

    if (findIndexById(PrescriptionID) != -1) {
        cout << "Error: Prescription ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter Dosage: ";
    cin >> Dosage;

    Prescription newPrescription;
    newPrescription.PrescriptionID = PrescriptionID;
    newPrescription.Dosage = Dosage;

    Prescriptions.push_back(newPrescription);

    cout << "Prescription created successfully.\n";
}

void PrescriptionManager::displayAll() {
    if (Prescriptions.empty()) {
        cout << "No prescriptions available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "| Prescription ID | Dosage  |\n";
    cout << "------------------------------------------------\n";
    for (const auto& prescription : Prescriptions) {
        cout << "| " << setw(10) << prescription.PrescriptionID << " | "
             << setw(13) << prescription.Dosage << " | \n";
    }
    cout << "------------------------------------------------\n";
}


int PrescriptionManager::findIndexById(const string& id) {
    for (size_t i = 0; i < Prescriptions.size(); ++i) {
        if (Prescriptions[i].PrescriptionID == id) {
            return i;
        }
    }
    return -1;
}


void PrescriptionManager::editById() {
    string PrescriptionID;
    cout << "Enter Prescription ID to edit: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    cout << "Current Details - Dosage: " << Prescriptions[index].Dosage << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> Prescriptions[index].Dosage;

    cout << "Dosage updated successfully.\n";
}


void PrescriptionManager::deleteById() {
    string PrescriptionID;
    cout << "Enter Prescription ID to delete: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    Prescriptions.erase(Prescriptions.begin() + index);

    cout << "Prescription deleted successfully.\n";
}

PrescriptionManager::PrescriptionManager() {
    // No explicit initialization required for deque
}

void printMenu() {
    cout << "\n=== Prescription Management System ===\n";
    cout << "1. Create Prescription\n";
    cout << "2. Display All Prescriptions\n";
    cout << "3. Edit Prescription\n";
    cout << "4. Delete Prescription\n";
    cout << "5. Exit\n";
}
