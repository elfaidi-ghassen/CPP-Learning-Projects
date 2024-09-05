#pragma once
#include <iostream>

using std::string;

class clsPerson 
{
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

    clsPerson(string firstName, string lastName, string email, string phone)
    {
        _FirstName = firstName;
        _LastName = lastName;
        _Email = email;
        _Phone = phone;
    }

    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    void SetEmail(string Email)
    {
        _Email = Email;
    }
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetFirstName()
    {
        return _FirstName;
    }
    string GetLastName()
    {
        return _LastName;
    }
    string GetEmail()
    {
        return _Email;
    }
    string GetPhone()
    {
        return _Phone;
    }

    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
    __declspec(property(get = GetLastName, put = SetLastName)) string LastName;
    __declspec(property(get = GetEmail, put = SetEmail)) string Email;
    __declspec(property(get = GetPhone, put = SetPhone)) string Phone;

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void Print()
    {
        std::cout << "\nInfo:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName: " << _FirstName;
        std::cout << "\nLastName : " << _LastName;
        std::cout << "\nFull Name: " << FullName();
        std::cout << "\nEmail    : " << _Email;
        std::cout << "\nPhone    : " << _Phone;
        std::cout << "\n___________________\n";

    }
};

