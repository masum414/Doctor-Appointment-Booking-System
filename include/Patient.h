#ifndef PATIENT_H
#define PATIENT_H

#include <vector>
#include <json.hpp>
#include "User.h"

using namespace std;
using json = nlohmann::json;

class Patient : public User
{
public:
    struct Appointment
    {
        int doctorID;
        string date;
        string timeSlot;
    };

    vector<Appointment> appointments;

    Patient(const string &name, const string &phone, const string &email, const string &password);

    // To create an appointment
    void createAppointment(const string &date, int doctorID, const string &timeSlot);

    // To show appointments for the patient
    void showAppointments(const vector<json> &doctors) const;

    // To cancel an appointment
    void cancelAppointment(int appointmentIndex, vector<json> &doctors);

    // To update patient details
    void updateDetails() override;
};

#endif