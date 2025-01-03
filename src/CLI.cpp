#include <iostream>
#include <limits>
#include <cstdlib>
#include "CLI.h"
#include "DataValidator.h"

using namespace std;

CLI::CLI(vector<Patient> &patients, vector<json> &doctors, JsonHandler &jsonHandler)
    : patients(patients), doctors(doctors), jsonHandler(jsonHandler) {}

// To clear console screen on Windows
void CLI::clearScreen()
{
    system("cls");
}

void CLI::displayMainMenu()
{
    clearScreen();
    int choice;
    cout << "########################################################" << endl;
    cout << "#######                                           ######" << endl;
    cout << "#######               W E L C O M E               ######" << endl;
    cout << "#######                    T O                    ######" << endl;
    cout << "#######     DOCTOR APPOINTMENT BOOKING SYSTEM     ######" << endl;
    cout << "#######                                           ######" << endl;
    cout << "########################################################" << endl;
    cout << "********************** Main Menu ***********************" << endl;

    cout << "\n1. Login" << endl;
    cout << "\n2. Register" << endl;
    cout << "\n3. Exit" << endl;
    cout << "\nTo get started, enter your choice: ";
    cin >> choice;
    while (!choice)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter a number: ";
    }

    switch (choice)
    {
    case 1:
        displayLoginMenu();
        break;
    case 2:
        displayRegisterMenu();
        break;
    case 3:
        cout << "\n########################################################" << endl;
        cout << "#########  Exiting the Application, Good Bye!  #########" << endl;
        cout << "########################################################" << endl;
        // Save data to JSON files before exiting
        jsonHandler.savePatients(patients);
        jsonHandler.saveDoctors(doctors);
        break;
    default:
        cout << "\nInvalid choice. Please try again." << endl;
        displayMainMenu();
        break;
    }
}