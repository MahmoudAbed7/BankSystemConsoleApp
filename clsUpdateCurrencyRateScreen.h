#pragma once
#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "clsCurrency.h"
using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
    static double _ReadRate()
    {
        double Rate;
        cout << "Enter new rate: ";
        cin >> Rate;
        return Rate;
    }
    
    static void _PrintCurrenciesRecordLine(clsCurrency Currency)
    {
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
    
public:
    static void ShowUpdateCurrencyRateScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t Update Currency Screen");
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(_ReadCode());
        _PrintCurrenciesRecordLine(Currency);
        
        char Answer = 'n';
        cout << "Are you sure you want update currency rate Y/N: ";
        cin >> Answer;
        
        if(Answer == 'Y' || Answer == 'y')
        {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";
            Currency.UpdateRate(_ReadRate());
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrenciesRecordLine(Currency);
        }
    }
};

