#pragma once
#include <iostream>
#include <cctype>
#include <string>


namespace input
{
	void inputRecover() {
		// clear() resets the state of the input stream
		std::cin.clear();
		// this ignores everything untill the first next new line
		// else; all invalid characters will remain in the buffer!
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// INPUT
	int readInt(std::string message) {
		int temp;
		std::cout << message << "\n";
		std::cin >> temp;

		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Not Valid: Enter another value: \n";
			std::cin >> temp;
		}

		return temp;


	}


	int readPositiveInt(std::string message) {
		int temp;
		do {
			std::cout << message << "\n";
			std::cin >> temp;
		} while (temp < 0);
		return temp;
	}
	int readIntBetween(int from, int to, std::string message) {
		int temp;
		do {
			std::cout << message << "\n";
			std::cin >> temp;
		} while (temp < from or temp > to);
		return temp;
	}
	float readFloat(std::string message) {
		float temp;
		std::cout << message << "\n";
		std::cin >> temp;
		return temp;
	}
	std::string readString(std::string message) {
		std::string temp;
		std::cout << message << std::endl;
		std::getline(std::cin >> std::ws, temp);
		return temp;
	}
	char readChar(std::string message) {
		char temp;
		std::cout << message << "\n";
		std::cin >> temp;
		return temp;
	}

	bool readBool(std::string message) {
		return readIntBetween(0, 1, message);
	}

	std::string capitalizeString(std::string str) {
		// suppose: each string starts with a letter, 
		// and only 1 space between words
		bool isFirstWordLetter = true;
		int i = 0;
		while (i < str.length()) {
			if (str[i] && isFirstWordLetter) {
				str[i] = toupper(str[i]);
			}
			isFirstWordLetter = (str[i] == ' ' ? true : false);
			i++;

		}
		return str;
	}

	std::string upperString(std::string str) {
		// suppose: each string starts with a letter, 
		// and only 1 space between words
		bool isFirstWordLetter = true;
		int i = 0;
		while (i < str.length()) {
			str[i] = toupper(str[i]);
			i++;
		}
		return str;
	}

	std::string lowerString(std::string str) {
		// suppose: each string starts with a letter, 
		// and only 1 space between words
		bool isFirstWordLetter = true;
		int i = 0;
		while (i < str.length()) {
			str[i] = tolower(str[i]);
			i++;
		}
		return str;
	}

	char invertChar(char c) {
		return isupper(c) ? tolower(c) : toupper(c);
	}
	int countUpper(std::string str) {
		int counter = 0;
		for (char c : str) {
			if (isupper(c))
				counter++;
		}
		return counter;
	}
	int countLower(std::string str) {
		int counter = 0;
		for (char c : str) {
			if (islower(c))
				counter++;
		}
		return counter;
	}

	bool isVowel(char c) {
		std::string vowels = "aeiou";
		return (vowels.find(tolower(c)) != (std::string::npos));
	}
	std::string replaceInString(std::string str, std::string oldWord, std::string newWord) {
		int pos = str.find(oldWord);

		while (pos != str.npos) {
			str = str.replace(pos, oldWord.length(), newWord);
			pos = str.find(oldWord);
		}

		return str;
	}

	
}