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
        int PrescriptionID;
        int Dosage;
    public:
        bool GreaterThan(const Prescription& other);
        bool LessThan(const Prescription& other);
         //getters-setters
        int GetPrescriptionID();
        int GetDosage();
};
// *****PrescriptionManager.h*****
class PrescriptionManager {
    friend class PrescriptionAggregator;
    friend int main();
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
//*****PrescriptionAggregator.h*****
class PrescriptionAggregator {
    public:
        int findMin(PrescriptionManager& manager);
        int findMax(PrescriptionManager& manager);
        int findSecondMin(PrescriptionManager& manager);
        int findSecondMax(PrescriptionManager& manager);
};
// *****Menu.h*****
void printMenu();

// *****Main.cpp*****

int main() {
    PrescriptionManager manager;
    PrescriptionAggregator aggregator;
   
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
                std::cout << "Prescription with Min Dosage: " 
                    << manager.Dosages[aggregator.findMin(manager)].GetPrescriptionID() 
                    << " with Dosage " 
                    << manager.Dosages[aggregator.findMin(manager)].GetDosage() 
                    << std::endl;
                break;
            case 6: 
                std::cout << "Prescription with Max Dosage: " 
                    << manager.Dosages[aggregator.findMax(manager)].GetPrescriptionID() 
                    << " with Dosage " 
                    << manager.Dosages[aggregator.findMax(manager)].GetDosage() 
                    << std::endl;
                break;
            case 7: 
                std::cout << "Prescription with 2nd Min Dosage: " 
                    << manager.Dosages[aggregator.findSecondMin(manager)].GetPrescriptionID() 
                    << " with Dosage " 
                    << manager.Dosages[aggregator.findSecondMin(manager)].GetDosage() 
                    << std::endl;
                break;
            case 8: 
                std::cout << "Prescription with 2nd Max Dosage: " 
                    << manager.Dosages[aggregator.findSecondMax(manager)].GetPrescriptionID() 
                    << " with Dosage " 
                    << manager.Dosages[aggregator.findSecondMax(manager)].GetDosage() 
                    << std::endl;
                break;
            case 9:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 9);

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

    // Ensure Prescription ID is unique
    if (findIndexById(PrescriptionID) != -1) {
        cout << "Error: Prescription ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter Dosage: ";
    cin >> Dosage;

    // Store the details
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
 * @brief Finds the index of a Dosages by ID.
 * @param id Prescription ID to search for.
 * @return Index of the Dosages if found, -1 otherwise.
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
 * @brief Edits an existing Dosage by ID.
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

    cout << "Current Details - : " << Dosages[index].Dosage << "\n";

    cout << "Enter New Dosage Amount: ";
    cin >> Dosages[index].Dosage;

    cout << "Dosage updated successfully.\n";
}

/**
 * @brief Deletes an existing Dosages by ID.
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

    cout << " Dosage Deleted successfully.\n";
}

PrescriptionManager::PrescriptionManager() {
    numDosages = 0;
}
// *****Menu.cpp*****
void printMenu() {
    cout << "\n=== Prescription Management System ===\n";
    cout << "1. Create \n";
    cout << "2. Display All \n";
    cout << "3. Edit Prescription\n";
    cout << "4. Delete Prescription\n";
    cout << "5. Find Min Dosage\n";
    cout << "6. Find Max Dosage\n";
    cout << "7. Find Second Min Dosage\n";
    cout << "8. Find Second Max Dosage\n";
    cout << "9. Exit\n";

}

//*****Prescription.cpp*****
bool Prescription::GreaterThan(const Prescription& other)
{
    return (Dosage > other.Dosage);
}

bool Prescription::LessThan(const Prescription& other)
{
    return (Dosage < other.Dosage);
}

//getters-setters
int Prescription::GetPrescriptionID()
{
    return PrescriptionID;
}
int Prescription::GetDosage()
{
    return Dosage;
}
//*****PrescriptionAggregator.cpp*****
// Function to find the index of the Prescription with the minimum dosage
int PrescriptionAggregator::findMin(PrescriptionManager& manager) {
    Prescription* arr = manager.Dosages;
    int& n = manager.numDosages;
    //
    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].LessThan(arr[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to find the index of the Prescription with the maximum dosage
int PrescriptionAggregator::findMax(PrescriptionManager& manager) {
    Prescription* arr = manager.Dosages;
    int& n = manager.numDosages;
    //
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].GreaterThan(arr[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to find the index of the Prescription with the second minimum dosage
int PrescriptionAggregator::findSecondMin(PrescriptionManager& manager) {
    Prescription* arr = manager.Dosages;
    int& n = manager.numDosages;
    //
    int minIndex = findMin(manager);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;
    
    for (int i = 0; i < n; ++i) {
        if (i != minIndex) {
            if (arr[i].LessThan(arr[secondMinIndex])) {
                secondMinIndex = i;
            }
        }
    }
    return secondMinIndex;
}

// Function to find the index of the Prescription with the second maximum dosage
int PrescriptionAggregator::findSecondMax(PrescriptionManager& manager) {
    Prescription* arr = manager.Dosages;
    int& n = manager.numDosages;
    //
    int maxIndex = findMax(manager);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;
    
    for (int i = 0; i < n; ++i) {
        if (i != maxIndex) {
            if (arr[i].GreaterThan(arr[secondMaxIndex])) {
                secondMaxIndex = i;
            }
        }
    }
    return secondMaxIndex;
}
