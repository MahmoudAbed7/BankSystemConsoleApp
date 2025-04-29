#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsPeriod.h"
using namespace std;

class clsInputValidate
{
public:
    template <typename T> static T IsNumberBetween(T Num, T From, T To)
    {
        return (Num >= From && Num <= To);
    }
    
    static bool IsDateBetween( clsDate Date, clsDate From, clsDate To)
    {
        //Date>=From && Date<=To
                if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
                    &&
                    (clsDate::IsDateBeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
                  )
                {
                    return true;
                }
                
                //Date>=To && Date<=From
                if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
                    &&
                    (clsDate::IsDateBeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
                   )
                {
                    return true;
                }

                return false;
    }
    
    template <typename T> static T ReadNumber(string ErrorMessage="Invalid Number, Enter again\n")
    {
        int Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage ;
        }
        return Number;
    }
        
    template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage="Number is not within range, Enter again:\n")
    {
            int Number = ReadNumber<T>();

            while (!IsNumberBetween<T>(Number,From,To))
            {
                cout << ErrorMessage;
                Number = ReadNumber<T>();
            }
            return Number;
    }

    static bool IsValideDate(clsDate Date)
    {
        return clsDate::ValideDate(Date);
    }
    
    static string ReadString()
        {
            string  Msg="";
            getline(cin >> ws, Msg);
            return Msg;
        }
};
