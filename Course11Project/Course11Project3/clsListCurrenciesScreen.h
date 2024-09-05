#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"

class clsListCurrenciesScreen : public clsScreen
{

    static void _PrintClientRecordLine(clsCurrency curr) {
        cout << setw(8) << left << "" << "| " << left << setw(30) << curr.Country();
        cout << "| " << left << setw(20) << curr.CurrencyCode();
        cout << "| " << left << setw(20) << curr.CurrencyName();
        cout << "| " << left << setw(20) << curr.Rate();
    }
public:
	static void clsListCurrencies() {
		vector <clsCurrency> currencies = clsCurrency::loadCurrencies();
        _DrawScreenHeader("List Currencies");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(20) << "Code";
        cout << "| " << left << setw(20) << "Name";
        cout << "| " << left << setw(20) << "Rate(/$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (currencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency curr : currencies)
            {

                _PrintClientRecordLine(curr);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	
	}

};

