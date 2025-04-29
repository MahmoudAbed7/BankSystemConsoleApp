#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    
    static clsClient _ReadClientData(clsClient &Client)
    {
        cout << "Enter First Name: ";
        Client.SetFirstName(clsInputValidate::ReadString());
        cout << "Enter Last Name: ";
        Client.SetLastName(clsInputValidate::ReadString());
        cout << "Enter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());
        cout << "Enter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());
        cout << "Enter Pin Code: ";
        Client.SetPinCode(clsInputValidate::ReadString());
        cout << "Enter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadNumber<float>());
        return Client;
    }
    
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
    static void UpdateClientScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("Update Client Screen");
        
        clsClient Client = clsClient::Find(_ReadAccountNumber());
        _PrintClientData(Client);
        
        char Answer = 'n';
        cout << "Are you sure you want to update this client Y/N: ";
        cin >> Answer;
        
        if(Answer == 'Y' || Answer == 'y')
        {
            cout << "\nUpdate Client Info: ";
            cout << "\n----------------------------------\n";
            _ReadClientData(Client);
            
            clsClient::enSaveResults SaveResult;
            SaveResult = Client.Save();
            
            switch (SaveResult)
            {
                case clsClient::svEmptyError:
                    cout << "Error, Client is empty\n";
                    break;
                case clsClient::svSuccess:
                    _PrintClientData(Client);
                    cout << "Client Updated Successfully\n";
                default:
                    break;
            }
        }
    }
};
