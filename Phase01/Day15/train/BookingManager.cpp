#include <iostream>
#include "BookingManager.h"
#include "Constants.h"

using namespace std;

// Ensure booking ID is unique
int isExist(int id, int bookingId[], int counter) {
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
		if(isExist(id, bookingId, bookingsCounter) == -1 ) {    
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
	cout << "\n";
}

/**
 * @brief Edits an existing booking by ID.
 * @param bookingIds Array of booking IDs.
 * @param ticketAmounts Array of ticket amounts.
 * @param foodAmounts Array of food amounts.
 * @param counter Current number of bookings.
 */
void editBooking(int bookingId[], int ticketAmount[], int foodAmount[], int counter) {
	if (counter == 0) {
		cout << "No data to be found.\n";
		return ;
	}
	
	int id;
	cout << "Enter the Booking Id: ";
	cin >> id;

	// Checks the bookingId exists
	int i = isExist(id, bookingId, counter);
	if (i != -1) {


		// Input new values
		cout << "Current Ticket Amount: " << ticketAmount[i] << endl;
		cout << "Current Food Amount: " << foodAmount[i] << endl;

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
	int index = isExist(id, bookingId, counter);
	if (index != -1) {
        
        // Left shift
		for (int i = index; i < counter - 1; i++) {
		    
			bookingId[i] = bookingId[i + 1];
			ticketAmount[i] = ticketAmount[i + 1];
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