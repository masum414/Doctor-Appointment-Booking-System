#include "DataValidator.h"

// Validate phone number
bool DataValidator::validatePhone(const string &phone)
{
    regex phoneRegex(R"(\+8801[0-9]{9})");
    return regex_match(phone, phoneRegex);
}

// Validate email address
bool DataValidator::validateEmail(const string &email)
{
    regex emailRegex(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, emailRegex);
}