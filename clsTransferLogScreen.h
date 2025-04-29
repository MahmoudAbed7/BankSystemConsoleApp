#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
    
    static void _PrintTransferLogRecordLine(clsClient::stTransferLog TransferLog)
    {
        cout << "| " << setw(25) << left << TransferLog.TimeDate;
        cout << "| " << setw(15) << left << TransferLog.SrcAccountNumber;
        cout << "| " << setw(15) << left << TransferLog.DesAccountNumber;
        cout << "| " << setw(15) << left << TransferLog.Amount;
        cout << "| " << setw(15) << left << TransferLog.SrcAmount;
        cout << "| " << setw(15) << left << TransferLog.DesAmount;
        cout << "| " << setw(15) << left << TransferLog.UserName;
    }
public:
    
    static void TransferLogScreen()
    {
        vector<clsClient::stTransferLog> vTransferLog = clsClient::GetTransferLog();
        string Title = "\t\t Transfer Log Register";
        string SubTitle = "\t\t " + to_string(vTransferLog.size()) + " Record(s)";
        
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(25) << "Time/Date";
        cout << "| " << left << setw(15) << "Src Acc.Num";
        cout << "| " << left << setw(15) << "Des Acc.Num";
        cout << "| " << left << setw(15) << "Amount";
        cout << "| " << left << setw(15) << "Src Acc.Balance";
        cout << "| " << left << setw(15) << "Des Acc.Balance";
        cout << "| " << left << setw(15) << "User Name";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        if(vTransferLog.size() == 0)
        {
            cout << "\t\t System is empty from records\n";
        }
        
        for(clsClient::stTransferLog &Record : vTransferLog)
        {
            _PrintTransferLogRecordLine(Record);
            cout << endl;
        }
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

