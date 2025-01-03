#include <iostream>
#include "Patient.h"
#include "DataValidator.h"

using namespace std;

Patient::Patient(const string &name, const string &phone, const string &email, const string &password)
    : User(name, phone, email, password) {}

void Patient::createAppointment(const string &date, int doctorID, const string &timeSlot)
{
    // To check if the appointment is not already booked
    for (const auto &appointment : appointments)
    {
        if (appointment.date == date && appointment.timeSlot == timeSlot && appointment.doctorID == doctorID)
        {
            cout << "\nThe selected time slot is already booked. Please choose another time slot." << endl;
            return;
        }
    }

    Appointment newAppointment = {doctorID, date, timeSlot};
    appointments.push_back(newAppointment);
    cout << "Appointment created successfully with doctor ID: " << doctorID << " at " << timeSlot << " on " << date << endl;
}

void Patient::showAppointments(const vector<json> &doctors) const
{
    cout << "\n####### Showing appointments for patient " << name << " #######" << endl;
    for (size_t i = 0; i < appointments.size(); i++)
    {
        const auto &appointment = appointments[i];
        string doctorName;
        for (const auto &doctor : doctors)
        {
            if (doctor["ID"] == appointment.doctorID)
            {
                doctorName = doctor["Name"];
                break;
            }
        }
        cout << "\n"
             << i + 1 << ". Doctor: " << doctorName << ", Date: " << appointment.date << ", Time Slot: " << appointment.timeSlot << endl;
    }
}

void Patient::cancelAppointment(int appointmentIndex, vector<json> &doctors)
{
    auto appointment = appointments[appointmentIndex];
    for (auto &doctor : doctors)
    {
        if (doctor["ID"] == appointment.doctorID)
        {
            doctor["Appointments"][appointment.date][appointment.timeSlot] = true;
            break;
        }
    }

    appointments.erase(appointments.begin() + appointmentIndex);
    cout << "\nAppointment canceled successfully." << endl;
}

void Patient::updateDetails()
{
    DataValidator validator;
    cout << "\n########################################################" << endl;
    cout << "#########       Updating Patient Details       #########" << endl;
    cout << "########################################################" << endl;

    cout << "\nter new name: ";
    // Clear the input buffer
    cin.ignore();
    getline(cin, name);

    do
    {
        cout << "\nEnter new phone number: ";
        getline(cin, phone);
        if (!validator.validatePhone(phone))
        {
            cout << "\nInvalid phone number. Please enter a valid phone number." << endl;
        }
    } while (!validator.validatePhone(phone));

    do
    {
        cout << "\nEnter new email address: ";
        getline(cin, email);
        if (!validator.validateEmail(email))
        {
            cout << "\nInvalid email address. Please enter a valid email address." << endl;
        }
    } while (!validator.validateEmail(email));

    cout << "\nEnter new password: ";
    getline(cin, password);

    cout << "\nPatient details updated successfully." << endl;
}