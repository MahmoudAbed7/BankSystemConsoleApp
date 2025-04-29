#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    
    static void _PrintUsersData(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.GetFullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermission  : " << User.GetPermissions();
        cout << "\n___________________\n";
    }
    
    static string _ReadUserName()
    {
        string UserName;
        cout << "Enter User Name: ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "User Name is not exist, Enter another one: ";
            UserName = clsInputValidate::ReadString();
        }
        return UserName;
    }
public:
    static void DeleteUserScreen()
    {
        clsScreen::_DrawScreenHeader("Delete Users Screen");
        
        clsUser User = clsUser::Find(_ReadUserName());
        _PrintUsersData(User);
        
        char Answer = 'n';
        cout << "Are you sure you want to delete this client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y')
        {
            if(User.Delete())
            {
                _PrintUsersData(User);
                cout << "\n Delete done successfully \n";
            }else
            {
                cout << "\n Error client was not deleted \n";
            }
        }
    }
};

