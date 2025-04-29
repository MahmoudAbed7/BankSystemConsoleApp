#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
    
    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegister LoginRegister)
    {
              cout << "| " << setw(35) << left << LoginRegister.Date;
              cout << "| " << setw(20) << left << LoginRegister.UserName;
              cout << "| " << setw(20) << left << clsUtil::EncriptionText(LoginRegister.Password);
              cout << "| " << setw(20) << left << LoginRegister.Permissions;
    }
public:
    
    static void LoginRegisterScreen()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pLogRegister))
        {
            return;
        }
        vector<clsUser::stLoginRegister> vLoginRegister = clsUser::GetLoginRegisterRecord();
        string Title = "\t\t Login Register";
        string SubTitle = "\t\t " + to_string(vLoginRegister.size()) + " Record(s)";
        
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(35) << "Time/Date";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(20) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        if(vLoginRegister.size() == 0)
        {
            cout << "\t\t System is empty from records\n";
        }
        
        for(clsUser::stLoginRegister &Record : vLoginRegister)
        {
            _PrintLoginRegisterRecordLine(Record);
            cout << endl;
        }
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};
