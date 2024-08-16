#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <optional>
#include "input.h"
#include "my_string_lib.h"

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
const int SEPARATOR_LENGTH = 110;
const string FILENAME = "clients.txt";

// Data Defintinos
struct stClient {
	string accNumber;
	string pinCode;
	string name;
	string phoneNumber;
	int accBalance;

	// Flags
	bool toBeDeleted = false;
};
enum enMainMenuOption { List = 1, Add = 2, Delete = 3, Update = 4, Search = 5, Transactions = 6 , End = 7 };
enum enTransMenuOption {Deposit = 1, Withdraw = 2, Total = 3, Main = 4};
enum enWithdrawDeposit {ApplyWithdraw, ApplyDeposit};
// Functions Declaratios
void mainMenu();
void returnToMain();
void mainNavigateInto(enMainMenuOption);
void showAllClients(string);
void transactionsMenu();


// Functions Definitions
stClient createClient() {
	stClient temp;
	temp.accNumber = input::readString("Enter accout number:");
	temp.pinCode = input::readString("Enter pin code:");
	temp.name = input::readString("Enter your full name:");
	temp.phoneNumber = input::readString("Enter phone number:");
	temp.accBalance = input::readInt("Enter accout balance:");
	return temp;
}
stClient createClient(string accountNumber) {
	stClient temp;
	temp.accNumber = accountNumber;
	temp.pinCode = input::readString("Enter pin code:");
	temp.name = input::readString("Enter your full name:");
	temp.phoneNumber = input::readString("Enter phone number:");
	temp.accBalance = input::readInt("Enter accout balance:");
	return temp;
}
void printUser(stClient user) {
	std::cout << "Account number: " << user.accNumber << "\n";
	std::cout << "Account pin code: " << user.pinCode << "\n";
	std::cout << "Account full name: " << user.name << "\n";
	std::cout << "Account phone number: " << user.phoneNumber << "\n";
	std::cout << "Account balance: " << user.accBalance << "\n";

}
string convertUserToString(stClient user, string sep="#//#") {
	string result = "";
	result = result + user.accNumber + sep;
	result = result + user.pinCode + sep;
	result = result + user.name + sep;
	result = result + user.phoneNumber + sep;
	result = result + to_string(user.accBalance);
	return result;
}
stClient convertStringToUser(string str, string sep="#//#") {
	vector <string> elements = str::splitString(str, sep);
	stClient temp;
	temp.accNumber = elements[0];
	temp.pinCode = elements[1];
	temp.name = elements[2];
	temp.phoneNumber = elements[3];
	temp.accBalance = stod(elements[4]);
	return temp;
}
bool clientAlreadyExists(stClient client, vector <stClient> clients) {
	for (stClient tempClient : clients) {
		if (tempClient.accNumber == client.accNumber)
			return true;
	}
	return false;
}
vector <stClient> convertFileIntoVector(string filename) {
	fstream file;
	string line;
	vector <stClient> clients;
	file.open(filename, ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			clients.push_back(convertStringToUser(line));
		}
	}
	file.close();
	return clients;
}
void addLineToFile(string filename, string line) {
	fstream file;
	file.open(filename, ios::app);
	file <<  line << "\n";
	file.close();
}
void addClientsToFile(string filename) {
	char again = 'y';
	vector <stClient> clients = convertFileIntoVector(filename);
	do {
		stClient client = createClient();
		if (clientAlreadyExists(client, clients)) {
			std::cout << "A client with account number (" << client.accNumber << ")";
			std::cout << " already exists, try again.\n";
		} else {
			addLineToFile(filename, convertUserToString(client));
			std::cout << "User Added Successfully\n";
			again = input::readChar("Add another user? [y][n]");
		}
	} while (tolower(again) == 'y');
}
void printClientsTableHeader(int numberOfClients) {
	printCharLine(40, ' ');
	std::cout << "Client List: (" << numberOfClients << ") client(s)";
	std::cout << "\n";
	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "|" << std::left << setw(20) << "Account Number";
	std::cout << "|" << std::left << setw(20) << "Pin Code";
	std::cout << "|" << std::left << setw(30) << "Client Name";
	std::cout << "|" << std::left << setw(10) << "Phone";
	std::cout << "|" << std::left << setw(10) << "Balance";
	std::cout << "\n";

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
}
void printClientRow(stClient client) {
	std::cout << "|" << std::left  << setw(20) << client.accNumber;
	std::cout << "|" << std::left  << setw(20) << client.pinCode;
	std::cout << "|" << std::left  << setw(30) << client.name;
	std::cout << "|" << std::left  << setw(10) << client.phoneNumber;
	std::cout << "|" << std::left  << setw(10) << client.accBalance;
	std::cout << "\n";
}
void showAllClients(string filename) {
	vector <stClient> clients = convertFileIntoVector(filename);
	printClientsTableHeader(clients.size());
	for (int i = 0; i < clients.size(); i++) {
		printClientRow(clients[i]);
	}

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
	
}
void printAccountInfo(stClient client) {
	std::cout << "\n";
	std::cout << "Account information:\n";
	std::cout << generateChars(50, '-') << "\n";
	std::cout << std::left << "Account Number:\t" << setw(20) << client.accNumber << "\n";
	std::cout << std::left << "PIN:\t" << setw(20) << client.pinCode << "\n";
	std::cout << std::left << "Name:\t" << setw(30) << client.name << "\n";
	std::cout << std::left << "Phone Number:\t" << setw(10) << client.phoneNumber << "\n";
	std::cout << std::left << "Balance:\t" << setw(10) << client.accBalance << "\n";
	std::cout << generateChars(50, '-') << "\n";
	std::cout << "\n";
}
std::optional <stClient> findClient(string number, vector <stClient> clients) {
	for (stClient& client : clients) {
		if (client.accNumber == number) {
			return client;
		}
	}
	return std::nullopt;
}
void printClientDetails(string number, vector <stClient> clients)
{
	std::optional client = findClient(number, clients);

	if (client == std::nullopt)
		std::cout << "Account (" << number << ") is not found.";
	else
		printAccountInfo(client.value());
}
void clearFile() {
	fstream file;
	file.open(FILENAME, ios::out);
	file.close();
}
void deleteClientFromFile(string clientNumber, vector <stClient>& clients) {
	clearFile();
	for (stClient client : clients) {
		if (client.toBeDeleted == false)
			addLineToFile(FILENAME, convertUserToString(client));
	}
}
void markClientsForDeletions(string clientNumber, vector <stClient>& clients) {
	for (stClient& client : clients) {
		if (client.accNumber == clientNumber)
			client.toBeDeleted = true;
	}
}
void deleteClient(string clientNumber) {
	vector <stClient> clients = convertFileIntoVector(FILENAME);
	std::optional client = findClient(clientNumber, clients);

	if (client == std::nullopt)
		std::cout << "Account (" << clientNumber << ") is not found.";
	else {
		printAccountInfo(client.value());
		char shouldDelete = input::readChar("Are you sure that you want to delete? [y][n]");
		if (tolower(shouldDelete) == 'y') {
			markClientsForDeletions(clientNumber, clients);
			deleteClientFromFile(clientNumber, clients);
		}
	}
}
void updateClientsFile(vector <stClient>& clients, stClient updateClient) {
	clearFile();
	for (stClient client : clients) {
		if (client.accNumber == updateClient.accNumber)
			addLineToFile(FILENAME, convertUserToString(updateClient));
		else
			addLineToFile(FILENAME, convertUserToString(client));

	}
}
void updateClientInfo(string clientNumber, vector <stClient> clients) {
	optional<stClient> client = findClient(clientNumber, clients);
	if (client == nullopt)
		std::cout << "Client with number (" << clientNumber << ") is not found";
	else {
		printAccountInfo(client.value());
		stClient updatedClient = createClient(clientNumber);
		updateClientsFile(clients, updatedClient);
	}
		
	
}
void returnToMain() {
	std::cout << "\n";
	system("pause");
	mainMenu();
}
void printHeading(string text) {
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";
	std::cout << "\t\t\t\t\t" << text << "\n";
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";

}
void mainNavigateInto(enMainMenuOption choice) {
	switch (choice)
	{
	case List:
		printHeading("List Clients Screen");
		showAllClients(FILENAME);
		returnToMain();
		break;
	case Add:
		printHeading("Add Client Screen");
		addClientsToFile(FILENAME);
		returnToMain();
		break;
	case Delete:
		printHeading("Delete Client Screen");
		deleteClient(input::readString("Enter client number to delete:"));
		returnToMain();
		break;
	case Update: {
		printHeading("Update Client Screen");
		string clientNumber = input::readString("Enter client number to update:");
		updateClientInfo(clientNumber, convertFileIntoVector(FILENAME));
		returnToMain();
		break;
	}
	case Search: {
		printHeading("Search Client Screen");
		string clientNumber = input::readString("Enter client number to update:");
		printClientDetails(clientNumber, convertFileIntoVector(FILENAME));
		returnToMain();
		break;
	}
	case Transactions: 
		transactionsMenu();
		break;
	default:
		std::cout << "GOODBYE :)\n";
		break;
	}
}

void mainMenu() {
	system("cls");
	std::cout << generateChars(80, '=') << "\n";
	std::cout << generateChars(4, '\t') << "Main Menu Screen\n";
	std::cout << generateChars(80, '=') << "\n";
	std::cout << "\t\t [1] Show Client List\n";
	std::cout << "\t\t [2] Add New Client\n";
	std::cout << "\t\t [3] Delete Client\n";
	std::cout << "\t\t [4] Update Client Info\n";
	std::cout << "\t\t [5] Find Client\n";
	std::cout << "\t\t [6] Transactions\n";
	std::cout << "\t\t [7] Exit\n";

	std::cout << generateChars(80, '=') << "\n";
	int choice = input::readIntBetween(1, 7, "Choose what you want to do: [1 to 7]");
	system("cls");
	mainNavigateInto((enMainMenuOption)choice);

}
void returnToTransactions() {
	std::cout << "\n";
	system("pause");
	transactionsMenu();
}
void vectorIntoFile(vector <stClient> listOfClients) {
	clearFile();
	for (stClient client : listOfClients) {
		addLineToFile(FILENAME, convertUserToString(client));
	}
}
void addToBalance(int amount, string clientNumber, vector <stClient> listOfClients) {
	for (stClient& client : listOfClients) {
		if (client.accNumber == clientNumber) {
			client.accBalance += amount;
			break;
		}
	}
	vectorIntoFile(listOfClients);
}
void withdrawDepositMenu(enWithdrawDeposit choice) {
	vector <stClient> listOfClients = convertFileIntoVector(FILENAME);
	string clientNumber = input::readString("Enter client number:");
	optional <stClient> client = findClient(clientNumber, listOfClients);

	int factor = (choice == ApplyWithdraw) ? -1 : 1;
	
	if (client == nullopt)
		std::cout << "Account (" << clientNumber << ") is not found.\n";
	else {
		printAccountInfo(client.value());

		int amount = input::readPositiveInt("Enter amount (>= 0): ");

		if (choice == ApplyWithdraw && client.value().accBalance < amount)
			std::cout << "Sorry, not enough balance\n";

		else if (tolower(input::readChar("Are you sure? [y][n]")) == 'y') {
			addToBalance(amount * factor, client.value().accNumber, listOfClients);
			std::cout << "Transaction completed successfully.\n";
			std::cout << "New Balance:" << client.value().accBalance + (amount * factor) << "\n";
		}
	}
}


void printTotalBalancesTableHeader(int numberOfClients) {
	printCharLine(40, ' ');
	std::cout << "Client List: (" << numberOfClients << ") client(s)";
	std::cout << "\n";
	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "|" << std::left << setw(20) << "Account Number";
	std::cout << "|" << std::left << setw(30) << "Client Name";
	std::cout << "|" << std::left << setw(30) << "Balance";
	std::cout << "\n";

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
}
void printTransactionClientRow(stClient client) {
	std::cout << "|" << std::left << setw(20) << client.accNumber;
	std::cout << "|" << std::left << setw(30) << client.name;
	std::cout << "|" << std::left << setw(30) << client.accBalance;
	std::cout << "\n";
}
void totalBalancesMenu() {
	vector <stClient> clients = convertFileIntoVector(FILENAME);
	printTotalBalancesTableHeader(clients.size());
	for (int i = 0; i < clients.size(); i++) {
		printTransactionClientRow(clients[i]);
	}

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
}
void transNavigateInto(enTransMenuOption choice) {
	switch (choice)
	{
	case Deposit:
		printHeading("Deposit Screen");
		withdrawDepositMenu(enWithdrawDeposit::ApplyDeposit);
		returnToTransactions();
		break;
	case Withdraw:
		printHeading("Withdraw Screen");
		withdrawDepositMenu(enWithdrawDeposit::ApplyWithdraw);
		returnToTransactions();
		break;
	case Total:
		printHeading("Total Balances Screen");
		totalBalancesMenu();
		returnToTransactions();
		break;
	case Main:
		system("cls");
		mainMenu();
		break;
	default:
		break;
	}
	
}
void transactionsMenu() {
	system("cls");
	std::cout << generateChars(80, '=') << "\n";
	std::cout << generateChars(4, '\t') << "Transaction Menu Screen\n";
	std::cout << generateChars(80, '=') << "\n";
	std::cout << "\t\t [1] Deposit\n";
	std::cout << "\t\t [2] Withdraw\n";
	std::cout << "\t\t [3] Total Balances\n";
	std::cout << "\t\t [4] Main Menu\n";
	std::cout << generateChars(80, '=') << "\n";
	int choice = input::readIntBetween(1, 4, "Choose what you want to do: [1 to 4]");
	system("cls");
	transNavigateInto((enTransMenuOption)choice);
}


int main() {
	mainMenu();
	return 0;
}