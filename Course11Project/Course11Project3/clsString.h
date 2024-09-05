#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
    string _value;




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

    static char invertChar(char c) {
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

public:
    // Constructor
    clsString()
    {
        _value = "";
    }
    clsString(string Value)
    {
        _value = Value;
    }

    // Getters and Setters
    void SetValue(string Value)
    {
        _value = Value;
    }
    string GetValue()
    {
        return _value;
    }

    // Alias
    __declspec(property(get = GetValue, put = SetValue)) string value;

    // Methods

    static short CountWords(string S1)
    {
        string delim = " "; // delimiter
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
            {
                Counter++;
            }
            // erase() until position and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++; // it counts the last word of the string.
        }

        return Counter;
    }
    short CountWords()
    {
        return CountWords(_value);
    }


    static string invert(string str) {
        for (char& c : str) {
            c = invertChar(c);
        }
        return str;
    }
    void invert() {
        _value = invert(_value);
    }




    static vector <string> Split(string str, string sep = " ") {
        vector <string> temp;
        int pos;
        while ((pos = str.find(sep)) != str.npos) {
            string word = str.substr(0, pos);
            if (word != "")
                temp.push_back(word);
            str = str.erase(0, pos + sep.length());
        }

        if (str != "")
            temp.push_back(str);

        return temp;
    }
    vector <string> Split(string sep = " ") {
        return Split(_value, sep);
    }

    static string trimLeft(string str) {
        if (str.length() == 0)
            return str;
        else {
            while (str[0] == ' ') {
                str = str.substr(1);
            }
            return str;
        }
    }
    string trimLeft() {
        return trimLeft(_value);
    }

    static string trimRight(string str) {
        if (str.length() == 0)
            return str;
        else {
            while (str[str.length() - 1] == ' ') {
                str.pop_back();
            }
            return str;
        }
    }
    string trimRight() {
        return trimRight(_value);
    }

    static string trimString(string str) {
        return trimLeft(trimRight(str));
    }
    string trimString() {
        return trimLeft(trimRight(_value));
    }


    static string join(vector <string> words, string sep) {
        string result = "";
        for (int i = 0; i < words.size() - 1; i++) {
            result = result + words[i] + sep;
        }
        return (result + words[words.size() - 1]);
    }



    static string replace(string str, string oldWord, string newWord) {
        int pos = str.find(oldWord);

        while (pos != str.npos) {
            str = str.replace(pos, oldWord.length(), newWord);
            pos = str.find(oldWord);
        }

        return str;
    }
    string replace(string oldWord, string newWord) {
        return replace(_value, oldWord, newWord);
    }

    static string removePunct(string str) {
        string result = "";
        for (char c : str) {
            if (!ispunct(c))
                result += c;
        }
        return result;
    }
    string removePunct() {
        return removePunct(_value);
    }


    static string capitalize(string str) {
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
    string capitalize() {
        return capitalize(_value);
    }

};

