#include <iostream>
#include <regex>

using namespace std;

class DataValidator
{
public:
    // Validate phone number
    bool validatePhone(const string &phone)
    {
        regex phoneRegex(R"(\+8801[0-9]{9})");
        return regex_match(phone, phoneRegex);
    }

    // Validate email address
    bool validateEmail(const string &email)
    {
        regex emailRegex(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
        return regex_match(email, emailRegex);
    }

    // Validate specialization
    bool validateSpecialization(const string &specialization)
    {
        const int maxLength = 30;
        return !specialization.empty() && specialization.length() <= maxLength;
    }

    // Validate date format (YYYY-MM-DD)
    bool validateDate(const string &date)
    {
        regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
        return regex_match(date, dateRegex);
    }

    // Validate time slot format (HH:MM)
    bool validateTimeSlot(const string &timeSlot)
    {
        regex timeSlotRegex(R"((0[0-9]|1[0-9]|2[0-3]):[0-5][0-9])");
        return regex_match(timeSlot, timeSlotRegex);
    }
};