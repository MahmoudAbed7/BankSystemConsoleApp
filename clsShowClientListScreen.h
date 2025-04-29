#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"
#include "Global.h"
using namespace std;

class clsShowClientListScreen : protected clsScreen
{
private:
    static void _PrintClientData(clsClient Client)
    {
        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.GetPhone();
        cout << "| " << setw(20) << left << Client.GetEmail();
        cout << "| " << setw(10) << left << Client.GetPinCode();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }
    
public:
    static void ShowClientListScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pListClients))
        {
            return;
        }
        vector<clsClient> vClient = clsClient::GetClientData();
        
        string Title = "\t\t Show Client List\n";
        string SubTitle = "\t\t" + to_string(vClient.size()) + " Client(s)";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        
        if(vClient.size() == 0)
        {
            cout << "\t\t System is empty from clients\n";
        }
        
        for(clsClient &C : vClient)
        {
            _PrintClientData(C);
            cout << endl;
        }
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
