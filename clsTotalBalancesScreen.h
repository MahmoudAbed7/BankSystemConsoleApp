#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
    
    static void _PrintBalancesList(clsClient Client)
    {
        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }
    
public:
    
    static void TotalBalancesScreen()
    {
        vector<clsClient> vClient = clsClient::GetClientData();
        string Title = "\t  Total Balances Screen";
        string SubTitle ="\t    (" + to_string(vClient.size()) + ") Client(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        
        cout << "\n--------------------------------------------------------------------------";
        cout << "----------------------------------------------\n";
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n--------------------------------------------------------------------------";
        cout << "----------------------------------------------\n";
       
        float TotalBalances = clsClient::GetTotalBalances();
        if(vClient.size() == 0)
        {
            cout << "\t\t No Client Availbale in the system";
        }else
        {
            for(clsClient &C : vClient)
            {
                _PrintBalancesList(C);
                cout << endl;
            }
            cout << "\n--------------------------------------------------------------------------";
            cout << "----------------------------------------------\n";
            cout << "\t\t Total Balances = " << TotalBalances << endl;
                cout << "\t\t ( " << clsUtil::NumberToText(TotalBalances) << ")";
        }
    }
};
