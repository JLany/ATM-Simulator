#ifndef ATM_H
#define ATM_H

#include "Screen.h"
#include "Keypad.h"
#include "CashDispenser.h"
#include "DepositSlot.h"

// forward declarations
class Transaction;
class BankDatabase;

class ATM {
public:
	ATM(BankDatabase*); // constructor
	void run(); // start ATM system
private:
	bool userAuthenticated; // whether user	is authenticated 
	int currentAccountNumber; // current user's account number
	Screen screen; // ATM's screen
	Keypad keypad; // ATM's keypad
	CashDispenser cashDispenser; // ATM's cash dispenser
	DepositSlot depositSlot; // ATM's depositSlot

	// associated objects
	BankDatabase* bankDatabase; // database holding accounts info

	// private utility functions
	void authenticateUser(); // attempts to authenticate user
	void performTransactions(); // performs transactions
	int displayMainMenu() const; // displays main menu

	// return object of specified Transaction derived class
	Transaction* createTransaction(int);
}; // end class ATM

#endif
