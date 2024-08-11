#pragma once

#include <iostream>
#include <string>
#include <vector>


namespace str
{
	
	std::vector <std::string> splitString(std::string str, std::string sep) {
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
	void printCharLine(int n, char sep) {
		for (int i = 0; i < n; i++) {
			std::cout << sep;
		}
	}
	std::string generateChars(int n, char sep) {
		std::string s = "";
		for (int i = 0; i < n; i++) {
			s += sep;
		}
		return s;
	}

}