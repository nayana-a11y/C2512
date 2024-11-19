/*
    Title: Railway Ticket Booking Management System

    The fields are:
    1. Booking ID -> bookingId[]
    2. Ticket Amount -> ticketAmounts[]
    3. Food Amount -> foodAmount[]

    Implement a counter to tract the number of customer booking 

    Max array size: 1000

    Operations required(menu-driven):
        C-> Create
        R-> Read
        U-> Update
        D-> Delete

    Create:
    When option 1 is given 
    add edit the 3 arrays
    ensure max limit is not exceeded

    Read: -> 
    Based on given input customerId

    Update:
    Based on given input customerId
    then edit all values
    implement left shift

    Delete:
    Based on given input customerId
    implement left shift

    counter=0
    bookingId[]


    Functions:



    ifExist(id,bookingId[]){                                            -> Bhagya
        check if id in bookingId[]
            return index
        return -1
    }

    createBookingTicket(bookingId[],ticketAmounts[], foodAmount[]){     -> Dhaheen
        enter bookingid
        if ((isExist(id)!=-1))&&(counter<1000)
            enter remaining fields
        else not unique
        increment counter

        display appropriate message in each case
    }

    displayBooking(bookingId[],ticketAmounts[], foodAmount[]){          -> Pitchumani
        print the arrays in a tabular form
    }

    editBooking(bookingId[],ticketAmounts[], foodAmount[]){             -> Nayana
        enter id
        if (isExist(id)!=-1){
            edit the arrays except bookingId
        }

        display appropriate message in each case
    }

    deleteBooking(bookingId[],ticketAmounts[], foodAmount[]){           -> Josh
        enter id
        if (isExist(id)!=-1){
            delete all records from [i]th index of all arrays
            implement left shift
            decrement counter
        }

        display appropriate message in each case
    }

*/

#include <iostream>
using namespace std;

// Constants
const int MAX_SIZE = 100;

// Function Prototypes
int ifExist(int id, int bookingId[], int counter);
void createBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &bookingsCounter);
void editBooking(int bookingId[], int ticketAmount[], int foodAmount[], int counter);
void deleteBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &counter);
void displayBooking(int bookingId[], int ticketAmount[], int foodAmounts[], int size);
void printMenu();

// Ensure booking ID is unique
int ifExist(int id, int bookingId[], int counter) {
	for (int i = 0; i < counter; i++) {
		if (bookingId[i] == id) {
			return i;
		}
	}
	return -1;
}

/**
 * @brief Creates a new booking.
 * @param bookingId Array of booking IDs.
 * @param ticketAmount Array of ticket amounts.
 * @param foodAmount Array of food amounts.
 * @param bookingsCounter Current number of bookings.
 */
void createBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &bookingsCounter) {

    // Checking whether the booking limit is exceeeded
	if (bookingsCounter >= MAX_SIZE) {                           
		cout << "Booking Limit exceeded!";
		return;
	}

	int id;

	cout << "Enter Booking Id: ";
	cin >> id;
    // Checking if the id is a positive value
	if (id>0) {           
        // Checking if the entered id is already existing                                      
		if(ifExist(id, bookingId, bookingsCounter) == -1 ) {    
			int amountOfTicket,amountOfFood;

            // Read the ticket amount and food amount once the id is validated
			cout << "Enter Ticket amount: ";                    
			cin >> amountOfTicket;
			cout << "Enter Food amount: ";
			cin >> amountOfFood;

            // Insert the values to each array
			bookingId[bookingsCounter] = id;                    
			ticketAmount[bookingsCounter] = amountOfTicket;
			foodAmount[bookingsCounter] = amountOfFood;

			cout << "Booking added successfully..";            

			bookingsCounter++ ;                                 
		}
		else {
			cout << "Booking Id already exists!";               
		}
	}
	else {
		cout << "Enter valid Booking ID.";
	}
	cout << "\n";
}

/**
 * @brief Edits an existing booking by ID.
 * @param bookingIds Array of booking IDs.
 * @param ticketAmounts Array of ticket amounts.
 * @param foodAmounts Array of food amounts.
 * @param counter Current number of bookings.
 */
void editBooking(int bookingId[], int ticketAmount[], int foodAmount[], int counter) {
	if (counter==0) {
		cout << "No data to be found.\n";
		return ;
	}
	int id;
	cout << "Enter the Booking Id: ";
	cin >> id;

	// Checks the bookingId exists
	int i = ifExist(id, bookingId, counter);
	if (i!=-1) {


		// Input new values
		cout << "Current Ticket Amount: " << ticketAmount[i]<< endl;
		cout << "Current Food Amount: " << foodAmount[i]<< endl;

		cout << "Enter new Ticket Amount: ";
		cin >> ticketAmount[i];
		cout << "Enter new Food Amount: ";
		cin >> foodAmount[i];

		cout << "Booking updated successfully ";

	}

	else {
		cout << "Booking id does not exists.";
	}
	cout << "\n";
}

/**
 * @brief Deletes an existing booking by ID.
 * @param bookingId Array of booking IDs.
 * @param ticketAmount Array of ticket amounts.
 * @param foodAmount Array of food amounts.
 * @param counter Current number of bookings.
 */
void deleteBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &counter) {

    // Check if there are any bookings
	if (counter==0) {
		cout << "No data to be found.\n";
		return ;
	}

	int id;
	cout << "Enter BookingID: ";
	cin >> id;

    // Check if entered Booking ID exists in the Booking array
	int index = ifExist(id, bookingId, counter);
	if (index != -1) {
        
        // Left shift
		for (int i = index; i < counter; i++) {
			bookingId[i] = bookingId[i + 1];
			ticketAmount[i] =ticketAmount[i + 1];
			foodAmount[i] = foodAmount[i + 1];
		}

        // Decrement counter
		counter--;
		
        cout << "Data for the BookingId: " << id << " has been removed." << endl;
	}

	else {
		cout << "Enter Valid BookingID";
	}
	cout << "\n";
}

/**
 * @brief Display an existing booking by ID.
 * @param bookingId Array of booking IDs.
 * @param ticketAmount Array of ticket amounts.
 * @param foodAmounts Array of food amounts.
 * @param size Current number of bookings.
 */
void displayBooking(int bookingId[], int ticketAmount[], int foodAmounts[], int size) {
    // Check if there is data to display
    if (size > 0) {
        // Print the column headers for the table
        cout << "Booking ID\t" << "Ticket Amount\t" << "Food Amount\t\n" << endl;

        // Loop through each booking entry and display its details
        for (int i = 0; i < size; i++) {
             // Display the Booking ID, Ticket Amount, Food Amount
            cout << bookingId[i] << "\t\t"   
                 << ticketAmount[i] << "\t\t" 
                 << foodAmounts[i] << "\n"    
                 << endl;
        }
    } else {
        // If there is no data, inform the user
        cout << "No data to be retrieved.";
    }

    // Print a newline for better readability
    cout << "\n";
}

/** 
 * @brief Prints the menu options to the console.
 */
void printMenu() {
	cout << "Menu:\n";
	cout << "1. Create Booking\n";
	cout << "2. Display All Bookings\n";
	cout << "3. Edit Booking\n";
	cout << "4. Delete Booking\n";
	cout << "5. Exit\n";
}

int main() {
	cout << "\n=== Railway Ticket Booking Management System ===\n";

	// Arrays to hold booking details
	int bookingId[MAX_SIZE] = {0};
	int ticketAmount[MAX_SIZE] = {0};
	int foodAmount[MAX_SIZE] = {0};

	int numBookings = 0; // Counter for current bookings

	int choice; // User's menu choice

	do {
		printMenu(); // Display menu
		cout<<"\n";
		cout << "Enter your choice: ";
		cin >> choice;

		// Menu-driven functionality
		switch (choice) {
		case 1:
			cout << "\n";
			createBooking(bookingId, ticketAmount, foodAmount, numBookings);
			cout << "\n";
			break;
		case 2:
			cout << "\n";
			displayBooking(bookingId, ticketAmount, foodAmount, numBookings);
			cout << "\n";
			break;
		case 3:
			cout << "\n";
			editBooking(bookingId, ticketAmount, foodAmount, numBookings);
			cout << "\n";
			break;
		case 4:
			cout << "\n";
			deleteBooking(bookingId, ticketAmount, foodAmount, numBookings);
			cout << "\n";
			break;
		case 5:
			cout << "\n";
			cout << "Exiting the system. Goodbye!\n";
			break;
		default:
			cout << "Invalid choice. Please enter a number between 1 and 5.\n\n";
		}
	} while (choice != 5);

	return 0;
}
