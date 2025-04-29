#include <iostream>
#include <fstream>
#include "clsLoginScreen.h"
int main()
{
    while (true)
    {
        if(clsLoginScreen::LoginScreen() == false)
        {
            break;
        }
    }
};
