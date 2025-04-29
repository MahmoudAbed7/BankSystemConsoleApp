#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
using namespace std;

class clsClient : public clsPerson
{
private:
    
    enum enMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _Acc_Number;
    string _PinCode;
    float _Acc_Balance;
    bool _MarkForDelete = false;
    
    static string _ConvertRecordToClientLine(clsClient Client, string Spaces = "/##/")
    {
        string DataLine;
        DataLine += Client.GetFirstName() + Spaces;
        DataLine += Client.GetLastName() + Spaces;
        DataLine += Client.GetEmail() + Spaces;
        DataLine += Client.GetPhone() + Spaces;
        DataLine += Client.GetAccountNumber() + Spaces;
        DataLine += Client.GetPinCode() + Spaces;
        DataLine += to_string(Client.GetAccountBalance());
        return DataLine;
    }
    
    string _PrepareTransferLog(clsClient To, float Amount, string UserName, string Spaces = "/##/")
    {
        string TransferLog;
        TransferLog += clsDate::GetSystemDateTimeString() + Spaces;
        TransferLog += GetAccountNumber() + Spaces;
        TransferLog += To.GetAccountNumber() + Spaces;
        TransferLog += to_string(Amount) + Spaces;
        TransferLog += to_string(GetAccountBalance()) + Spaces;
        TransferLog += to_string(To.GetAccountBalance()) + Spaces;
        TransferLog += UserName;
        return TransferLog;
    }
    
    static clsClient _ConvertClientDataToRecord(string Text, string Spaces = "/##/")
    {
        vector<string> vClient = clsString::Split(Text, Spaces);
        clsClient Client(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stof(vClient[6]));
        return Client;
    }
    
    public: struct stTransferLog;
    static stTransferLog _ConvertTransferLogToRecord(string Text, string Spaces = "/##/")
    {
        stTransferLog TransferLog;
        vector<string> vTransferLog = clsString::Split(Text, Spaces);
        TransferLog.TimeDate = vTransferLog[0];
        TransferLog.SrcAccountNumber = vTransferLog[1];
        TransferLog.DesAccountNumber = vTransferLog[2];
        TransferLog.Amount = stof(vTransferLog[3]);
        TransferLog.SrcAmount = stof(vTransferLog[4]);
        TransferLog.DesAmount = stof(vTransferLog[5]);
        TransferLog.UserName = vTransferLog[6];
        return TransferLog;
    }
    
    void _RegisterTransferLog(float Amount, clsClient To,string UserName)
    {
        fstream MyFile;
        string DataLine = _PrepareTransferLog(To, Amount, UserName);
        MyFile.open("MyTransferLog.txt", ios::out | ios::app);
        if(MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }
    
    static vector<clsClient> _LoadClientDataFromFile()
    {
        fstream MyFile;
        vector<clsClient> vClient;
        MyFile.open("MyClientData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsClient Client = _ConvertClientDataToRecord(Line);
                vClient.push_back(Client);
            }MyFile.close();
        }return vClient;
    }
    
    static vector<stTransferLog> _LoadTransferLogFromFile()
    {
        fstream MyFile;
        vector<stTransferLog> vTransferLog;
        MyFile.open("MyTransferLog.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stTransferLog TransferLog = _ConvertTransferLogToRecord(Line);
                vTransferLog.push_back(TransferLog);
            }MyFile.close();
        }return vTransferLog;
    }
    
    static void _SaveClientDataOnFile(vector<clsClient> vClient)
    {
        fstream MyFile;
        MyFile.open("MyClientData.txt", ios::out);
        if(MyFile.is_open())
        {
            string DataLine;
            for(clsClient &C : vClient)
            {
                if(!C.MarkedForDelete())
                {
                    DataLine = _ConvertRecordToClientLine(C);
                    MyFile << DataLine << endl;
                }
            }MyFile.close();
        }
    }
    
    static void _AddClientDataToFile(string ClientData)
    {
        fstream MyFile;
        MyFile.open("MyClientData.txt", ios::out | ios::app);
        if(MyFile.is_open())
        {
            
            MyFile << ClientData << endl;
            MyFile.close();
        }
    }
    
    void _AddNew()
    {
        _AddClientDataToFile(_ConvertRecordToClientLine(*this));
    }
    
    void _Update()
    {
        vector<clsClient> vClient = _LoadClientDataFromFile();
        for(clsClient &C : vClient)
        {
            if(C.GetAccountNumber() == _Acc_Number)
            {
                C = *this;
                break;
            }
        }_SaveClientDataOnFile(vClient);
    }
    static clsClient _GetEmptyClientData()
    {
        return clsClient(EmptyMode, "", "", "", "", "", "", 0);
    }
    
   
    
public:
    clsClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _Acc_Number = AccountNumber;
        _PinCode = PinCode;
        _Acc_Balance = AccountBalance;
    }
    
    struct stTransferLog
    {
        string TimeDate;
        string SrcAccountNumber;
        string DesAccountNumber;
        float Amount;
        float SrcAmount;
        float DesAmount;
        string UserName;
    };
    
    
    //Setter
    void SetPinCode(string PinCode){_PinCode = PinCode;}
    void SetAccountBalance(float AccountBalance){_Acc_Balance = AccountBalance;}
    //Getter
    string GetAccountNumber(){return _Acc_Number;}
    string GetPinCode(){return _PinCode;}
    float GetAccountBalance(){return _Acc_Balance;}
    
    bool IsEmpty(){return _Mode == EmptyMode;}
    bool MarkedForDelete(){return _MarkForDelete;}
    
    static clsClient Find(string AccountNumber)
    {
        fstream MyFile;
        vector<clsClient> vClient = _LoadClientDataFromFile();
        MyFile.open("MyClientData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsClient Client = _ConvertClientDataToRecord(Line);
                if(Client.GetAccountNumber() == AccountNumber)
                {
                    return Client;
                    MyFile.close();
                }
            }
        }return _GetEmptyClientData();
    }
    
    static clsClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        vector<clsClient> vClient = _LoadClientDataFromFile();
        MyFile.open("MyClientData.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsClient Client = _ConvertClientDataToRecord(Line);
                if(Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    return Client;
                    MyFile.close();
                }
            }
            
        }return _GetEmptyClientData();
    }
    
    static bool IsClientExist(string AccountNumber)
    {
        clsClient Client = clsClient::Find(AccountNumber);
        return !Client.IsEmpty();
    }
    enum enSaveResults{svEmptyError = 0, svSuccess = 1, svAccountNumberExistError = 2};
    enSaveResults Save()
    {
        switch (_Mode)
        {
            case EmptyMode:
                if(IsEmpty())
                    return svEmptyError;
                break;
                
            case AddNewMode:
                if(IsClientExist(_Acc_Number))
                    return svAccountNumberExistError;
                else
                {
                    _Mode = UpdateMode;
                    _AddNew();
                    return svSuccess;
                }
                break;
                
            case UpdateMode:
                _Update();
                return svSuccess;
            default:
                break;
        }
        return svEmptyError;
    }
    
    static vector<clsClient> GetClientData()
    {
        return _LoadClientDataFromFile();
    }
    
    static clsClient AddNewClient(string AccountNumber)
    {
        return clsClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    bool Delete()
    {
        vector<clsClient> vClient = _LoadClientDataFromFile();
        for(clsClient &C : vClient)
        {
            if(C.GetAccountNumber() == _Acc_Number)
            {
                C._MarkForDelete = true;
                break;
            }
        }_SaveClientDataOnFile(vClient);
         *this = _GetEmptyClientData();
         return true;
    }
    
    void Deposite(float Amount)
    {
        _Acc_Balance += Amount;
        Save();
    }
    
    bool Withdraw(float Amount)
    {
        if(Amount > _Acc_Balance) return false;
        _Acc_Balance -= Amount;
        Save();
        return true;
    }

    
    bool Transfer(float Amount, clsClient &To, string UserName)
    {
        if(Amount > GetAccountBalance())
        {
            return false;
        }
        Withdraw(Amount);
        To.Deposite(Amount);
        _RegisterTransferLog(Amount, To, UserName);
        return true;
        
    }
    
    static float GetTotalBalances()
    {
        vector<clsClient> vClient = GetClientData();
        float TotalBalances = 0;
        for(clsClient &C : vClient)
        {
            TotalBalances += C.GetAccountBalance();
        }
        return TotalBalances;
    }
    
    static vector<stTransferLog> GetTransferLog()
    {
        return _LoadTransferLogFromFile();
    }
};
