#include <fstream>
#include "JsonHandler.h"

using namespace std;
using json = nlohmann::json;

// Load doctors data from JSON file
void JsonHandler::loadDoctors(vector<json> &doctors)
{
    ifstream inFile("data/doctors.json");
    if (inFile.is_open())
    {
        json j;
        inFile >> j;
        doctors = j.get<vector<json>>();
        inFile.close();
    }
}

// Save doctors data to JSON file
void JsonHandler::saveDoctors(const vector<json> &doctors)
{
    ofstream outFile("data/doctors.json");
    if (outFile.is_open())
    {
        json j = doctors;
        outFile << j.dump(4);
        outFile.close();
    }
}

// Load patients data from JSON file
void JsonHandler::loadPatients(vector<Patient> &patients)
{
    ifstream inFile("data/patients.json");
    if (inFile.is_open())
    {
        json j;
        inFile >> j;
        for (const auto &item : j)
        {
            int id = item["ID"];
            string name = item["Name"];
            string email = item["Email"];
            string phone = item["Phone"];
            string password = item["Password"];
            vector<Patient::Appointment> appointments;
            for (const auto &appointment : item["Appointments"])
            {
                int doctorID = appointment["DoctorID"];
                string date = appointment["Date"];
                string timeSlot = appointment["TimeSlot"];
                appointments.push_back({doctorID, date, timeSlot});
            }
            patients.push_back(Patient(name, phone, email, password));
            patients.back().id = id;
            patients.back().appointments = appointments;
        }
        inFile.close();
    }
}

// Save patients data to JSON file
void JsonHandler::savePatients(const vector<Patient> &patients)
{
    ofstream outFile("data/patients.json");
    if (outFile.is_open())
    {
        json j;
        for (const auto &patient : patients)
        {
            json item;
            item["ID"] = patient.id;
            item["Name"] = patient.name;
            item["Email"] = patient.email;
            item["Phone"] = patient.phone;
            item["Password"] = patient.password;
            json appointmentsJson;
            for (const auto &appointment : patient.appointments)
            {
                json appointmentJson;
                appointmentJson["DoctorID"] = appointment.doctorID;
                appointmentJson["Date"] = appointment.date;
                appointmentJson["TimeSlot"] = appointment.timeSlot;
                appointmentsJson.push_back(appointmentJson);
            }
            item["Appointments"] = appointmentsJson;
            j.push_back(item);
        }
        outFile << j.dump(4);
        outFile.close();
    }
}