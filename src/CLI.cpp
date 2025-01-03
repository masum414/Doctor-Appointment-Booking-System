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

void CLI::displayLoginMenu()
{
    clearScreen();
    string email, password;
    cout << "\n########################################################" << endl;
    cout << "#########            Patient Login             #########" << endl;
    cout << "########################################################" << endl;
    cout << "\nEnter email: ";
    cin >> email;
    cout << "\nEnter password: ";
    cin >> password;

    for (auto &patient : patients)
    {
        if (patient.email == email && patient.password == password)
        {
            cout << "\nLogin successful. Welcome, " << patient.name << "!" << endl;
            displayPatientMenu(patient);
            return;
        }
    }
    cout << "\nInvalid email or password. Please try again." << endl;
    displayMainMenu();
}

void CLI::displayRegisterMenu()
{
    clearScreen();
    string name, phone, email, password;
    DataValidator validator;

    cout << "\n########################################################" << endl;
    cout << "#########         Patient Registration         #########" << endl;
    cout << "########################################################" << endl;
    cout << "\nEnter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    do
    {
        cout << "\nEnter phone number: ";
        getline(cin, phone);
        if (!validator.validatePhone(phone))
        {
            cout << "\nInvalid phone number. Please enter a valid phone number." << endl;
        }
    } while (!validator.validatePhone(phone));

    do
    {
        cout << "\nEnter email address: ";
        getline(cin, email);
        if (!validator.validateEmail(email))
        {
            cout << "\nInvalid email address. Please enter a valid email address." << endl;
        }
    } while (!validator.validateEmail(email));

    cout << "\nEnter password: ";
    getline(cin, password);

    patients.push_back(Patient(name, phone, email, password));
    cout << "\nPatient registered successfully." << endl;
    displayMainMenu();
}