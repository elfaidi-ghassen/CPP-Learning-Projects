#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogsScreen : public clsScreen
{
    static void _printLogLine(stTransferLog log) {
        cout << setw(8) << left << "" << "| " << left << setw(30) << log.date;
        cout << "| " << left << setw(10) << log.fromAcc;
        cout << "| " << left << setw(10) << log.toAcc;
        cout << "| " << left << setw(8) << log.amount;
        cout << "| " << left << setw(8) << log.fromBalance;
        cout << "| " << left << setw(8) << log.toBalance;
        cout << "| " << left << setw(10) << log.user;

    }
public:
	static void ShowTransferLogsScreen() {
		clsScreen::_DrawScreenHeader("Transfer Logs");
		vector <stTransferLog> logs = clsBankClient::LoadTransferLogs();



        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date";
        cout << "| " << left << setw(10) << "S.acc";
        cout << "| " << left << setw(10) << "D.acc";
        cout << "| " << left << setw(8)  << "Amount";
        cout << "| " << left << setw(8)  << "S.B";
        cout << "| " << left << setw(8)  << "D.B";
        cout << "| " << left << setw(10) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (logs.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (stTransferLog log : logs)
            {
                _printLogLine(log);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;




	}
};

