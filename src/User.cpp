#include <iostream>
#include "User.h"
#include "DataValidator.h"

using namespace std;

int User::nextID = 0;

User::User(const string &name, const string &phone, const string &email, const string &password)
{
    id = nextID++;
    this->name = name;
    this->phone = phone;
    this->email = email;
    this->password = password;
}

void User::updateDetails()
{
    DataValidator validator;
    cout << "Updating User Details..." << endl;

    cout << "Enter new name: ";
    getline(cin, name);

    do
    {
        cout << "Enter new phone number: ";
        getline(cin, phone);
        if (!validator.validatePhone(phone))
        {
            cout << "Invalid phone number. Please enter a valid phone number." << endl;
        }
    } while (!validator.validatePhone(phone));

    do
    {
        cout << "Enter new email address: ";
        getline(cin, email);
        if (!validator.validateEmail(email))
        {
            cout << "Invalid email address. Please enter a valid email address." << endl;
        }
    } while (!validator.validateEmail(email));

    cout << "Enter new password: ";
    getline(cin, password);

    cout << "User details updated successfully." << endl;
}