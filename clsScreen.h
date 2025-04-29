#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "=========================================\n\n";
        cout << Title << endl;
        if(SubTitle != "")
        {
            cout << SubTitle << endl;
        }
        cout << "User: " << Current.GetUserName() << endl;
        cout << "Date: " << clsDate::DateToString(clsDate()) << endl;
        cout << "\n=========================================\n";
    }
    
    static bool AccessPermissions(clsUser::enPermissions Permission)
    {
        if(!Current.CheckPermission(Permission))
        {
            cout << "=========================================\n\n";
            cout << "\t\t Access Denied call admin";
            cout << "\n=========================================\n";
            return false;
        }
        return true;
    }
};
