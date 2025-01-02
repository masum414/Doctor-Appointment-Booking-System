#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
public:
    static int nextID;
    int id;
    string name;
    string phone;
    string email;
    string password;

    User(const string &name, const string &phone, const string &email, const string &password);

    // Method to update user details
    virtual void updateDetails();
};

#endif