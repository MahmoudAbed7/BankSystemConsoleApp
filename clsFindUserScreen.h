#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsFindUsersScreen : protected clsScreen
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
    
public:
    
    static void FindUserScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t Find User");
        
        string UserName;
        cout << "Enter User Name: ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "User is not exist, Enter aonther one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        if(User.IsEmpty())
        {
            cout << "User is not Found\n";
        }else
        {
            _PrintUsersData(User);
            cout << "User Found Successfully\n";
        }
    }
};



