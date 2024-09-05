#pragma once
#include "clsScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalc.h"

class clsCurrencyMenu : public clsScreen
{
    enum enCurrencyMenuOption {
        currList = 1, currFind = 2, currUpdate = 3, currCalculator = 4, currMain = 5
    };

    static void _returnToCurrencyScreen() {
        system("pause");
        clsCurrencyMenu::ShowCurrencyMenu();
    }

    static void _showListScreen() {
        clsListCurrenciesScreen::clsListCurrencies();
    }
    static void _showFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _showUpdateCurrencyScreen() {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }
    static void _showCurrencyCalcScreen() {
        clsCurrencyCalc::ShowCurrencyCalc();
    }



    static void _PerformTransactionsMenueOption(enCurrencyMenuOption option) {
        switch (option)
        {
        case clsCurrencyMenu::currList:
            system("cls");
            _showListScreen();
            _returnToCurrencyScreen();
            break;
        case clsCurrencyMenu::currFind:
            system("cls");
            _showFindCurrencyScreen();
            _returnToCurrencyScreen();
            break;
        case clsCurrencyMenu::currUpdate:
            system("cls");
            _showUpdateCurrencyScreen();
            _returnToCurrencyScreen();
            break;
        case clsCurrencyMenu::currCalculator:
            system("cls");
            _showCurrencyCalcScreen();
            _returnToCurrencyScreen();
        break;
        case clsCurrencyMenu::currMain:
            break;
        }

    }
    static short _ReadTransactionsMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

public:
	static void ShowCurrencyMenu() {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrency))
            return;
        

        system("cls");
        _DrawScreenHeader("\tCurrency Exchange Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find currencies.\n";
        cout << setw(37) << left << "" << "\t[3] Update rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enCurrencyMenuOption)_ReadTransactionsMenueOption());
    }
	
};

