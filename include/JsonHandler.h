#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <vector>
#include <json.hpp>
#include "Patient.h"

using namespace std;
using json = nlohmann::json;

class JsonHandler
{
public:
    // Load doctors data from JSON file
    void loadDoctors(vector<json> &doctors);

    // Save doctors data to JSON file
    void saveDoctors(const vector<json> &doctors);

    // Load patients data from JSON file
    void loadPatients(vector<Patient> &patients);

    // Save patients data to JSON file
    void savePatients(const vector<Patient> &patients);
};

#endif