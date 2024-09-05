#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyScreen : public clsScreen
{
	static clsCurrency _readCurrency() {
		std::cout << "Enter currency code: ";
		string code = clsInputValidate::ReadString();
		clsCurrency currency = clsCurrency::FindByCode(code);
		while (currency.IsEmpty()) {
			std::cout << "Not Found\n";
			std::cout << "Enter currency code: ";
			string code = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCode(code);

		}
		return currency;
	}
public:
	static void ShowUpdateCurrencyScreen() {
		clsScreen::_DrawScreenHeader("Update Currency Screen");
		clsCurrency currency = _readCurrency();
		currency.printInfo();

		std::cout << "Enter new rate: ";
		float newRate = clsInputValidate::ReadNumber<float>();

		currency.UpdateRate(newRate);
		std::cout << "Rate updated successfully.\n";
		currency.printInfo();

	}
};

