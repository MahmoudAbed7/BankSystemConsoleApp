#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositeScreen : protected clsScreen
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
    
    static void DepositeScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t\t Deposite Screen");
        
        clsClient Client = clsClient::Find(_ReadAccountNumber());
        _PrintClientData(Client);
        
        float Amount;
        char Answer = 'n';
        cout << "Are you sure you want to deposite to this client Y/N: ";
        cin >> Answer;
        
        if(Answer == 'Y' || Answer == 'y')
        {
            cout << "Enter amount to deposite: ";
            cin >> Amount;
            Client.Deposite(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client.GetAccountBalance() << endl;
        }
        
    }
};
