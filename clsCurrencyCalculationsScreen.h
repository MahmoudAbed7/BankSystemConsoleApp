#pragma once
#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "clsCurrency.h"
using namespace std;

class clsCurrencyCalculationsScreen : protected clsScreen
{
private:
    
    static void _PrintCurrenciesRecordLine(clsCurrency Currency, string Title)
    {
              cout << setw(35) << left << Title << endl;
              cout << "| " << setw(35) << left << Currency.GetCountry();
              cout << "| " << setw(15) << left << Currency.GetCurrencyCode();
              cout << "| " << setw(25) << left << Currency.GetCurrencyName();
              cout << "| " << setw(15) << left << Currency.GetRate();
              cout << endl;
    }
    
    static string _ReadCode()
    {
        string Code;
        cout << "Enter currency code: ";
        Code = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(Code))
        {
            cout << "Currency is not found, Enter currency code: ";
            Code = clsInputValidate::ReadString();
        }
        return Code;
    }
    
    static clsCurrency _ReadCurrency()
    {
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(_ReadCode());
        return Currency;
    }
    
    static double _ReadAmount()
    {
        double Amount;
        cout << "Enter amount: ";
        cin >> Amount;
        return Amount;
    }
    
    static void _PrintCalculationResult(clsCurrency From, clsCurrency To, float Amount)
    {
        
        float ResultInUSD = From.ConvertToUSD(Amount);
       _PrintCurrenciesRecordLine(From, "Exchange From");
       
      cout << Amount << " " << From.GetCurrencyCode() << " = "
       << ResultInUSD << " " << "USD" << endl;
        
        if (To.GetCurrencyCode() == "USD")
        {
            return;
        }
        
        cout << "\nConverting from USD to:\n";
        _PrintCurrenciesRecordLine(To, "Exchange To");
        float Result = From.ConvertToOtherCurrencies(ResultInUSD, To);
        
        cout << Amount << " " << From.GetCurrencyCode() << " = "
         << Result << " " << To.GetCurrencyCode() << endl;
        
    }
public:
    static void ShowCurrencyCalculationScreen()
    {
        char Continue = 'y';
        
        while(Continue == 'Y' || Continue == 'y')
        {
            system("cls");
            clsScreen::_DrawScreenHeader("\t\t Currency Calculations");
            _PrintCalculationResult(_ReadCurrency(), _ReadCurrency(), _ReadAmount());
            cout << "Do you want to perform another calculation Y/N: ";
            cin >> Continue;
        }
      
        
        
    }
};

