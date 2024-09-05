#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"
class clsFindCurrencyScreen : public clsScreen
{
	enum enFindOption {fCode = 1, fCountry = 2};
	static void _printCurrencyInfo(clsCurrency currency) {
		if (!currency.IsEmpty())
			currency.printInfo();
		else
			std::cout << "Not Found\n";
	}
public:
	static void ShowFindCurrencyScreen() {
		clsScreen::_DrawScreenHeader("Find Currency Screen");

		std::cout << "Find by: [1] Code or [2] Country\n";
		short choice = clsInputValidate::ReadNumberBetween<short>(1, 2);


		switch ((enFindOption)choice) {
		case fCode: {
			std::cout << "Enter code: ";
			string code = clsInputValidate::ReadString();
			clsCurrency currency = clsCurrency::FindByCode(code);
			_printCurrencyInfo(currency);
			break;
		}
		case fCountry: {
			std::cout << "Enter country: ";
			string country = clsInputValidate::ReadString();
			clsCurrency currency = clsCurrency::FindByCountry(country);
			_printCurrencyInfo(currency);
			break;

		}
		}
		
	}
};

