#pragma once
#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "clsCurrency.h"
using namespace std;

class clsShowCurrencyListScreen : protected clsScreen
{
private:
    static void _PrintCurrenciesRecordLine(clsCurrency Currency)
    {
              cout << "| " << setw(35) << left << Currency.GetCountry();
              cout << "| " << setw(15) << left << Currency.GetCurrencyCode();
              cout << "| " << setw(25) << left << Currency.GetCurrencyName();
              cout << "| " << setw(15) << left << Currency.GetRate();
    }
public:
    static void ShowCurrencyListScreen()
    {
        vector<clsCurrency> vCurrency = clsCurrency::GetCurrencyDataFromFile();
        string Title = "\t\t Show Currency List\n";
        string SubTitle = "\t\t" + to_string(vCurrency.size()) + " Currencie(s)";
        
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(15) << "CurrencyCode";
        cout << "| " << left << setw(25) << "CurrencyName";
        cout << "| " << left << setw(15) << "Currency Rate";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        
        if(vCurrency.size() == 0)
        {
            cout << "\t\t System is empty from currencies\n";
        }
        
        for(clsCurrency &C : vCurrency)
        {
            _PrintCurrenciesRecordLine(C);
            cout << endl;
        }
        
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

