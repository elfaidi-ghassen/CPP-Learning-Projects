#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

using std::string;
using std::vector;

class clsDate {
	int _day, _month, _year;

	// Private helper methods
	static bool isLeapYear(short year) {
		return (year % 400 == 0 || year % 4 == 0 && year % 100 != 0);
	}
	static int daysInMonth(int month, int year) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return month == 2 ? (isLeapYear(year) ? 29 : 28) : days[month - 1];
	}
	static void addOneDay(clsDate& date) {
		if (date.day < daysInMonth(date.month, date.year))
			date.day++;
		else if (date.month < 12) {
			date.day = 1;
			date.month++;
		}
		else {
			date.day = 1;
			date.month = 1;
			date.year++;
		}
	}
	void addOneDay() {
		addOneDay(*this);
	}
	static vector <string> splitString(string str, string sep) {
		std::vector <std::string> temp;
		int pos;
		while ((pos = str.find(sep)) != str.npos) {
			std::string word = str.substr(0, pos);
			if (word != "")
				temp.push_back(word);

			str = str.erase(0, pos + sep.length());
		}
		if (str != "")
			temp.push_back(str);

		return temp;
	}
	// Inner Classes

		
	
public:
	class Calendar {
		static int dayOrder(clsDate date) {
			// 0 = Sunday
			int a = (14 - date.month) / 12;
			int y = date.year - a;
			int m = date.month + 12 * a - 2;
			return (date.day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
		}
		static void printCalendarHeader(string month) {
			const string days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
			std::cout << "______________" << month << "______________\n\n";
			for (int i = 0; i < 7; i++) {
				std::cout << std::setw(4) << days[i];
			}
			std::cout << "\n";
		}
		static string monthName(int month) {
			const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
			return months[month - 1];
		}
		static void printCalendarDays
		(int start, int numberOfDays) {
			std::cout << std::setw(start * 4) << "";
			for (int i = 1; i <= numberOfDays; i++) {
				std::cout << std::setw(4) << i;
				if ((i + start) % 7 == 0)
					std::cout << "\n";
			}
			std::cout << "\n";
		}

	public:
		static void printCalendar(short year, short month) {
			printCalendarHeader(monthName(month));
			printCalendarDays(dayOrder(clsDate(1, month, year)),
				daysInMonth(month, year));
			std::cout << "_______________________________";
		}
		static void printYearlyCalander(int year) {
			std::cout << "=========================================\n";
			std::cout << "\t\t" << year << " Calendar\n";
			std::cout << "=========================================\n";

			for (int i = 1; i <= 12; i++) {
				printCalendar(year, i);
				std::cout << "\n";
			}
		}

	};
	// Getters
	int getDay() {
		return _day;
	}
	int getMonth() {
		return _month;
	}
	int getYear() {
		return _year;
	}

	// Setters
	void setDay(int day) {
		_day = day;
	}
	void setMonth(int month) {
		_month = month;
	}
	void setYear(int year) {
		_year = year;
	}

	// Alias
	__declspec(property(get = getDay, put = setDay)) int day;
	__declspec(property(get = getMonth, put = setMonth)) int month;
	__declspec(property(get = getYear, put = setYear)) int year;

	// Constructors
	clsDate() {
		time_t t = time(0); // current time
		tm* now = localtime(&t); // tm is a strucutre, tm* means a pointer to a structure
		// localtime() returns a the adress of a pointer to structure
		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_day = now->tm_mday;
	}
	clsDate(int day, int month, int year) {
		_day = day;
		_month = month;
		_year = year;
	}
	clsDate(int days, int year) {
		_day = 1;
		_month = 1;
		_year = year;
		addDays(days);
	}
	clsDate(string strDate) {
		vector <string> parts = splitString(strDate, "/");
		_day = stoi(parts[0]);
		_month = stoi(parts[1]);
		_year = stoi(parts[2]);
	}




	//// Other Methods
	// Modify date
	void addDays(int n) {
		for (int i = 0; i < n; i++) {
			addOneDay();
		}
	}


	// Printing
	static string concatDate(int a, int b, int c, string sep) {
		return std::to_string(a) + sep + std::to_string(b) + sep
			+ std::to_string(c);
	}


	static void printCalendar(clsDate date) {
		Calendar::printCalendar(date.year, date.month);

	}
	void printCalendar() {
		printCalendar(*this);
	}

	static void printYearlyCalendar(clsDate date) {
		Calendar::printYearlyCalander(date.year);
	}
	void printYearlyCalendar() {
		printYearlyCalendar(*this);
	}

	string concatDate(string sep) {
		return concatDate(_day, _month, _year, sep);
	}

	void printDate() {
		std::cout << "Date: " << concatDate(_day, _month, _year, "/") << "\n";
	}



	// State
	static bool isValid(clsDate date) {
		if (date.day < 1 || date.day > daysInMonth(date.month, date.year))
			return false;

		if (date.month < 1 || date.month > 12)
			return false;

		return true;

	}
	bool isValid() {
		isValid(*this);
	}


	static bool before(clsDate d1, clsDate d2) {
		return d1.year < d2.year
			|| (d1.year == d2.year && d1.month < d2.month)
			|| (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day);
	}
	bool before(clsDate date) {
		return before(*this, date);
	}

	static bool equal(clsDate d1, clsDate d2) {
		return (d1.before(d2) == d2.before(d1));
	}
	bool equal(clsDate date) {
		return equal(*this, date);
	}
	
	static bool after(clsDate d1, clsDate d2) {
		return !(before(d1, d2) || equal(d1, d2));
	}
	bool after(clsDate date) {
		return after(*this, date);
	}


	static int daysUntil(clsDate d1, clsDate d2, bool includeLast = false) {
		if (d2.before(d1)) {
			throw std::invalid_argument("the given date should be after the date in the object");
		}
		int count = 0;
		while (!d1.equal(d2)) {
			count++;
			d1.addOneDay();
		}
		return (includeLast ? ++count : count);
	}
	int daysUntil(clsDate date, bool includeLast = false) {
		return daysUntil(*this, date, includeLast);
	}



	static int dayUntilEndOfYear(clsDate date) {
		clsDate endOfYear(31, 12, date.year);
		return date.daysUntil(endOfYear);
	}
	int dayUntilEndOfYear() {
		return dayUntilEndOfYear(*this);
	}
};

