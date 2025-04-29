#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionMenueScreen.h"
#include "clsManageUsersMenueScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrenciesMenueScreen.h"
#include "Global.h"

class clsMainScreen : protected clsScreen
{
private:
    enum enMainScreenOptions{enShowClientListScreen = 1, enAddNewClientScreen = 2, enDeleteClientScreen = 3, enUpdateClientScreen = 4, enFindClientScreen = 5, enTransactions = 6, enManageUsersScreen = 7, enLoginRegister = 8 , enCurrencyExchange = 9, enLogoutScreen = 10};
    static short _ReadMainMenueOptions()
    {
        short Option;
        std::cout << "Enter Number From 1 To 10: ";
        Option = clsInputValidate::ReadNumberBetween(1, 10);
        return Option;
    }
    
    static void _GoBackToMainMenue()
    {
        system("cls");
        std::cout << "Press any key to go back to main menue..\n";
        ShowMainMenue();
    }
    
    static void _ShowClientListScreen()
    {
        system("cls");
       // cout << "Show Client List Screen Here\n";
        clsShowClientListScreen::ShowClientListScreen();
    }
    
    static void _AddNewClientScreen()
    {
        system("cls");
        //cout << "Add New Client Screen Here\n";
        clsAddNewClientScreen::AddNewClientScreen();
    }
    
    static void _DeleteClientScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsDeleteClientScreen::DeleteClientScreen();
    }
    
    static void _UpdateClientScreen()
    {
        system("cls");
        //cout << "Update Client Screen Here\n";
        clsUpdateClientScreen::UpdateClientScreen();
    }
    
    static void _FindClientScreen()
    {
        system("cls");
        //cout << "Find Client Screen Here\n";
        clsFindClientScreen::FindClientScreen();
    }
    
    static void _TransactionScreen()
    {
        system("cls");
        //cout << "Transaction Screen Here\n";
        clsTransactionMenueScreen::ShowTransactionMenue();
    }
    
    static void _ManageUsersScreen()
    {
        system("cls");
       // cout << "Manage Users Screen Here\n";
        clsManageUsersMenueScreen::ShowManageUsersMenue();
    }
    
    static void _LoginRegister()
    {
        system("cls");
       // cout << "Manage Users Screen Here\n";
        clsLoginRegisterScreen::LoginRegisterScreen();
    }
    
    static void _CurrencyExchangeScreen()
    {
        system("cls");
       // cout << "Manage Users Screen Here\n";
        clsCurrenciesMenueScreen::ShowCurrenciesMenue();
    }
    
    static void _LogoutScreen()
    {
        Current = clsUser::Find("", "");
    }
    
    static void _PerformMainMenueScreen(enMainScreenOptions Options)
    {
        switch (Options)
        {
            case enShowClientListScreen:
                system("cls");
                _ShowClientListScreen();
                _GoBackToMainMenue();
                break;
                
            case enAddNewClientScreen:
                system("cls");
                _AddNewClientScreen();
                _GoBackToMainMenue();
                break;
                
            case enDeleteClientScreen:
                system("cls");
                _DeleteClientScreen();
                _GoBackToMainMenue();
                break;
                
            case enUpdateClientScreen:
                system("cls");
                _UpdateClientScreen();
                _GoBackToMainMenue();
                break;
                
            case enFindClientScreen:
                system("cls");
                _FindClientScreen();
                _GoBackToMainMenue();
                break;
                
            case enTransactions:
                system("cls");
                _TransactionScreen();
                _GoBackToMainMenue();
                break;
                
            case enManageUsersScreen:
                system("cls");
                _ManageUsersScreen();
                _GoBackToMainMenue();
                break;
                
            case enLoginRegister:
                system("cls");
                _LoginRegister();
                _GoBackToMainMenue();
                break;
                
            case enCurrencyExchange:
                system("cls");
                _CurrencyExchangeScreen();
                _GoBackToMainMenue();
                break;
                
            case enLogoutScreen:
                system("cls");
                _LogoutScreen();
                break;
                
            default:
                break;
        }
        
    }
public:
    static void ShowMainMenue()
    {
        clsScreen::_DrawScreenHeader("\t\t\tMain Menue Screen");
        
       std::cout << "=================================================\n";
       std::cout << "\t Show Main Menue Options \t\n";
       std::cout << "=================================================\n";
       std::cout << "[1] Show Client List\n";
       std::cout << "[2] Add New Client\n";
       std::cout << "[3] Delete Client\n";
       std::cout << "[4] Update Client\n";
       std::cout << "[5] Find Client\n";
       std::cout << "[6] Transaction\n";
       std::cout << "[7] Manage Users\n";
       std::cout << "[8] Login Register\n";
       std::cout << "[9] Currency Exchange\n";
       std::cout << "[10] Logout\n";
       std::cout << "=================================================\n";
        _PerformMainMenueScreen(enMainScreenOptions(_ReadMainMenueOptions()));
    }
};
