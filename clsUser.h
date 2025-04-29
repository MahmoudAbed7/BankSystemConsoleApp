#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
using namespace std;

class clsUser : public clsPerson
{
    
private:
    enum enMode{enEmptyMode = 0, enUpdateMode = 1, enAddNewMode = 2};
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permission;
    bool _MarkForDelete = false;
    
    static string _ConvertUserDataToLine(clsUser User, string Spaces = "/##/")
    {
        string Dataline;
        Dataline += User.GetFirstName() + Spaces;
        Dataline += User.GetLastName() + Spaces;
        Dataline += User.GetEmail() + Spaces;
        Dataline += User.GetPhone() + Spaces;
        Dataline += User.GetUserName() + Spaces;
        Dataline += User.GetPassword() + Spaces;
        Dataline += to_string(User.GetPermissions());
        return Dataline;
    }
    
    static clsUser _ConvertUserDataLineToRecord(string Text, string Spaces = "/##/")
    {
        vector<string> vUser = clsString::Split(Text, Spaces);
        clsUser User(enMode::enUpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], vUser[5], stoi(vUser[6]));
        return User;
    }
    
    public: struct stLoginRegister;
    static stLoginRegister _ConvertLineToRegisterRecord(string Text, string Spaces = "/##/")
    {
        vector<string> vLoginRegister = clsString::Split(Text, Spaces);
        stLoginRegister LoginRegister;
        LoginRegister.Date = vLoginRegister[0];
        LoginRegister.UserName = vLoginRegister[1];
        LoginRegister.Password = vLoginRegister[2];
        LoginRegister.Permissions = stoi(vLoginRegister[3]);
        return LoginRegister;
    }
    
    static vector<clsUser> _LoadUsersDataFromFile()
    {
        fstream MyFile;
        vector<clsUser> vUser;
        MyFile.open("MyUserData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertUserDataLineToRecord(Line);
                vUser.push_back(User);
            }MyFile.close();
        }return vUser;
    }
    
    static void _SaveUsersDataOnFile(vector<clsUser> vUser)
    {
        fstream MyFile;
        MyFile.open("MyUserData.txt", ios::out);
        if(MyFile.is_open())
        {
            string Dataline;
            for(clsUser &U : vUser)
            {
                if(!U.MarkedForDelete())
                {
                    Dataline = _ConvertUserDataToLine(U);
                    MyFile << Dataline << endl;
                }
            }MyFile.close();
        }
    }
    
    static void _AddUserDataToFile(string UserData)
    {
        fstream MyFile;
        MyFile.open("MyUserData.txt", ios::out | ios::app);
        if(MyFile.is_open())
        {
            MyFile << UserData << endl;
            MyFile.close();
        }
    }
    
    void _AddNew()
    {
        _AddUserDataToFile(_ConvertUserDataToLine(*this));
    }
    
    void _Update()
    {
        vector<clsUser> vUser = _LoadUsersDataFromFile();
        for(clsUser &U : vUser)
        {
            if(U.GetUserName() == _UserName)
            {
                U = *this;
                break;
            }
        }_SaveUsersDataOnFile(vUser);
    }
    static clsUser _GetEmptyUserData()
    {
        return clsUser(enMode::enEmptyMode, "", "", "", "", "", "", 0);
    }
    
    string _PrepareLogRegister()
    {
        string LogRegister;
        LogRegister += clsDate::GetSystemDateTimeString() + "/##/";
        LogRegister += GetUserName() + "/##/";
        LogRegister += GetPassword() + "/##/";
        LogRegister += to_string(GetPermissions());
        return LogRegister;
    }
    
public:
    
    enum enPermissions
    {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLogRegister = 128
    };
    
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permission) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permission = Permission;
    }
    
    struct stLoginRegister
    {
        string Date, UserName, Password;
        int Permissions;
    };
    
    stLoginRegister LoginRegister;
    //Setter
    void SetPassword(string Password){ _Password = Password;}
    void SetPermissions(int Permissions){_Permission = Permissions;}
   //Getter
    string GetUserName(){return _UserName;}
    string GetPassword(){return _Password;}
    int GetPermissions(){return _Permission;}
    
    bool IsEmpty(){ return _Mode == enMode::enEmptyMode;}
    bool MarkedForDelete(){return _MarkForDelete;}
    
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("MyUserData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertUserDataLineToRecord(Line);
                if(User.GetUserName() == UserName)
                {
                    return User;
                    MyFile.close();
                }
            }
        }return _GetEmptyUserData();
    }
    
    bool CheckPermission(enPermissions Permission)
    {
        if(this->GetPermissions() == enPermissions::eAll) return true;
        if((this->GetPermissions() & Permission) == Permission) return true;
        else return false;
    }
    
    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("MyUserData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertUserDataLineToRecord(Line);
                if(User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    return User;
                    MyFile.close();
                }
            }
        }return _GetEmptyUserData();
    }
    
    static vector<clsUser> GetUsersDataFromFile()
    {
        return _LoadUsersDataFromFile();
    }
    
    static clsUser AddNewUser(string UserName)
    {
        return clsUser(enAddNewMode, "", "", "", "", UserName, "", 0);
    }
    
    enum enSaveResult{svEmptyFailed = 0, svSuccess = 1, svUserExistFailed = 2};
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
                
            case enAddNewMode:
                if(clsUser::IsUserExist(_UserName)) return svUserExistFailed;
                else
                {
                    _Mode = enUpdateMode;
                    _AddNew();
                    return svSuccess;
                }
            default:
                break;
        }  return svEmptyFailed;
    }
    
    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return !User.IsEmpty();
    }
    
    bool Delete()
    {
        vector<clsUser> vUser = _LoadUsersDataFromFile();
        for(clsUser &U : vUser)
        {
            if(U.GetUserName() == _UserName)
            {
                U._MarkForDelete = true;
                break;
            }
        }_SaveUsersDataOnFile(vUser);
        *this = _GetEmptyUserData();
        return true;
    }
    
    void CreateLogRegisterFile()
    {
        string DataLine = _PrepareLogRegister();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        if(MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
        MyFile.close();
    }
    
    static vector<stLoginRegister> GetLoginRegisterRecord()
    {
        fstream MyFile;
        vector<stLoginRegister> vLoginRegister;
        MyFile.open("LoginRegister.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            stLoginRegister LoginRegister;
            while (getline(MyFile, Line))
            {
                LoginRegister = _ConvertLineToRegisterRecord(Line);
                vLoginRegister.push_back(LoginRegister);
            }MyFile.close();
        }
        return vLoginRegister;
    }
};
