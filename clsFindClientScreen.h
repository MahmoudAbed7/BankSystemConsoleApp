#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:
    
    static void _PrintClientData(clsClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }
    
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "Enter your account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsClient::IsClientExist(AccountNumber))
        {
            cout << "Account is not exist, Enter another account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }
    
public:
    static void FindClientScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("Find Client Screen");
        clsClient Client = clsClient::Find(_ReadAccountNumber());
        if(!Client.IsEmpty())
        {
            _PrintClientData(Client);
            cout << "Client is found successfully\n";
        }
        else
        {
            cout << "Client is not found\n";
        }
       
      
    }
};
