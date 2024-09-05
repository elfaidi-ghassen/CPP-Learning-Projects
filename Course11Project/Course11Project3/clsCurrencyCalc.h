#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrencyCalc : public clsScreen
{
	static clsCurrency _readCurrency() {
		string code = clsInputValidate::ReadString();
		clsCurrency currency = clsCurrency::FindByCode(code);
		while (currency.IsEmpty()) {
			std::cout << "Not Found\n";
			std::cout << "Again: ";
			string code = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCode(code);

		}
		return currency;
	}
public:
	static void ShowCurrencyCalc() {
		clsScreen::_DrawScreenHeader("Convert Currencies");
		char choice;


		do {
			std::cout << "Enter currency1 code: \n";
			clsCurrency currency1 = _readCurrency();
			std::cout << "Enter currency2 code: \n";
			clsCurrency currency2 = _readCurrency();

			std::cout << "Enter amount: \n";
			float amount = clsInputValidate::ReadNumber<float>();

			std::cout << "Convert from:\n";
			currency1.printInfo();

			std::cout << amount << currency1.CurrencyCode();
			std::cout << " = " << amount * currency1.convertInto(currency2);
			std::cout << currency2.CurrencyCode() << "\n";


			std::cout << "Want to do another calculation? [y/n]\n";
			std::cin >> choice;
		} while (choice == 'Y' || choice == 'y');

	}
};

