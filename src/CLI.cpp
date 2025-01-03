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

void CLI::displayPatientMenu(Patient &patient)
{
    clearScreen();
    int choice;
    cout << "\n########################################################" << endl;
    cout << "#########            Patient Menu              #########" << endl;
    cout << "########################################################" << endl;
    cout << "\n1. Create Appointment" << endl;
    cout << "\n2. Show Appointments" << endl;
    cout << "\n3. Cancel Appointment" << endl;
    cout << "\n4. Update User Info" << endl;
    cout << "\n5. Logout" << endl;
    cout << "\nEnter your choice: ";
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
        createPatientAppointment(patient);
        break;
    case 2:
        showPatientAppointments(patient);
        break;
    case 3:
        cancelPatientAppointment(patient);
        break;
    case 4:
        updatePatientInfo(patient);
        break;
    case 5:
        displayMainMenu();
        break;
    default:
        cout << "\nInvalid choice. Please try again." << endl;
        displayPatientMenu(patient);
        break;
    }
}

void CLI::createPatientAppointment(Patient &patient)
{
    clearScreen();
    string date, timeSlot;
    int doctorIndex;

    cout << "\n####### Available Doctors:" << endl;
    for (size_t i = 0; i < doctors.size(); ++i)
    {
        const auto &doctor = doctors[i];
        cout << "\n"
             << i + 1 << ". Doctor ID: " << doctor["ID"] << ", Name: " << doctor["Name"] << ", Specialization: " << doctor["Specialization"] << endl;
    }

    cout << "\nEnter the serial number of the doctor (or 0 to go back): ";
    while (!(cin >> doctorIndex) || doctorIndex < 0 || static_cast<size_t>(doctorIndex) > doctors.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter a valid number: ";
    }
    if (doctorIndex == 0)
    {
        displayPatientMenu(patient);
        return;
    }
    // Convert to zero-based index
    doctorIndex--;

    const auto &doctor = doctors[doctorIndex];

    cout << "\n####### Available Dates:" << endl;
    vector<string> availableDates;
    for (const auto &dateEntry : doctor["Appointments"].items())
    {
        availableDates.push_back(dateEntry.key());
        cout << "\n"
             << availableDates.size() << ". " << dateEntry.key() << endl;
    }

    int dateIndex;
    cout << "\nEnter the serial number of the date (or 0 to go back): ";
    while (!(cin >> dateIndex) || dateIndex < 0 || static_cast<size_t>(dateIndex) > availableDates.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter a valid number: ";
    }
    if (dateIndex == 0)
    {
        displayPatientMenu(patient);
        return;
    }
    // Convert to zero-based index
    date = availableDates[dateIndex - 1];

    cout << "\n####### Available Time Slots:" << endl;
    vector<string> availableTimeSlots;
    for (const auto &slot : doctor["Appointments"][date].items())
    {
        availableTimeSlots.push_back(slot.key());
        cout << "\n"
             << availableTimeSlots.size() << ". " << slot.key() << " - " << (slot.value() ? "Not Booked" : "Booked") << endl;
    }

    int timeSlotIndex;
    cout << "\nEnter the serial number of the time slot (or 0 to go back): ";
    while (!(cin >> timeSlotIndex) || timeSlotIndex < 0 || static_cast<size_t>(timeSlotIndex) > availableTimeSlots.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter a valid number: ";
    }
    if (timeSlotIndex == 0)
    {
        displayPatientMenu(patient);
        return;
    }
    // Convert to zero-based index
    timeSlot = availableTimeSlots[timeSlotIndex - 1];

    // Check if the selected time slot is available
    if (!doctor["Appointments"][date][timeSlot])
    {
        cout << "\nThe selected time slot is already booked. Please choose another time slot." << endl;
        createPatientAppointment(patient);
        return;
    }

    // Mark the time slot as booked
    for (auto &doc : doctors)
    {
        if (doc["ID"] == doctor["ID"])
        {
            doc["Appointments"][date][timeSlot] = false;
            break;
        }
    }

    // Create the appointment
    patient.createAppointment(date, doctor["ID"], timeSlot);
    jsonHandler.savePatients(patients);
    jsonHandler.saveDoctors(doctors);
    displayPatientMenu(patient);
}

void CLI::showPatientAppointments(Patient &patient)
{
    clearScreen();
    patient.showAppointments(doctors);
    cout << "\nEnter 0 to go back: ";
    int choice;
    while (!(cin >> choice) || choice != 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter 0 to go back: ";
    }
    displayPatientMenu(patient);
}

void CLI::cancelPatientAppointment(Patient &patient)
{
    clearScreen();
    patient.showAppointments(doctors);
    int appointmentIndex;
    cout << "\nEnter the serial number of the appointment to cancel (or 0 to go back): ";
    while (!(cin >> appointmentIndex) || appointmentIndex < 0 || static_cast<size_t>(appointmentIndex) > patient.appointments.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid choice. Please enter a valid number: ";
    }
    if (appointmentIndex == 0)
    {
        displayPatientMenu(patient);
        return;
    }
    // Convert to zero-based index
    appointmentIndex--;

    patient.cancelAppointment(appointmentIndex, doctors);
    jsonHandler.savePatients(patients);
    jsonHandler.saveDoctors(doctors);
    displayPatientMenu(patient);
}

void CLI::updatePatientInfo(Patient &patient)
{
    clearScreen();
    patient.updateDetails();
    jsonHandler.savePatients(patients);
    displayPatientMenu(patient);
}