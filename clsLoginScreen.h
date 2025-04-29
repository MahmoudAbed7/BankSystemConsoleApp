#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
    
    static bool _Login()
    {
        string UserName, Password;
        bool LoginFailed = false;
        short Trials = 3;
    
        do {
            if(LoginFailed)
            {
                --Trials;
                std::cout << "Invalide user name & password\n";
                std::cout << "You have " << Trials << " Time(s) to login" << endl;
            }
            
            if(Trials == 0)
            {
                cout << "\n\nYou are looked after 3 failed trials\n";
                return false;
            }
            cout << "User Name: ";
            UserName = clsInputValidate::ReadString();
            cout << "Password: ";
            Password = clsInputValidate::ReadString();
            Current = clsUser::Find(UserName, Password);
            LoginFailed = Current.IsEmpty();
            
        } while (LoginFailed);
        Current.CreateLogRegisterFile();
        clsMainScreen::ShowMainMenue();
        return true;
    }
public:
    
    static bool LoginScreen()
    {
        system("cls");
        clsScreen::_DrawScreenHeader("\t\t Login Screen");
        return _Login();
    }
    
};
