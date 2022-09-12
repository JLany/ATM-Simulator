#include <iostream>
#include <string>
#include <regex>
#include <conio.h>
#include "Keypad.h"
using namespace std;

int Keypad::getInput() const {
	string input;
	regex digitEx("[0-9]+");

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

		string temp = ""; // empty string
		temp += static_cast<char>(nextChr);

		if (regex_match(temp, digitEx)) {
			input.append(temp);
			cout << temp;
		} // end if
	} // end while

	return (input.empty() ? 0 : stoi(input));
} // end function getInput
