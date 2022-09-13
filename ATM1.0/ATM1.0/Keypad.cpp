#include <iostream>
#include <string>
#include <cctype> // isdigit function definition
#include <conio.h> // _getch function definition 
#include "Keypad.h"
using namespace std;

int Keypad::getInput() const {
	string input;

	int nextChr = 0;
	while (nextChr != 13) { // ascii of newline
		nextChr = _getch();

		if (nextChr == 8) { // ascii of backspace
			if (input.length() > 0) {
				input.pop_back();
				cout << "\b \b"; // erase one char from console | \b = cursor one step back
			} // end if
			continue;
		} // end if

		if (isdigit(nextChr)) {
			char temp = static_cast<char>(nextChr);
			input.push_back(temp);
			cout << temp;
		} // end if
	} // end while

	return (input.empty() ? 0 : stoi(input));
} // end function getInput

int Keypad::getHiddenInput() const {
	string input;

	int nextChr = 0;
	while (nextChr != 13) { // ascii of newline
		nextChr = _getch();

		if (nextChr == 8) { // ascii of backspace
			if (input.length() > 0) {
				input.pop_back();
				cout << "\b \b"; // erase one char from console | \b = cursor one step back
			} // end if
			continue;
		} // end if

		if (isdigit(nextChr)) {
			char temp = static_cast<char>(nextChr);
			input.push_back(temp);
			cout << "*";
		} // end if
	} // end while

	return (input.empty() ? 0 : stoi(input));
} // end function getHiddenInput
