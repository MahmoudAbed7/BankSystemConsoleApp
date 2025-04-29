#pragma once
#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    
    static void _PrintCurrenciesRecordLine(clsCurrency Currency)
    {
              cout << "| " << setw(35) << left << Currency.GetCountry();
              cout << "| " << setw(15) << left << Currency.GetCurrencyCode();
              cout << "| " << setw(25) << left << Currency.GetCurrencyName();
              cout << "| " << setw(15) << left << Currency.GetRate();
    }
    
    static string _ReadCountry()
    {
        string Country;
        cout << "Enter country: ";
        Country = clsInputValidate::ReadString();
        return Country;
    }
    
    static string _ReadCode()
    {
        string Code;
        cout << "Enter currency code: ";
        Code = clsInputValidate::ReadString();
        return Code;
    }
    
    static void _ShowResult(clsCurrency Currency)
    {
        if(!Currency.IsEmpty())
        {
            cout << "Currency is found \n";
            _PrintCurrenciesRecordLine(Currency);
        }else
        {
            cout << "Currency is not found \n";
        }
    }
    
public:
    static void ShowFindCurrencyScreen()
    {
        clsScreen::_DrawScreenHeader("\t\t Find Currency");
        
        short Answer = 1;
        cout << "choose type of search [1] Code, [2] Country Name: ";
        cin >> Answer;
        
        if(Answer == 1)
        {
            string Code = _ReadCode();
            clsCurrency Currency = clsCurrency::FindByCurrencyCode(Code);
            _ShowResult(Currency);
        }
        
        else
        {
            string Country = _ReadCountry();
            clsCurrency Currency = clsCurrency::FindCurrencyByCountryName(Country);
            _ShowResult(Currency);
        }
    }
};

