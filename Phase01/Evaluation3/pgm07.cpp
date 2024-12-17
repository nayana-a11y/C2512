#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

class PrescriptionManager {
private:
    deque<string> PrescriptionIDs;
    deque<int> Dosages;

public:
    int findIndexById(const string& PrescriptionID);
    void create();
    void displayAll();
    void editById();
    void deleteById();
};

void printMenu();

int main() {
    PrescriptionManager manager;

    int choice; // User's menu choice

    do {
        printMenu(); // Display menu
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

    PrescriptionIDs.push_back(PrescriptionID);
    Dosages.push_back(Dosage);

    cout << "Prescription created successfully.\n";
}

void PrescriptionManager::displayAll() {
    if (PrescriptionIDs.empty()) {
        cout << "No prescriptions available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "| Prescription ID   | Dosage       |\n";
    cout << "------------------------------------------------\n";

    for (size_t i = 0; i < PrescriptionIDs.size(); i++) {
        cout << "| " << setw(15) << PrescriptionIDs[i] << " | "
             << setw(12) << Dosages[i] << " |\n";
    }

    cout << "------------------------------------------------\n";
}

int PrescriptionManager::findIndexById(const string& id) {
    auto iter = find(PrescriptionIDs.begin(), PrescriptionIDs.end(), id);
    if (iter != PrescriptionIDs.end()) {
        return distance(PrescriptionIDs.begin(), iter);
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

    cout << "Current Dosage: " << Dosages[index] << "\n";
    cout << "Enter New Dosage Amount: ";
    cin >> Dosages[index];

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
