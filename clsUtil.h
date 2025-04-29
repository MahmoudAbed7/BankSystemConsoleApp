#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsUtil {
  
public:
    enum enCharType{SmallLetter = 1, CapitalLetter = 2, Digit = 3, MixChar = 4, SpecialChar = 5};
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }
    static int RandomNumber(int From, int To)
    {
        int Random = rand() % (To - From + 1) + From;
        return Random;
    }
    
    static char RandomChar(enCharType CharType)
    {
        switch (CharType) {
            case SmallLetter:
                return (char)RandomNumber(97, 122);
                break;
            case CapitalLetter:
                return (char)RandomNumber(65, 90);
                break;
            case Digit:
                return (char)RandomNumber(48, 57);
                break;
            case SpecialChar:
                return (char)RandomNumber(33, 47);
                break;
            default:
                return (char)RandomNumber(65, 90);
                break;
        }
    }
    static string GenerateWord(enCharType CharType, short WordLength)
    {
        string Word = "";
        for (short i = 1; i <= WordLength; i++)
        {
            Word += RandomChar(CharType);
        }return Word;
    }
    
    static string Generatekey(enCharType CharType)
    {
        string Key = "";
        Key += GenerateWord(CharType, 8) + "-";
        Key += GenerateWord(CharType, 8) + "-";
        Key += GenerateWord(CharType, 8) + "-";
        Key += GenerateWord(CharType, 8);
        return Key;
    }
    static void Generatekeys(short NumOfKeys,enCharType CharType)
    {
        for (short i = 1; i <= NumOfKeys; i++)
        {
            cout << "Key " << i << ": " << Generatekey(CharType) << endl;
        }
    }
    
    static void Swap(int &A, int &B)
    {
        int Temp = B;
        B = A;
        A = Temp;
    }
    
    static void Swap(double &A, double &B)
    {
        double Temp = B;
        B = A;
        A = Temp;
    }
    
    static void Swap(string &A, string &B)
    {
        string Temp = B;
        B = A;
        A = Temp;
    }
    static void Swap(clsDate &A, clsDate &B)
    {
        clsDate Temp = B;
        B = A;
        A = Temp;
    }
    
    static void SuffleArray(int Array[], int ArrayLen)
    {
        Swap(Array[RandomNumber(1, ArrayLen) - 1], Array[RandomNumber(1, ArrayLen) - 1]);
    }
    
    static void SuffleArray(string Array[], int ArrayLen)
    {
        Swap(Array[RandomNumber(1, ArrayLen) - 1], Array[RandomNumber(1, ArrayLen) - 1]);
    }
    
    static void FillArrayWithRandomNumber(int Arr[], int Len, int From, int To)
    {
        for (int i = 0; i < Len; i++)
        {
            Arr[i] = RandomNumber(From, To);
        }
    }
    
    static void FillArrayWithRandomWord(string Arr[], int ArrLen, enCharType CharType, int WordLen)
    {
        for (int i = 0; i < ArrLen; i++)
        {
            Arr[i] = GenerateWord(CharType, WordLen);
        }
    }
    
    static void FillArrayWithRandomKeys(string Arr[], int ArrLen, enCharType CharType)
    {
        for (int i = 0; i < ArrLen; i++)
        {
            Arr[i] = Generatekey(CharType);
        }
    }
    
    static string Tabs(int NumOfTabs)
    {
        string Tab = "";
        for (short i = 1; i <= NumOfTabs; i++)
        {
            Tab += "\t";
        }return Tab;
    }
    
    static string EncriptionText(string Text, int EncriptionKey = 2)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncriptionKey);
        }return Text;
    }
    
    static string DecriptionText(string Text, int EncriptionKey = 2)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncriptionKey);
        }return Text;
    }
    
    static string NumberToText(int Number)
     {

         if (Number == 0)
         {
             return "";
         }

         if (Number >= 1 && Number <= 19)
         {
             string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
         "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
           "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

             return  arr[Number] + " ";

         }

         if (Number >= 20 && Number <= 99)
         {
             string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
             return  arr[Number / 10] + " " + NumberToText(Number % 10);
         }

         if (Number >= 100 && Number <= 199)
         {
             return  "One Hundred " + NumberToText(Number % 100);
         }

         if (Number >= 200 && Number <= 999)
         {
             return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
         }

         if (Number >= 1000 && Number <= 1999)
         {
             return  "One Thousand " + NumberToText(Number % 1000);
         }

         if (Number >= 2000 && Number <= 999999)
         {
             return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
         }

         if (Number >= 1000000 && Number <= 1999999)
         {
             return  "One Million " + NumberToText(Number % 1000000);
         }

         if (Number >= 2000000 && Number <= 999999999)
         {
             return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
         }

         if (Number >= 1000000000 && Number <= 1999999999)
         {
             return  "One Billion " + NumberToText(Number % 1000000000);
         }
         else
         {
             return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
         }


     }


};
