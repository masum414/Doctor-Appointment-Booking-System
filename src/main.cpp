#include <iostream>
#include <vector>
#include "Patient.h"
#include "JsonHandler.h"
#include "CLI.h"

using namespace std;

int main()
{
    // Vectors to hold patients and doctors
    vector<Patient> patients;
    vector<json> doctors;

    // Create an instance of JsonHandler to manage file operations
    JsonHandler jsonHandler;

    // Load data from JSON files into vectors
    jsonHandler.loadDoctors(doctors);
    jsonHandler.loadPatients(patients);

    // Create an instance of CLI for user interaction
    CLI cli(patients, doctors, jsonHandler);
    cli.displayMainMenu();

    // Save data back to JSON files before exiting
    jsonHandler.saveDoctors(doctors);
    jsonHandler.savePatients(patients);

    return 0;
}