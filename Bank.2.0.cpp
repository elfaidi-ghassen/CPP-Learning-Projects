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
const string CFILENAME = "clients.txt";
const string UFILENAME = "users.txt";


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
struct stUser {
	string username;
	string password;
	int permissions;

	// Flags
	bool toBeDeleted = false;
};

enum enMainMenuOption { List = 1, Add = 2, Delete = 3, Update = 4, Search = 5, Transactions = 6 , ManageUsers = 7, Logout = 8};
enum enTransMenuOption {Deposit = 1, Withdraw = 2, Total = 3, Main = 4};
enum enUserManagementOption { UserList = 1, UserAdd = 2, UserDelete = 3, UserUpdate = 4, UserFind = 5, BackToMain = 6};


enum enWithdrawDeposit {ApplyWithdraw, ApplyDeposit};
enum enPermissions {ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4,
					FindClient = 5, CanDoTransactions = 6, CanManageUsers = 7, LeaveMenu = 8};
// Functions Declaratios
void mainMenu(stUser);
void returnToMain(stUser);
void mainNavigateInto(enMainMenuOption, stUser);
void showAllClients(string);
void transactionsMenu(stUser);
void login();
void ManageUsersMenu(stUser);

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
string convertUserToString(stUser user, string sep = "#//#") {
	string result = "";
	result = result + user.username + sep;
	result = result + user.password + sep;
	result = result + to_string(user.permissions);
	return result;
}

stClient convertStringToClient(string str, string sep="#//#") {
	vector <string> elements = str::splitString(str, sep);
	stClient temp;
	temp.accNumber = elements[0];
	temp.pinCode = elements[1];
	temp.name = elements[2];
	temp.phoneNumber = elements[3];
	temp.accBalance = stod(elements[4]);
	return temp;
}
stUser convertStringToUser(string str, string sep = "#//#") {
	vector <string> elements = str::splitString(str, sep);
	stUser temp;
	temp.username = elements[0];
	temp.password = elements[1];
	temp.permissions = stoi(elements[2]);
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
			clients.push_back(convertStringToClient(line));
		}
	}
	file.close();
	return clients;
}


vector <stUser> userFileToVector(string filename) {
	fstream file;
	string line;
	vector <stUser> users;
	file.open(filename, ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			users.push_back(convertStringToUser(line));
		}
	}
	file.close();
	return users;
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

void printUsersTableHeader(int numberOfUsers) {
	printCharLine(40, ' ');
	std::cout << "User List: (" << numberOfUsers << ") user(s)";
	std::cout << "\n";
	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "|" << std::left << setw(30) << "Username";
	std::cout << "|" << std::left << setw(30) << "Password";
	std::cout << "|" << std::left << setw(20) << "Permissions";
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


void printUserRow(stUser user) {
	std::cout << "|" << std::left << setw(30) << user.username;
	std::cout << "|" << std::left << setw(30) << user.password;
	std::cout << "|" << std::left << setw(20) << user.permissions;
	std::cout << "\n";
}

void listUsers(string filename) {
	vector <stUser> users = userFileToVector(filename);
	printUsersTableHeader(users.size());
	for (int i = 0; i < users.size(); i++)
		printUserRow(users[i]);

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";

}


void printAccount(stClient client) {
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
void printAccount(stUser user) {
	std::cout << "\n";
	std::cout << "Account information:\n";
	std::cout << generateChars(50, '-') << "\n";
	std::cout << std::left << "UserName:\t" << setw(20) << user.username << "\n";
	std::cout << std::left << "Password:\t" << setw(30) << user.password << "\n";
	std::cout << std::left << "Permissions:\t" << setw(20) << user.permissions << "\n";
	std::cout << generateChars(50, '-') << "\n";
	std::cout << "\n";
}
std::optional <stUser> findUser(string username, vector <stUser> users) {
	for (stUser& user : users) {
		if (user.username == username)
			return user;
	}
	return std::nullopt;
}

std::optional <stClient> findClient(string number, vector <stClient> clients) {
	for (stClient& client : clients) {
		if (client.accNumber == number) {
			return client;
		}
	}
	return std::nullopt;
}
void printAccountDetails(string number, vector <stClient> clients)
{
	std::optional client = findClient(number, clients);

	if (client == std::nullopt)
		std::cout << "Account (" << number << ") is not found.";
	else
		printAccount(client.value());
}
void printAccountDetails(string username, vector <stUser> users)
{
	std::optional <stUser> client = findUser(username, users);
	if (client == std::nullopt)
		std::cout << "Account (" << username << ") is not found.";
	else
		printAccount(client.value());
}

void clearClientFile() {
	fstream file;
	file.open(CFILENAME, ios::out);
	file.close();
}

void clearUserFile() {
	fstream file;
	file.open(UFILENAME, ios::out);
	file.close();
}

void deleteFromFile(string clientNumber, vector <stClient>& clients) {
	clearClientFile();
	for (stClient client : clients) {
		if (client.toBeDeleted == false)
			addLineToFile(CFILENAME, convertUserToString(client));
	}
}
void deleteFromFile(string username, vector <stUser>& users) {
	clearUserFile();
	for (stUser user : users) {
		if (user.toBeDeleted == false)
			addLineToFile(UFILENAME, convertUserToString(user));
	}
}

void markForDeletions(string clientNumber, vector <stClient>& clients) {
	for (stClient& client : clients) {
		if (client.accNumber == clientNumber)
			client.toBeDeleted = true;
	}
}
void markForDeletions(string username, vector <stUser>& users) {
	for (stUser& user : users) {
		if (user.username == username)
			user.toBeDeleted = true;
	}
}



void deleteClient(string clientNumber) {
	vector <stClient> clients = convertFileIntoVector(CFILENAME);
	std::optional client = findClient(clientNumber, clients);

	if (client == std::nullopt)
		std::cout << "Account (" << clientNumber << ") is not found.";
	else {
		printAccount(client.value());
		char shouldDelete = input::readChar("Are you sure that you want to delete? [y][n]");
		if (tolower(shouldDelete) == 'y') {
			markForDeletions(clientNumber, clients);
			deleteFromFile(clientNumber, clients);
		}
	}
}
void updateAccountFile(vector <stClient>& clients, stClient updateClient) {
	clearClientFile();
	for (stClient client : clients) {
		if (client.accNumber == updateClient.accNumber)
			addLineToFile(CFILENAME, convertUserToString(updateClient));
		else
			addLineToFile(CFILENAME, convertUserToString(client));

	}
}
void updateAccountFile(vector <stUser>& users, stUser updateUser) {
	clearUserFile();
	for (stUser user : users) {
		if (user.username == updateUser.username)
			addLineToFile(UFILENAME, convertUserToString(updateUser));
		else
			addLineToFile(UFILENAME, convertUserToString(user));

	}
}
void readOnePermission(int& total, int& permissionNumber, string message, string subMessage = "y/n") {
	char choice = input::readChar(message + subMessage);
	if (tolower(choice) == 'y')
		total += permissionNumber;
	permissionNumber *= 2;
}

int readPermission() {
	int total = 0;
	int permissionNumber = 1;
	readOnePermission(total, permissionNumber, "Access to listing clients?");
	readOnePermission(total, permissionNumber, "Access to adding clients?");
	readOnePermission(total, permissionNumber, "Access to removing clients?");
	readOnePermission(total, permissionNumber, "Access to updating clients?");
	readOnePermission(total, permissionNumber, "Access to finding clients?");
	readOnePermission(total, permissionNumber, "Access to Transactions?");
	readOnePermission(total, permissionNumber, "Access to user management?");
	return total;
}

stUser createUser() {
	stUser temp;
	temp.username = input::readString("Enter accout username:");
	temp.password = input::readString("Enter password:");
	char choice = input::readChar("Do you want to grant the user full permissions? y/n");
	if (tolower(choice) == 'y')
		temp.permissions = -1;
	else {
		temp.permissions = readPermission();
	}
	return temp;
}
stUser createUser(string user) {
	stUser temp;
	temp.username = user;
	temp.password = input::readString("Enter password:");
	char choice = input::readChar("Do you want to grant the user full permissions? y/n");
	if (tolower(choice) == 'y')
		temp.permissions = -1;
	else {
		temp.permissions = readPermission();
	}
	return temp;
}

void updateInfo(string clientNumber, vector <stClient> clients) {
	optional<stClient> client = findClient(clientNumber, clients);
	if (client == nullopt)
		std::cout << "Client with number (" << clientNumber << ") is not found";
	else {
		printAccount(client.value());
		stClient updatedClient = createClient(clientNumber);
		updateAccountFile(clients, updatedClient);
	}
}

void updateInfo(string username, vector <stUser> users) {
	optional<stUser> user = findUser(username, users);
	if (user == nullopt)
		std::cout << "User with number (" << username << ") is not found";
	else {
		printAccount(user.value());
		stUser updatedUser = createUser(username);
		updateAccountFile(users, updatedUser);
	}
}


void returnToMain(stUser user) {
	std::cout << "\n";
	system("pause");
	mainMenu(user);
}
void printHeading(string text) {
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";
	std::cout << "\t\t\t\t\t" << text << "\n";
	std::cout << generateChars(SEPARATOR_LENGTH, '=') << "\n";

}
void mainNavigateInto(enMainMenuOption choice, stUser user) {
	switch (choice)
	{
	case List:
		printHeading("List Clients Screen");
		showAllClients(CFILENAME);
		returnToMain(user);
		break;
	case Add:
		printHeading("Add Client Screen");
		addClientsToFile(CFILENAME);
		returnToMain(user);
		break;
	case Delete:
		printHeading("Delete Client Screen");
		deleteClient(input::readString("Enter client number to delete:"));
		returnToMain(user);
		break;
	case Update: {
		printHeading("Update Client Screen");
		string clientNumber = input::readString("Enter client number to update:");
		updateInfo(clientNumber, convertFileIntoVector(CFILENAME));
		returnToMain(user);
		break;
	}
	case Search: {
		printHeading("Search Client Screen");
		string clientNumber = input::readString("Enter client number to search for:");
		printAccountDetails(clientNumber, convertFileIntoVector(CFILENAME));
		returnToMain(user);
		break;
	}
	case Transactions: 
		transactionsMenu(user);
		break;
	case ManageUsers:
		ManageUsersMenu(user);
		break;
		
	default:
		login();
		break;
	}
}


int permissionValue(enMainMenuOption choice) {
	return pow(2, choice - 1);
}

bool validPermission(enMainMenuOption choice, stUser user) {
	if (user.permissions == -1)
		return true;
	else if ((user.permissions & permissionValue(choice)) == permissionValue(choice))
		return true;
	else
		return false;
}


void mainMenu(stUser user) {
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
	std::cout << "\t\t [7] Manage Users\n";
	std::cout << "\t\t [8] Logout\n";


	std::cout << generateChars(80, '=') << "\n";
	enMainMenuOption choice = (enMainMenuOption) input::readIntBetween(1, 8, "Choose what you want to do: [1 to 8]");
	if (choice == Logout || validPermission(choice, user)) {
		system("cls");
		mainNavigateInto(choice, user);
	} else {
		system("cls");
		std::cout << "You don't have the permission to do that.\n";
		std::cout << "Please, contact you admin.\n";
		system("pause");
		mainMenu(user);
	}
}
void returnToTransactions(stUser user) {
	std::cout << "\n";
	system("pause");
	transactionsMenu(user);
}
void returnToManagementMenu(stUser user) {
	std::cout << "\n";
	system("pause");
	ManageUsersMenu(user);
}


void vectorIntoFile(vector <stClient> listOfClients) {
	clearClientFile();
	for (stClient client : listOfClients) {
		addLineToFile(CFILENAME, convertUserToString(client));
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
	vector <stClient> listOfClients = convertFileIntoVector(CFILENAME);
	string clientNumber = input::readString("Enter client number:");
	optional <stClient> client = findClient(clientNumber, listOfClients);

	int factor = (choice == ApplyWithdraw) ? -1 : 1;
	
	if (client == nullopt)
		std::cout << "Account (" << clientNumber << ") is not found.\n";
	else {
		printAccount(client.value());

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
	vector <stClient> clients = convertFileIntoVector(CFILENAME);
	printTotalBalancesTableHeader(clients.size());
	for (int i = 0; i < clients.size(); i++) {
		printTransactionClientRow(clients[i]);
	}

	printCharLine(SEPARATOR_LENGTH, '_');
	std::cout << "\n";
}
void transNavigateInto(enTransMenuOption choice, stUser user) {
	switch (choice)
	{
	case Deposit:
		printHeading("Deposit Screen");
		withdrawDepositMenu(enWithdrawDeposit::ApplyDeposit);
		returnToTransactions(user);
		break;
	case Withdraw:
		printHeading("Withdraw Screen");
		withdrawDepositMenu(enWithdrawDeposit::ApplyWithdraw);
		returnToTransactions(user);
		break;
	case Total:
		printHeading("Total Balances Screen");
		totalBalancesMenu();
		returnToTransactions(user);
		break;
	case Main:
		system("cls");
		mainMenu(user);
		break;
	default:
		break;
	}
	
}
void transactionsMenu(stUser user) {
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
	transNavigateInto((enTransMenuOption)choice, user);
}

std::optional <stUser> findUser(string username, string pwd, vector <stUser> users) {
	for (stUser& user : users) {
		if (user.username == username && user.password == pwd)
			return user;
	}
	return std::nullopt;
}


void addUserToFile(string filename) {
		char again = 'y';
		vector <stUser> users = userFileToVector(filename);
		do {
			stUser user = createUser();
			if (findUser(user.username, users) != nullopt) {
				std::cout << "User with this username already exists, try again.\n";
			}
			else {
				addLineToFile(filename, convertUserToString(user));
				std::cout << "User Added Successfully\n";
				again = input::readChar("Add another user? [y][n]");
			}
		} while (tolower(again) == 'y');
}

void removeUser(string username) {
	vector <stUser> users = userFileToVector(UFILENAME);
	std::optional <stUser> user = findUser(username, users);

	if (user == std::nullopt)
		std::cout << "Account (" << username << ") is not found.";
	else {
		printAccount(user.value());
		char shouldDelete = input::readChar("Are you sure that you want to delete? [y][n]");
		if (tolower(shouldDelete) == 'y') {
			markForDeletions(username, users);
			deleteFromFile(username, users);
			std::cout << "User deleted successfully.";
		}
	}
}


void userManagementNavigateInto(enUserManagementOption choice, stUser user) {
	switch (choice)
	{
	case UserList:
		printHeading("List User Screen");
		listUsers(UFILENAME);
		returnToManagementMenu(user);
		break;
	case UserAdd:
		printHeading("Add User Screen");
		addUserToFile(UFILENAME);
		returnToManagementMenu(user);
		break;
	case UserDelete: {
		printHeading("Delete User Screen");
		vector <stUser> users = userFileToVector(UFILENAME);
		removeUser(input::readString("Enter a username to delete:"));
		returnToManagementMenu(user);
		break;
	}
	case UserUpdate: {
		printHeading("Update User Screen");
		string username = input::readString("Enter username to update:");
		updateInfo(username, userFileToVector(UFILENAME));
		returnToManagementMenu(user);
		break;
	}
	case UserFind: {
		printHeading("Find User Screen");
		string username = input::readString("Enter a username to search for:");
		printAccountDetails(username, userFileToVector(UFILENAME));
		returnToManagementMenu(user);
		break;
	}
	case BackToMain:
		mainMenu(user);
		break;
	default:
		break;
	}
	
}

void ManageUsersMenu(stUser user) {
	system("cls");
	std::cout << generateChars(80, '=') << "\n";
	std::cout << generateChars(4, '\t') << "User Management Screen\n";
	std::cout << generateChars(80, '=') << "\n";
	std::cout << "\t\t [1] List Users\n";
	std::cout << "\t\t [2] Add Users\n";
	std::cout << "\t\t [3] Delete Users\n";
	std::cout << "\t\t [4] Update Users\n";
	std::cout << "\t\t [5] Find User\n";
	std::cout << "\t\t [6] Main Menu\n";
	std::cout << generateChars(80, '=') << "\n";
	int choice = input::readIntBetween(1, 6, "Choose what you want to do: [1 to 6]");
	system("cls");
	userManagementNavigateInto((enUserManagementOption)choice, user);
}

stUser readLoginUser(vector <stUser> users) {
	do {
		string username = input::readString("Enter accout username:");
		string password = input::readString("Enter password:");
		std::optional <stUser> user = findUser(username, password, users);
		if (user != nullopt)
			return user.value();
		else
			std::cout << "Wrong username/password\n";
	} while (true);
}

void login() {
	printHeading("Login Screen");
	vector <stUser> users= userFileToVector(UFILENAME);
	mainMenu(readLoginUser(users));
}

int main() {
	login();
	return 0;
}