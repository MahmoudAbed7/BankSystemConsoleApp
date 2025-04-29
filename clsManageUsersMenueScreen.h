#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowUsersListScreen.h"
#include "clsAddNewUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUsersScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersMenueScreen : protected clsScreen
{
private:
    enum enManageUsersScreenOptions
    {
        enShowUsersList = 1, enAddNewUsers = 2, enDeleteUsers = 3,
        enUpdateUsers = 4, enFindUsers = 5, enMainMenue = 6
    };
    
    static short _ReadManageUsersMenueOptions()
    {
        short Option;
        cout << "Enter Number From 1 To 6: ";
        Option = clsInputValidate::ReadNumberBetween(1, 6);
        return Option;
    }
    
    static void _GoBackToManageUsersMenue()
    {
        system("cls");
        cout << "Press any key to go back to main menue..\n";
        ShowManageUsersMenue();
    }
    static void _ShowUsersListScreen()
    {
        system("cls");
       // cout << "Show Client List Screen Here\n";
        clsShowUserListScreen::ShowUsersListScreen();
    }
    
    static void _AddNewUsersScreen()
    {
        system("cls");
        //cout << "Add New Client Screen Here\n";
        clsAddNewUsersScreen::AddNewUserScreen();
    }
    
    static void _DeleteUsersScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsDeleteUserScreen::DeleteUserScreen();
    }
    
    static void _UpdateUsersScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsUpdateUsersScreen::UpdateUserScreen();
    }
    
    static void _FindUsersScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsFindUsersScreen::FindUserScreen();
    }
    
    static void _PerformManageUsersMenueScreen(enManageUsersScreenOptions Options)
    {
        switch (Options)
        {
            case enShowUsersList:
                system("cls");
                _ShowUsersListScreen();
                _GoBackToManageUsersMenue();
                break;
                
            case enAddNewUsers:
                system("cls");
                _AddNewUsersScreen();
                _GoBackToManageUsersMenue();
                break;
                
            case enDeleteUsers:
                system("cls");
                _DeleteUsersScreen();
                _GoBackToManageUsersMenue();
                break;
                
            case enUpdateUsers:
                system("cls");
                _UpdateUsersScreen();
                _GoBackToManageUsersMenue();
                break;
                
            case enFindUsers:
                system("cls");
                _FindUsersScreen();
                _GoBackToManageUsersMenue();
                break;
                
            case enMainMenue:
                system("cls");
                break;
            
            default:
                break;
        }
        
    }
public:
    static void ShowManageUsersMenue()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t\t\tManage Users Menue Screen");
        
        cout << "=================================================\n";
        cout << "\t Manage Users Menue Options \t\n";
        cout << "=================================================\n";
        cout << "[1] Show Users List\n";
        cout << "[2] Add New Users\n";
        cout << "[3] Delete Users\n";
        cout << "[4] Update Users\n";
        cout << "[5] Find Users\n";
        cout << "[6] Main Menue\n";
        cout << "=================================================\n";
        _PerformManageUsersMenueScreen(enManageUsersScreenOptions(_ReadManageUsersMenueOptions()));
    }
};

