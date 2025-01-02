#ifndef DATAVALIDATOR_H
#define DATAVALIDATOR_H

#include <string>
#include <regex>

using namespace std;

class DataValidator
{
public:
    // Validate phone number
    bool validatePhone(const string &phone);

    // Validate email address
    bool validateEmail(const string &email);
};

#endif