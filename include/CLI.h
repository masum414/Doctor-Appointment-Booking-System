#ifndef CLI_H
#define CLI_H

#include <vector>
#include <json.hpp>
#include "Patient.h"
#include "JsonHandler.h"

using namespace std;
using json = nlohmann::json;

class CLI
{
private:
    vector<Patient> &patients;
    vector<json> &doctors;
    JsonHandler &jsonHandler;

    // To clear the console
    void clearScreen();

public:
    CLI(vector<Patient> &patients, vector<json> &doctors, JsonHandler &jsonHandler);

    // Display main menu
    void displayMainMenu();

    // Display login menu
    void displayLoginMenu();

    // Display register menu
    void displayRegisterMenu();

    // Display patient menu
    void displayPatientMenu(Patient &patient);

    // Create patient appointment
    void createPatientAppointment(Patient &patient);

    // Show patient appointments
    void showPatientAppointments(Patient &patient);

    // Cancel patient appointment
    void cancelPatientAppointment(Patient &patient);

    // Update patient info
    void updatePatientInfo(Patient &patient);
};

#endif