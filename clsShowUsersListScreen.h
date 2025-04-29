#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsShowUserListScreen : protected clsScreen
{
private:
    static void _PrintUserData(clsUser User)
    {
        cout << "| " << setw(15) << left << User.GetUserName();
        cout << "| " << setw(20) << left << User.GetFullName();
        cout << "| " << setw(12) << left << User.GetPhone();
        cout << "| " << setw(20) << left << User.GetEmail();
        cout << "| " << setw(10) << left << User.GetPassword();
        cout << "| " << setw(12) << left << User.GetPermissions();
    }
    
public:
    static void ShowUsersListScreen()
    {
        vector<clsUser> vUser = clsUser::GetUsersDataFromFile();
        
        string Title = "\t\t Show User List\n";
        string SubTitle = "\t\t" + to_string(vUser.size()) + " User(s)";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permission";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        
        if(vUser.size() == 0)
        {
            cout << "\t\t System is empty from users\n";
        }
        
        for(clsUser &U : vUser)
        {
            _PrintUserData(U);
            cout << endl;
        }
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

