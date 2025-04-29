#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsCurrency
{
    
private:
    enum enMode{enEmptyMode = 0, enUpdateMode = 1};
    enMode _Mode;
    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;
    
    static string _ConvertCurrencyDataToLine(clsCurrency Currency, string Spaces = "/##/")
    {
        string DataLine;
        DataLine += Currency.GetCountry() + Spaces;
        DataLine += Currency.GetCurrencyCode() + Spaces;
        DataLine += Currency.GetCurrencyName() + Spaces;
        DataLine += to_string(Currency.GetRate());
        return DataLine;
    }
    
    static clsCurrency _ConvertCurrencyDataLineToRecord(string Text, string Spaces = "/##/")
    {
        vector<string> vCurrency = clsString::Split(Text, Spaces);
        clsCurrency Currency(enMode::enUpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
        return Currency;
    }
    
   
    static vector<clsCurrency> _LoadCurrencyDataFromFile()
    {
        fstream MyFile;
        vector<clsCurrency> vCurrency;
        MyFile.open("Currencies.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertCurrencyDataLineToRecord(Line);
                vCurrency.push_back(Currency);
            }MyFile.close();
        }return vCurrency;
    }
    
    static void _SaveCurrencyDataOnFile(vector<clsCurrency> vCurrency)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);
        if(MyFile.is_open())
        {
            string Dataline;
            for(clsCurrency &C : vCurrency)
            {
                Dataline = _ConvertCurrencyDataToLine(C);
                MyFile << Dataline << endl;
            }MyFile.close();
        }
    }
    
    static void _AddCurrencyDataToFile(string CurrencyData)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out | ios::app);
        if(MyFile.is_open())
        {
            MyFile << CurrencyData << endl;
            MyFile.close();
        }
    }
    
    void _AddNew()
    {
        _AddCurrencyDataToFile(_ConvertCurrencyDataToLine(*this));
    }
    
    void _Update()
    {
        vector<clsCurrency> vCurrency = _LoadCurrencyDataFromFile();
        for(clsCurrency &C : vCurrency)
        {
            if(C.GetCurrencyCode() == _CurrencyCode)
            {
                C = *this;
                break;
            }
        }_SaveCurrencyDataOnFile(vCurrency);
    }
    static clsCurrency _GetEmptyCurrencyData()
    {
        return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
    }
    
   
public:
    
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    
  
    //Setter
    void SetRate(float Rate){_Rate = Rate;}
   //Getter
    string GetCountry(){return _Country;}
    string GetCurrencyCode(){return _CurrencyCode;}
    string GetCurrencyName(){return _CurrencyName;}
    float  GetRate(){return _Rate;}
    
    bool IsEmpty(){ return _Mode == enMode::enEmptyMode;}
    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }
    
    static clsCurrency FindCurrencyByCountryName(string Country)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertCurrencyDataLineToRecord(Line);
                if(clsString::UpperAllString(Currency.GetCountry()) == clsString::UpperAllString(Country))
                {
                    return Currency;
                    MyFile.close();
                }
            }
        }return _GetEmptyCurrencyData();
    }
    
    static clsCurrency FindByCurrencyCode(string CurrencyCode)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertCurrencyDataLineToRecord(Line);
                if(Currency.GetCurrencyCode() == clsString::UpperAllString(CurrencyCode))
                {
                    return Currency;
                    MyFile.close();
                }
            }
        }return _GetEmptyCurrencyData();
    }
    
    
    static vector<clsCurrency> GetCurrencyDataFromFile()
    {
        return _LoadCurrencyDataFromFile();
    }
    
    
    enum enSaveResult{svEmptyFailed = 0, svSuccess = 1};
    enSaveResult Save()
    {
        switch (_Mode)
        {
            case enEmptyMode:
                if(IsEmpty()) return svEmptyFailed;
                break;
                
            case enUpdateMode:
                _Update();
                return svSuccess;
        
            default:
                break;
        }  return svEmptyFailed;
    }
    
    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = FindByCurrencyCode(CurrencyCode);
        return !Currency.IsEmpty();
    }
    
    float ConvertToUSD(float Amount)
    {
        return Amount / GetRate();
    }
    
    float ConvertToOtherCurrencies(float Amount, clsCurrency Currency)
    {
        float Change = ConvertToUSD(Amount);
        if(Currency.GetCurrencyCode() == "USD")
        {
            return Change;
        }
        return Change * Currency.GetRate();
    }
};

