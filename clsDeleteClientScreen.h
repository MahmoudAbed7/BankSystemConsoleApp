#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowClientListScreen.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
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
        string AccountNumber;
        cout << "Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while(!clsClient::IsClientExist(AccountNumber))
        {
            cout << "Account number is not exist, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }
public:
    static void DeleteClientScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("Delete Clients Screen");
        
        clsClient Client1 = clsClient::Find(_ReadAccountNumber());
        _PrintClientData(Client1);
        
        char Answer = 'n';
        cout << "Are you sure you want to delete this client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y')
        {
            if(Client1.Delete())
            {
                _PrintClientData(Client1);
                cout << "\n Delete done successfully \n";
            }else
            {
                cout << "\n Error client was not deleted \n";
            }
        }
    }
};
