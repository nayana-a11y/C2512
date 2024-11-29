#include <iostream>
#include <iomanip>

using namespace std;

// *****Const.h*****
// Constants
const int MAX_HOSPITAL_STAYS = 100;
// *****HospitalStay.h*****
class HospitalStay {
    friend class HospitalStayManager;
    private:
        string StayID;
        int NumberOfDays;
    public:
        bool GreaterThan(const HospitalStay& other);
        bool LessThan(const HospitalStay& other);
         //getters-setters
        string GetStayID();
        int GetNumberOfDays();
};
// *****HospitalStayManager.h*****
class HospitalStayManager {
    friend class HospitalStayAggregator;
    friend int main();
    private:
        // attributes
        HospitalStay stays[MAX_HOSPITAL_STAYS];    
        int numHospitalStays;
    public:
        // support
        int findIndexById(string StayID);
        // behaviours
        void create();
        void displayAll();
        void editById();
        void deleteById();
        //
        HospitalStayManager();
};
//*****HospitalStayAggregator.h*****
class HospitalStayAggregator {
    public:
        int findMin(HospitalStayManager& manager);
        int findMax(HospitalStayManager& manager);
        int findSecondMin(HospitalStayManager& manager);
        int findSecondMax(HospitalStayManager& manager);
};
// *****Menu.h*****
void printMenu();

// *****Main.cpp*****

int main() {
    HospitalStayManager manager;
    HospitalStayAggregator aggregator;
   
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
                std::cout << "HospitalStay with Min Stay: " 
                    << manager.stays[aggregator.findMin(manager)].GetStayID() 
                    << " with NumberOfDays " 
                    << manager.stays[aggregator.findMin(manager)].GetNumberOfDays() 
                    << std::endl;
                break;
            case 6: 
                std::cout << "HospitalStay with Max Stay: " 
                    << manager.stays[aggregator.findMax(manager)].GetStayID() 
                    << " with NumberOfDays " 
                    << manager.stays[aggregator.findMax(manager)].GetNumberOfDays() 
                    << std::endl;
                break;
            case 7: 
                std::cout << "HospitalStay with 2nd Min Stay: " 
                    << manager.stays[aggregator.findSecondMin(manager)].GetStayID() 
                    << " with NumberOfDays " 
                    << manager.stays[aggregator.findSecondMin(manager)].GetNumberOfDays() 
                    << std::endl;
                break;
            case 8: 
                std::cout << "HospitalStay with 2nd Max Stay: " 
                    << manager.stays[aggregator.findSecondMax(manager)].GetStayID() 
                    << " with NumberOfDays " 
                    << manager.stays[aggregator.findSecondMax(manager)].GetNumberOfDays() 
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

// *****HospitalStayManager.cpp*****
/**
 * @brief Creates a new hospital stay and stores details in arrays. 
 */
void HospitalStayManager::create() {
    if (numHospitalStays >= MAX_HOSPITAL_STAYS) {
        cout << "Error: Maximum hospital stay limit reached.\n";
        return;
    }

    string StayID;
    int NumberOfDays;

    cout << "Enter HospitalStay STAYID: ";
    cin >> StayID;

    // Ensure hospital stay STAYID is unique
    if (findIndexById(StayID) != -1) {
        cout << "Error: HospitalStay STAYID already exists. Please use a unique STAYID.\n";
        return;
    }

    cout << "Enter Number Of Days: ";
    cin >> NumberOfDays;

    // Store the hospital stay details
    stays[numHospitalStays].StayID = StayID;
    stays[numHospitalStays].NumberOfDays = NumberOfDays;
    numHospitalStays++;

    cout << "HospitalStay created successfully.\n";
}

/**
 * @brief Displays all existing stays in a tabular format.
 */
void HospitalStayManager::displayAll() {
    if (numHospitalStays == 0) {
        cout << "No stays available to display.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   STAYID | Number Of Days                    |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numHospitalStays; i++) {
        cout << "| " << setw(10) << stays[i].StayID << " | "
             << setw(13) << stays[i].NumberOfDays << " |\n";
    }
    cout << "------------------------------------------------\n";
}

/**
 * @brief Finds the index of a hospital stay by STAYID.
 * @param StayID HospitalStay STAYID to search for.
 * @return Index of the hospital stay if found, -1 otherwise.
 */
int HospitalStayManager::findIndexById(string StayID) {
    for (int i = 0; i < numHospitalStays; i++) {
        if (stays[i].StayID == StayID) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Edits an existing hospital stay by STAYID.
 */
void HospitalStayManager::editById() {
    string StayID;
    cout << "Enter HospitalStay STAYID to edit: ";
    cin >> StayID;

    int index = findIndexById(StayID);
    if (index == -1) {
        cout << "Error: HospitalStay STAYID not found.\n";
        return;
    }

    cout << "Current Details - Number Of Days: " << stays[index].NumberOfDays << "\n";

    cout << "Enter New Number Of Days: ";
    cin >> stays[index].NumberOfDays;

    cout << "HospitalStay updated successfully.\n";
}

/**
 * @brief Deletes an existing hospital stay by STAYID.
 */
void HospitalStayManager::deleteById() {
    string StayID;
    cout << "Enter HospitalStay STAYID to delete: ";
    cin >> StayID;

    int index = findIndexById(StayID);
    if (index == -1) {
        cout << "Error: HospitalStay STAYID not found.\n";
        return;
    }

    // Shift data to fill the gap
    for (int i = index; i < numHospitalStays - 1; i++) {
        stays[i] = stays[i + 1];
    }
    numHospitalStays--;

    cout << "HospitalStay deleted successfully.\n";
}

HospitalStayManager::HospitalStayManager() {
    numHospitalStays = 0;
}
// *****Menu.cpp*****
void printMenu() {
    cout << "\n=== Hospital Stay Management Module ===\n";
    cout << "1. Create Hospital Stay\n";
    cout << "2. Display All Hospital Stays\n";
    cout << "3. Edit Hospital Stay\n";
    cout << "4. Delete Hospital Stay\n";
    cout << "5. Find Min Stay\n";
    cout << "6. Find Max Stay\n";
    cout << "7. Find Second Min Stay\n";
    cout << "8. Find Second Max Stay\n";
    cout << "9. Exit\n";
}

//*****HospitalStay.cpp*****
bool HospitalStay::GreaterThan(const HospitalStay& other)
{
    return (NumberOfDays > other.NumberOfDays);
}

bool HospitalStay::LessThan(const HospitalStay& other)
{
    return (NumberOfDays < other.NumberOfDays);
}

//getters-setters
string HospitalStay::GetStayID()
{
    return StayID;
}
int HospitalStay::GetNumberOfDays()
{
    return NumberOfDays;
}
//*****HospitalStayAggregator.cpp*****
// Function to find the index of the HospitalStay with the minimum years of Stay
int HospitalStayAggregator::findMin(HospitalStayManager& manager) {
    HospitalStay* arr = manager.stays;
    int& n = manager.numHospitalStays;
    //
    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].LessThan(arr[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to find the index of the HospitalStay with the maximum years of Stay
int HospitalStayAggregator::findMax(HospitalStayManager& manager) {
    HospitalStay* arr = manager.stays;
    int& n = manager.numHospitalStays;
    //
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i].GreaterThan(arr[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to find the index of the HospitalStay with the second minimum years of Stay
int HospitalStayAggregator::findSecondMin(HospitalStayManager& manager) {
    HospitalStay* arr = manager.stays;
    int& n = manager.numHospitalStays;
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

// Function to find the index of the HospitalStay with the second maximum years of Stay
int HospitalStayAggregator::findSecondMax(HospitalStayManager& manager) {
    HospitalStay* arr = manager.stays;
    int& n = manager.numHospitalStays;
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