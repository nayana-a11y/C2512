#include <iostream>
#include <iomanip>

using namespace std;

// *****Const.h*****
// Constants
const int MAX_Dosages = 100;
// *****Booking.h*****
class Prescription {
    friend class PrescriptionManager;
    private:
        int PrescriptionID;
        int Dosage;
};
// *****PrescriptionManager.h*****
class PrescriptionManager {
    private:
        // attributes
        Prescription Dosages[MAX_Dosages];    
        int numDosages;
    public:
        // support
        int findIndexById(int PrescriptionID);
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

    int PrescriptionID; 
    int Dosage;

    cout << "Enter Prescription ID: ";
    cin >> PrescriptionID;

    // Ensure booking ID is unique
    if (findIndexById(PrescriptionID) != -1) {
        cout << "Error: Prescription ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter Dosage: ";
    cin >> Dosage;

    // Store the booking details
    Dosages[numDosages].PrescriptionID = PrescriptionID;
    Dosages[numDosages].Dosage = Dosage;
    numDosages++;

    cout << "Booking created successfully.\n";
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
        cout << "| " << setw(10) << Dosages[i].PrescriptionID << " | "
             << setw(13) << Dosages[i].Dosage << " | \n";
    }
    cout << "------------------------------------------------\n";
}

/**
 * @brief Finds the index of a booking by ID.
 * @param id Booking ID to search for.
 * @return Index of the booking if found, -1 otherwise.
 */
int PrescriptionManager::findIndexById(int id) {
    for (int i = 0; i < numDosages; i++) {
        if (Dosages[i].PrescriptionID == id) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Edits an existing booking by ID.
 */

void PrescriptionManager::editById() {
    int PrescriptionID;
    cout << "Enter PrescriptionID to edit: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: PrescriptionID not found.\n";
        return;
    }

    cout << "Current Details - Dosage : " << Dosages[index].Dosage << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> Dosages[index].Dosage;

    cout << "Dosage updated successfully.\n";
}

/**
 * @brief Deletes an existing booking by ID.
 */
void PrescriptionManager::deleteById() {
    int PrescriptionID;
    cout << "Enter Prescription ID to delete: ";
    cin >> PrescriptionID;

    int index = findIndexById(PrescriptionID);
    if (index == -1) {
        cout << "Error: Prescription ID not found.\n";
        return;
    }

    // Shift data to fill the gap
    for (int i = index; i < numDosages - 1; i++) {
        Dosages[i] = Dosages[i + 1];
    }
    numDosages--;

    cout << " deleted successfully.\n";
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
