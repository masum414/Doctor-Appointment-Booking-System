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

    // Validate specialization
    bool validateSpecialization(const string &specialization);

    // Validate date format (YYYY-MM-DD)
    bool validateDate(const string &date);

    // Validate time slot format (HH:MM)
    bool validateTimeSlot(const string &timeSlot);
};

#endif