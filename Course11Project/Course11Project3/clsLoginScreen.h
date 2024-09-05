#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainMenu.h"
#include "Global.h"
#include <fstream>

using std::to_string;

class clsLoginScreen : protected clsScreen
{
private:
    

    static bool _Login()
    {
        short tries = 3;
        bool LoginFaild = false;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\t\t\t\t\tInvlaid Username/Password!\n";
                tries--;
                string sNoS = tries > 1 ? "s" : "";
                std::cout << "\t\t\t\t\tYou have " << tries << " trie" << sNoS << " to login\n\n";
            }
            if (tries == 0) {
                std::cout << "\t\t\t\t\tYou are locked after 3 wrong tries\n";
                return false;
            }


            cout << "\t\t\t\t\tUsername? ";
            cin >> Username;

            cout << "\t\t\t\t\tEnter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.storeLoginLogs();

        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

