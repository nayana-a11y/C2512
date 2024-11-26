#include <iostream>
#include "BookingManager.h"
#include "Menu.h"
#include "Constants.h"

using namespace std;


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