#include <iostream>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main()
{
    // Create a JSON object
    json j;
    j["name"] = "Masum";
    j["age"] = 21;

    // Output JSON object to the console
    cout << j << endl;

    // Write the JSON object to a file
    string filePath = "data/doctors.json";
    ofstream outFile(filePath);
    if (outFile.is_open())
    {
        outFile << j.dump(4);
        outFile.close();
        cout << "JSON data has been written to " << filePath << endl;
    }
    else
    {
        cout << "Failed to open file " << filePath << endl;
    }

    // Read the JSON data back from the file
    ifstream inFile(filePath);
    if (inFile.is_open())
    {
        json j2;
        inFile >> j2;
        inFile.close();

        cout << "Read JSON data from file:" << endl;
        cout << j2.dump(4) << endl;

        cout << "Name: " << j2["name"] << ", Age: " << j2["age"] << endl;
    }
    else
    {
        cout << "Failed to open file " << filePath << endl;
    }

    return 0;
}
