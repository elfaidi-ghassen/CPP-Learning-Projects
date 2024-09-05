#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsTransferScreen : protected clsScreen
{
	static clsBankClient _readClient(string msg) {
		 
		do {
		cout << msg;
		string number = clsInputValidate::ReadString();
		clsBankClient client = clsBankClient::Find(number);
		if (!client.IsEmpty())
			return client;
		else
			std::cout << "Client not found\n";
		} while (true);
	}
public:
	static void ShowTransferScreen() {
		
		clsScreen::_DrawScreenHeader("Transfer Screen");

		clsBankClient client1 = _readClient("Account number to transfer from: ");
		client1.Print();
		clsBankClient client2 = _readClient("Account number to transfer to: ");
		client2.Print();

		int amount;
		do {
			std::cout << "Enter the amount: \n";
			amount = clsInputValidate::ReadNumber<int>();
			if (amount > client1.AccountBalance)
				std::cout << "Amount exceeds the account's balance\n";
			else
				break;
		} while (true);
		
		client1.transferTo(client2, amount);
		std::cout << "Transaction completed successfully\n";

	}
};

