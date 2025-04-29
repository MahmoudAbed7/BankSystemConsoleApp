#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
private:
    
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;
   
public:
   
    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }
    
    //Setter
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
    
    //Getter
    string GetFirstName()
    {
        return _FirstName;
    }
    string GetLastName()
    {
        return _LastName;
    }
    string GetFullName()
    {
        return  _FirstName + " " + _LastName;
    }
    string GetEmail()
    {
        return _Email;
    }
    string GetPhone()
    {
        return _Phone;
    }
    
};

