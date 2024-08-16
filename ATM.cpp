#include <iostream>
#include <fstream>
#include <vector>
#include "input.h"
#include "my_string_lib.h"
#include <optional>
#include <iomanip>

using std::string,
	std::vector,
	std::fstream,
	std::ios,
	std::optional,
	std::nullopt,
	std::to_string,
	std::setw,
	str::printCharLine,
	str::generateChars;

// Constants
const string CLIENTS_FILE_PATH = "clients.txt";
const int SEPARATOR_LENGTH = 80;

// Data defintions
struct stClient {
	string number;
	string pin;
	int balance = 0;
};
enum enMainMenuOption { QuickW = 1, NormalW = 2, Balance = 3, Deposit = 4, Logout = 5 };

// Global Variables
stClient currentClient;

// Functions
void mainMenu();


void printHeading(string text) {
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";
	std::cout << "\t\t\t\t\t" << text << "\n";
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";

}
stClient stringToClient(string line) {
	vector <string> parts = str::splitString(line, "#//#");
	stClient client;
	client.number = parts[0];
	client.pin= parts[1];
	client.balance = stoi(parts[2]);
	return client;
}

vector <stClient> clientsFileToVector() {
	vector <stClient> clients;
	fstream file;
	file.open(CLIENTS_FILE_PATH, ios::in);
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			clients.push_back(stringToClient(line));
		}
	}
	return clients;
}

optional <stClient> findClient(string number, string pwd) {
	vector <stClient> clients = clientsFileToVector();
	for (stClient client : clients) {
		if (client.number == number && client.pin == pwd)
			return client;
	}
	return nullopt;
}




void login() {
	printHeading("Login Screen");
	optional <stClient> client;
	string name, pwd;
	do {
		name = input::readString("Enter card number: ");
		pwd= input::readString("Enter password:");
		client = findClient(name, pwd);
		if (client != nullopt) {
			currentClient = client.value();
			mainMenu();
			break;
		}
		else {
			std::cout << "Wrong password/number\n";
		}
	} while (true);
}

int readWithdrawAmount() {
	do {
		int amount = input::readInt("Enter an amount:");
		if (amount % 5 != 0) {
			std::cout << "Must be a multiple of 5";
		}
		else {
			return amount;
			break;
		}
	} while (true);
}


void clearClientsFile() {
	fstream file;
	file.open(CLIENTS_FILE_PATH, ios::out);
	file.close();
}

string clientToString(stClient client, string sep) {
	string result = "";
	result = result + client.number + sep;
	result = result + client.pin + sep;
	result = result + to_string(client.balance);
	return result;
}

void addLineInClientsFile(string line) {
	fstream file;
	file.open(CLIENTS_FILE_PATH, ios::app);
	file << line << "\n";
	file.close();
}

void vectorIntoClientsFile(vector <stClient> clients) {
	clearClientsFile();
	for (stClient client : clients) {
		// Opening a file is slow, so it's probably better to open it just once!
		addLineInClientsFile(clientToString(client, "#//#"));
	}
}

void setBalance(stClient currentClient, int amount) {
	vector <stClient> clients = clientsFileToVector();
	for (stClient& client : clients) {
		if (client.number == currentClient.number)
			client.balance = currentClient.balance;
	}
	vectorIntoClientsFile(clients);
}


void normalWithdrawMenu(int withdrawAmount) {
	if (withdrawAmount > currentClient.balance) {
		std::cout << "Not enough balance: you have " << currentClient.balance << "\n";
	} else {
		char answer = input::readChar("Are you sure you want complete this transaction? y/n");
		if (tolower(answer) == 'y') {
			currentClient.balance = currentClient.balance - withdrawAmount;
			setBalance(currentClient, currentClient.balance - withdrawAmount);
		}
	}
}


void printQuickWithdrawOptions() {
	std::cout << "\t[1] " << std::left << setw(10) << "20\t";
	std::cout << "\t[2] " << std::left << setw(10) << "50\n";

	std::cout << "\t[3] " << std::left << setw(10) << "100\t";
	std::cout << "\t[4] " << std::left << setw(10) << "200\n";

	std::cout << "\t[5] " << std::left << setw(10) << "400\t";
	std::cout << "\t[6] " << std::left << setw(10) << "600\n";

	std::cout << "\t[7] " << std::left << setw(10) << "800\t";
	std::cout << "\t[8] " << std::left << setw(10) << "1000\n";
	std::cout << "\t[9] " << std::left << setw(10) << "Exit\n";


}

void quickWithdrawMenu() {
	system("cls");
	printHeading("Quick Withdraw Screen");
	printQuickWithdrawOptions();
	int choice = input::readIntBetween(1, 9, "Choose an option: [1-9]");
	if (choice == 9)
		mainMenu();
	else {
		int options[] = { 20, 50, 100, 200, 400, 600, 800, 1000 };
		normalWithdrawMenu(options[choice - 1]);
	}
}

void showBalanceMenu() {
	std::cout << "You balance is: " << currentClient.balance << "\n";
}


void mainNavigateInto(enMainMenuOption choice) {
	system("cls");
	switch (choice)
	{
	case QuickW: {
		quickWithdrawMenu();
		system("pause");
		mainMenu();
		break;
	}
	case NormalW: {
		printHeading("Normal Withdraw Screen");
		int withdrawAmount = readWithdrawAmount();
		normalWithdrawMenu(withdrawAmount);
		system("pause");
		mainMenu();
		break;
	}
	case Balance: {
		printHeading("Your Balance");
		showBalanceMenu();
		system("pause");
		mainMenu();
		break;
	}
	case Deposit: {
		printHeading("Deposit");
		int amount = input::readPositiveInt("Enter amount:");
		currentClient.balance += amount;
		setBalance(currentClient, currentClient.balance + amount);
		system("pause");
		mainMenu();
		break;
	}
	case Logout:
		login();
	}
}

void mainMenu() {
	system("cls");
	std::cout << generateChars(80, '=') << "\n";
	std::cout << generateChars(4, '\t') << "Main Menu Screen\n";
	std::cout << generateChars(80, '=') << "\n";
	std::cout << "\t\t [1] Quick Withdraw\n";
	std::cout << "\t\t [2] Normal Withdraw\n";
	std::cout << "\t\t [3] Check Balance\n";
	std::cout << "\t\t [4] Deposit\n";
	std::cout << "\t\t [5] Logout\n";
	std::cout << generateChars(80, '=') << "\n";

	enMainMenuOption choice = (enMainMenuOption)input::readIntBetween(1, 5, "Choose what you want to do: [1 to 5]");	
	mainNavigateInto(choice);
}

int main() {
	login();

	return 0;
}