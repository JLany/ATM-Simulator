#ifndef KEYPAD_H
#define KEYPAD_H

class Keypad {
public:
	int getInput() const;
	int getHiddenInput() const;
private:
	bool normalInput() const;
	bool hiddenInput() const;

	// we must specify that a member function
	// will be received, very important distinction 
	// for the COMPILER
	int input(bool (Keypad::*)() const) const;
}; // end class Keypad

#endif // KEYPAD_H
