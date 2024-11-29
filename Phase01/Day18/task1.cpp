#include <iostream>
#include <iomanip>

using namespace std;

// *****Const.h*****
// Constants
const int MAX_BOOKINGS = 100;
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
        Prescription bookings[MAX_BOOKINGS];    
        int numBookings;
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
    if (numBookings >= MAX_BOOKINGS) {
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
    bookings[numBookings].PrescriptionID = PrescriptionID;
    bookings[numBookings].Dosage = Dosage;
    numBookings++;

    cout << "Booking created successfully.\n";
}

/**
 * @brief Displays all existing bookings in a tabular format.
 */
void PrescriptionManager::displayAll() {
    if (numBookings == 0) {
        cout << "No prescription available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "| Prescription ID | Dosage  |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numBookings; i++) {
        cout << "| " << setw(10) << bookings[i].PrescriptionID << " | "
             << setw(13) << bookings[i].Dosage << " | \n";
    }
    cout << "------------------------------------------------\n";
}

/**
 * @brief Finds the index of a booking by ID.
 * @param id Booking ID to search for.
 * @return Index of the booking if found, -1 otherwise.
 */
int PrescriptionManager::findIndexById(int id) {
    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].PrescriptionID == id) {
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

    cout << "Current Details - Dosage : " << bookings[index].Dosage << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> bookings[index].Dosage;

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
    for (int i = index; i < numBookings - 1; i++) {
        bookings[i] = bookings[i + 1];
    }
    numBookings--;

    cout << " deleted successfully.\n";
}

PrescriptionManager::PrescriptionManager() {
    numBookings = 0;
}
// *****Menu.cpp*****
void printMenu() {
    cout << "\n=== Prescription Management System ===\n";
    cout << "1. Create Booking\n";
    cout << "2. Display All Bookings\n";
    cout << "3. Edit Booking\n";
    cout << "4. Delete Booking\n";
    cout << "5. Exit\n";
}