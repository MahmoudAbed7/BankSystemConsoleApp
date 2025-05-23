#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsUpdateUsersScreen : protected clsScreen
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
    
    static int _ReadPermissionToSet()
    {
        int Permission = 0;
        char Answer = 'n';
        cout << "Do you want to give him/her all permissions Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') return -1;
        
        cout << "Do you want to give him/her access to show client list Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pListClients;
        
        cout << "Do you want to give him/her access to add new client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pAddNewClient;
        
        cout << "Do you want to give him/her access to delete client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pDeleteClient;
        
        cout << "Do you want to give him/her access to update client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pUpdateClients;
        
        cout << "Do you want to give him/her access to find client Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pFindClient;
        
        cout << "Do you want to give him/her access to transaction Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pTranactions;
        
        cout << "Do you want to give him/her access to manage users Y/N: ";
        cin >> Answer;
        if(Answer == 'Y' || Answer == 'y') Permission += clsUser::enPermissions::pManageUsers;
        
        return Permission;
    }
    
    static clsUser _ReadUserData(clsUser &User)
    {
        cout << "Enter First Name: ";
        User.SetFirstName(clsInputValidate::ReadString());
        cout << "Enter Last Name: ";
        User.SetLastName(clsInputValidate::ReadString());
        cout << "Enter Email: ";
        User.SetEmail(clsInputValidate::ReadString());
        cout << "Enter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());
        cout << "Enter Password: ";
        User.SetPassword(clsInputValidate::ReadString());
        cout << "Permissions: ";
        User.SetPermissions(_ReadPermissionToSet());
        
        return User;
    }
public:
    
    static void UpdateUserScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t Update User");
        
        string UserName;
        cout << "Enter User Name: ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "User is not exist, Enter aonther one: ";
            UserName = clsInputValidate::ReadString();
        }
        
        clsUser User = clsUser::Find(UserName);
        char Answer = 'n';
        cout << "Are you sure you want to update this user Y/N: ";
        cin >> Answer;
        
        if(Answer == 'Y' || Answer == 'y')
        {
            cout << "\nUpdate User Info: ";
            cout << "\n----------------------------------\n";
            _ReadUserData(User);
            
            clsUser::enSaveResult SaveResult;
            SaveResult = User.Save();
    
            switch (SaveResult)
            {
                case clsUser::svEmptyFailed:
                    cout << "User Data Is Empty\n";
                    break;
                    
                case clsUser::svSuccess:
                    _PrintUsersData(User);
                    cout << "User Data Updated Sucessfully :-)\n";
                    break;
                    
                default:
                    break;
            }
        }
       
    }
};


