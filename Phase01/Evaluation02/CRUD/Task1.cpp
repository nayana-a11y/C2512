#include <iostream>
#include <iomanip>

using namespace std;

// *****Const.h*****
// Constants
const int MAX_Dosages = 100;
// *****Prescription.h*****
class Prescription {
    friend class PrescriptionManager;
    private:
        string PrescriptionID;
        int Dosage;
};
// *****PrescriptionManager.h*****
class PrescriptionManager {
    private:
        // attributes
        Prescription Prescriptions[MAX_Dosages];    
        int numDosages;
    public:
        // support
        int findIndexById(string PrescriptionID);
        // behaviours
        void create();
        void displayAll();
        void editById();
        void deleteById();
        //
        PrescriptionManager();
};
// *****Menu.h*****
void printMenu();

// *****Main.cpp*****

int main() {
    PrescriptionManager manager;
   
    int choice; // User's menu choice

    do {
        printMenu(); // Display menu
        cout << "Enter your choice: ";
        cin >> choice;

        // Menu-driven functionality
        switch (choice) {
            case 1: manager.create();    break;
            case 2: manager.displayAll();  break;
            case 3: manager.editById();      break;
            case 4: manager.deleteById();    break;
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
    if (numDosages >= MAX_Dosages) {
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

    Prescriptions[numDosages].PrescriptionID = PrescriptionID;
    Prescriptions[numDosages].Dosage = Dosage;
    numDosages++;

    cout << "Prescription created successfully.\n";
}

/**
 * @brief Displays all existing Dosages in a tabular format.
 */
void PrescriptionManager::displayAll() {
    if (numDosages == 0) {
        cout << "No prescription available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "| Prescription ID | Dosage  |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numDosages; i++) {
        cout << "| " << setw(10) << Prescriptions[i].PrescriptionID << " | "
             << setw(13) << Prescriptions[i].Dosage << " | \n";
    }
    cout << "------------------------------------------------\n";
}

/**
 * @brief Finds the index of a Prescription by ID.
 * @param id Prescription ID to search for.
 * @return Index of the Dosages if found, -1 otherwise.
 */
int PrescriptionManager::findIndexById(string id) {
    for (int i = 0; i < numDosages; i++) {
        if (Prescriptions[i].PrescriptionID == id) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Edits an existing Dosages by ID.
 */

void PrescriptionManager::editById() {
    string PrescriptionID;
    cout << "Enter PrescriptionID to edit: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: PrescriptionID not found.\n";
        return;
    }

    cout << "Current Details - Dosage : " << Prescriptions[index].Dosage << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> Prescriptions[index].Dosage;

    cout << "Dosage updated successfully.\n";
}

/**
 * @brief Deletes an existing Dosage by ID.
 */
void PrescriptionManager::deleteById() {
    string PrescriptionID;
    cout << "Enter Prescription ID to delete: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    // Shift data to fill the gap
    for (int i = index; i < numDosages - 1; i++) {
        Prescriptions[i] = Prescriptions[i + 1];
    }
    numDosages--;

    cout << " Prescription deleted successfully.\n";
}

PrescriptionManager::PrescriptionManager() {
    numDosages = 0;
}
// *****Menu.cpp*****
void printMenu() {
    cout << "\n=== Prescription Management System ===\n";
    cout << "1. Create Booking\n";
    cout << "2. Display All Dosages\n";
    cout << "3. Edit Booking\n";
    cout << "4. Delete Booking\n";
    cout << "5. Exit\n";
}
