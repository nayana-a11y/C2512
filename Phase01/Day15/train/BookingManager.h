#pragma once
// Function Prototypes
int isExist(int id, int bookingId[], int counter);
void createBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &bookingsCounter);
void editBooking(int bookingId[], int ticketAmount[], int foodAmount[], int counter);
void deleteBooking(int bookingId[], int ticketAmount[], int foodAmount[], int &counter);
void displayBooking(int bookingId[], int ticketAmount[], int foodAmounts[], int size);