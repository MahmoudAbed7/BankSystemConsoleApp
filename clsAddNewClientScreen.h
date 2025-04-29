#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"
#include "clsShowClientListScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
public:
    
    static void AddNewClientScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t\t Add New Client");
        
        string AccountNumber;
        cout << "Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        
        clsClient NewClient = clsClient::AddNewClient(AccountNumber);
        while(NewClient.IsClientExist(AccountNumber))
        {
            cout << "Client is exist, Enter aonther one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        
        _ReadClientData(NewClient);
        clsClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
       
        switch (SaveResult)
        {
            case clsClient::svEmptyError:
                cout << "Client Data Is Empty\n";
                break;
                
            case clsClient::svAccountNumberExistError:
                cout << "Client Data Is Already Exsit\n";
                break;
                
            case clsClient::svSuccess:
                _PrintClientData(NewClient);
                cout << "Client Data Added Sucessfully :-)\n";
                break;
                
            default:
                break;
        }
       
    }
};
