#ifndef USER_H
#define USER_H

#include <string>
#include "DataValidator.h"

using namespace std;

class User
{
public:
    int id;
    string name;
    string phone;
    string email;
    string password;

    // To keep track of the next ID
    static int nextId;

public:
    User(const string &name, const string &phone, const string &email, const string &password);

    // Pure virtual functions for login and registration
    virtual void loginUser() = 0;
    virtual void registerUser() = 0;

    // To update user details
    void updateDetails();
};

#endif