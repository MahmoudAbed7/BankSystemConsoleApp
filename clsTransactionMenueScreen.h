#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;

class clsTransactionMenueScreen : protected clsScreen
{
private:
    enum enTransactionScreenOptions{enDeposite = 1, enWithdraw = 2, enTotalBalances = 3, enTransfer = 4, enTransferLog = 5,enMainMenue = 6};
    static short _ReadTransactionMenueOptions()
    {
        short Option;
        cout << "Enter Number From 1 To 6: ";
        Option = clsInputValidate::ReadNumberBetween(1, 6);
        return Option;
    }
    
    static void _GoBackToTransactionMenue()
    {
        system("cls");
        cout << "Press any key to go back to main menue..\n";
        ShowTransactionMenue();
    }
    static void _DepositeScreen()
    {
        system("cls");
       // cout << "Show Client List Screen Here\n";
        clsDepositeScreen::DepositeScreen();
    }
    
    static void _WithdrawScreen()
    {
        system("cls");
        //cout << "Add New Client Screen Here\n";
        clsWithdrawScreen::WithdrawScreen();
    }
    
    static void _TotalBalancesScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsTotalBalancesScreen::TotalBalancesScreen();
    }
    
    static void _TransferScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsTransferScreen::TransferScreen();
        
    }
    
    static void _TransferLogScreen()
    {
        system("cls");
        //cout << "Delete Client Screen Here\n";
        clsTransferLogScreen::TransferLogScreen();
    }
    
    
    static void _PerformTransactionsMenueScreen(enTransactionScreenOptions Options)
    {
        switch (Options)
        {
            case enDeposite:
                system("cls");
                _DepositeScreen();
                _GoBackToTransactionMenue();
                break;
                
            case enWithdraw:
                system("cls");
                _WithdrawScreen();
                _GoBackToTransactionMenue();
                break;
                
            case enTotalBalances:
                system("cls");
                _TotalBalancesScreen();
                _GoBackToTransactionMenue();
                break;
                
            case enTransfer:
                system("cls");
                _TransferScreen();
                _GoBackToTransactionMenue();
                break;
                
            case enTransferLog:
                system("cls");
                _TransferLogScreen();
                _GoBackToTransactionMenue();
                break;
                
            case enMainMenue:
                system("cls");
                break;
            
            default:
                break;
        }
        
    }
public:
    static void ShowTransactionMenue()
    {
        if(!clsScreen::AccessPermissions(clsUser::enPermissions::pTranactions))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t\t\tTransactions Menue Screen");
        
        cout << "=================================================\n";
        cout << "\t Transactions Menue Options \t\n";
        cout << "=================================================\n";
        cout << "[1] Deposite\n";
        cout << "[2] Withdraw\n";
        cout << "[3] Total Balances\n";
        cout << "[4] Transfer\n";
        cout << "[5] Transfer Log\n";
        cout << "[6] Main Menue\n";
        cout << "=================================================\n";
        _PerformTransactionsMenueScreen(enTransactionScreenOptions(_ReadTransactionMenueOptions()));
    }
};
