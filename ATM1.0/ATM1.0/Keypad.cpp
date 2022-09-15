#include <iostream>
#include <string>
#include <cctype> // isdigit function definition
#include <conio.h> // _getch function definition 
#include "Keypad.h"
using namespace std;

int Keypad::getInput() const {
	return input(normalInput);
} // end function getInput

int Keypad::getHiddenInput() const {
	return input(hiddenInput);
} // end function getHiddenInput

bool Keypad::normalInput() const {
	return false;
}

bool Keypad::hiddenInput() const {
	return true;
}

int Keypad::input(bool (Keypad::*isHiddenInput)() const) const {
	string userInput;

	int nextChr = 0;
	while (nextChr != 13) { // ascii of newline
		nextChr = _getch();

		if (nextChr == 8) { // ascii of backspace
			if (userInput.length() > 0) {
				userInput.pop_back();
				cout << "\b \b"; // erase one char from console | \b = cursor one step back
			} // end if
			continue;
		} // end if

		if (isdigit(nextChr)) {
			char temp = static_cast<char>(nextChr);
			
			userInput.push_back(temp);

			// unary * operator cannot be used with pointer to member function
			// instead, we use ->* or .* operator to dereference a pointer to 
			// member function
			cout << ((this->*isHiddenInput)() ? '*' : temp);
			
		} // end if
	} // end while

	return (userInput.empty() ? 0 : stoi(userInput));
}
