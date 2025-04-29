#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculationsScreen.h"
#include "Global.h"
using namespace std;

class clsCurrenciesMenueScreen : protected clsScreen
{
private:
    enum enCurrencyMenueOption{enCurrencyList = 1, enFindCurrency = 2, enUpdateRate = 3,
        enCurrencyCalculator = 4, enExit = 5};
    
    static short _ReadCurrencyMenueOptions()
    {
        short Option = 0;
        cout << "\t\t Enter number from 1 to 5: ";
        Option = clsInputValidate::ReadNumberBetween(1, 5, "\t\t Enter number from 1 to 5: ");
        return Option;
    }
    
    static void _GoBackToCurrencyMenue()
    {
        system("cls");
        cout << "Press any key to return to currency menue \n";
        ShowCurrenciesMenue();
    }
    
    static void _CurrencyList()
    {
        //cout << "Currency List Here";
        clsShowCurrencyListScreen::ShowCurrencyListScreen();
    }
    
    static void _FindCurrency()
    {
        //cout << "Find Currency Here";
       clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    
    static void _UpdateRate()
    {
        //cout << "Update Currency Rate Here";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    
    static void _CurrencyCalculation()
    {
        //cout << "Currency Calaculator Rate Here";
        clsCurrencyCalculationsScreen::ShowCurrencyCalculationScreen();
    }
    
    static void _PerformCurrencyMenueScreen(enCurrencyMenueOption CurrencyMenueOption)
    {
        switch (CurrencyMenueOption)
        {
            case enCurrencyList:
                system("cls");
                _CurrencyList();
                _GoBackToCurrencyMenue();
                break;
                
            case enFindCurrency:
                system("cls");
                _FindCurrency();
                _GoBackToCurrencyMenue();
                break;
                
            case enUpdateRate:
                system("cls");
                _UpdateRate();
                _GoBackToCurrencyMenue();
                break;
                
            case enCurrencyCalculator:
                system("cls");
                _CurrencyCalculation();
                _GoBackToCurrencyMenue();
                break;
                
            case enExit:
                break;
            default:
                break;
        }
    }
public:
    static void ShowCurrenciesMenue()
    {
        clsScreen::_DrawScreenHeader("\t\t Currency Exchange Menue");
        cout << "-----------------------------------------\n";
        cout << "\t\t Currency Exchange Menue Options\n";
        cout << "-----------------------------------------\n";
        cout << "\t\t [1] Show Currnecy List" << endl;
        cout << "\t\t [2] FInd Currency" << endl;
        cout << "\t\t [3] Update Currency Rate" << endl;
        cout << "\t\t [4] Currency Calculator" << endl;
        cout << "\t\t [5] Main Menue" << endl;
        cout << "-----------------------------------------\n";
        _PerformCurrencyMenueScreen(enCurrencyMenueOption(_ReadCurrencyMenueOptions()));
};

