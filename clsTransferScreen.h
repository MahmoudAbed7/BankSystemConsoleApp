#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber(string Msg)
    {
        string AccountNumber;
        cout << Msg;
        AccountNumber = clsInputValidate::ReadString();
        if(!clsClient::IsClientExist(AccountNumber))
        {
            cout << "Client is not exist" << Msg;
            AccountNumber = clsInputValidate::ReadString();
        }return AccountNumber;
    }
    
    static void _PrintClientCard(clsClient Client)
    {
        cout << "Client Card\n";
        cout << "---------------------------------\n\n";
        cout << "Client Name    : " << Client.GetFullName() << endl;
        cout << "Account Number : " << Client.GetAccountNumber() << endl;
        cout << "Account Balance: " << Client.GetAccountBalance() << endl;
        cout << "---------------------------------\n\n";
    }
    
    static float _ReadAmount(clsClient Client)
    {
        float Amount;
        cout << "Enter amount to transfer: ";
        cin >> Amount;
        if(Client.GetAccountBalance() < Amount)
        {
            cout << "Amount excceds the available balance, Enter another amount: ";
            cin >> Amount;
        }
        return Amount;
    }
    
public:
    static void TransferScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t Transfer Screen");
        clsClient From = clsClient::Find(_ReadAccountNumber("Enter Account Number To Transfer From: "));
        _PrintClientCard(From);
        clsClient To = clsClient::Find(_ReadAccountNumber("Enter Account Number To Transfer To: "));
        _PrintClientCard(To);
        
        float Amount = _ReadAmount(From);
        
        char Answer = 'n';
        cout << "Are you sure you want to transfer this amount Y/N: ";
        cin >> Answer;
        
        if(Answer == 'Y' || Answer == 'y')
        {
            if(From.Transfer(Amount, To, Current.GetUserName()))
            {
                cout << "\n Transfer done successfully \n";
               
            }else
            {
                cout << "\n Transfer failed \n";
            }
            _PrintClientCard(From);
            cout << endl;
            _PrintClientCard(To);
        }
    }
};
