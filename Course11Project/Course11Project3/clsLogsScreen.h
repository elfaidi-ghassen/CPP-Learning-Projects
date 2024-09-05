#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <vector>;
#include <string>;

using std::to_string;

class clsLogsScreen : protected clsScreen
{
    static void _printLogsLine(stLog log) {
        cout << setw(8) << left << "" << "| " << left << setw(30) << log.date;;
        cout << "| " << left << setw(20) << log.userName;
        cout << "| " << left << setw(30) << log.password;
        cout << "| " << left << setw(10) << log.permission;
        cout << "\n";
    }

public:
	static void ShowLogsScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pSeeLogs))
        {
            return;// this will exit the function and it will not continue
        }


		vector <stLog> logs = clsUser::loadLoginLogs();

		string subtitle = to_string(logs.size()) + " Record(s) found\n";
		clsScreen::_DrawScreenHeader("Logs", subtitle);
	
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(30) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (logs.size() == 0)
            cout << "\t\t\t\tNo data Available In the System!";
        else {
        
            for (stLog log : logs) {
                _printLogsLine(log);
            }
        
        }

            

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    
	}
};

