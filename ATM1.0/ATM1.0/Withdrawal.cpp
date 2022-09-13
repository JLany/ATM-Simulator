#include <stdexcept>
#include "Withdrawal.h"
#include "Screen.h"
#include "Keypad.h"
#include "CashDispenser.h"
#include "BankDatabase.h"
using namespace std;

static const int CANCELED = 6;

Withdrawal::Withdrawal(int userAccountNumber, Screen* aScreen,
	BankDatabase* database, Keypad* aKeypad, CashDispenser* dispenser)
	: Transaction(userAccountNumber, aScreen, database),
	amount{ 0.0 },
	keypad{ aKeypad },
	cashDispenser{ dispenser } { /* empty body */ } // end Withdrawal constructor

void Withdrawal::execute() {
	bool cashDispensed = false;
	bool transactionCanceled = false;

	// get access to private inherited members
	Screen* screen = getScreen(); // local pointer to screen
	BankDatabase* bankDatabase = getBankDatabase(); // local pointer to bankDatabase

	while (!cashDispensed && !transactionCanceled) {
		int selection = displayWithdrawalMenu();

		if (selection == CANCELED) {
			transactionCanceled = true;
			cancelTransactionMessage();
			continue;
		}

		amount = selection;

		double availableBalance =
			bankDatabase->getAvailableBalance(getAccountNumber());

		if (amount > availableBalance) {
			screen->displayMessageLine("\nInsufficient available balance "
				"in your account.\nPlease try again.");
			continue;
		}

		bool sufficientCashAvailable =
			cashDispenser->isSufficientCashAvailable(getAccountNumber());
		if (!sufficientCashAvailable) {
			screen->displayMessageLine("\nInsufficient cash in the ATM."
				"\nPlease try again with a smaller amount.");
			continue;
		}

		bankDatabase->debit(getAccountNumber(), amount);

		cashDispenser->dispenseCash(static_cast<int>(amount));
		screen->displayMessageLine("\nPlease take your cash.");
		cashDispensed = true;
	}
}

int Withdrawal::displayWithdrawalMenu() const {
	int userChoice = 0;

	// array of amounts correspond to menu numbers
	int amounts[]{ 0, 20, 40, 60, 100, 200 };

	Screen* screen = getScreen(); // get local access to private member

	while (userChoice == 0) { // loop until valid selection 
		screen->clear();
		screen->displayMessageLine("\nWithdrawal Options:");
		screen->displayMessageLine("	1 - $20		4 - $100");
		screen->displayMessageLine("	2 - $40		5 - $200");
		screen->displayMessageLine("	3 - $60		6 - Cancel Transaction");
		screen->displayMessage("Choose an option (1 - 6): ");

		int input = keypad->getInput();

		switch (input) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			userChoice = amounts[input];
			break;
		case 6:
			userChoice = CANCELED;
			break;
		default:
			screen->displayMessageLine("\nInvalid selection. Try again.");
			break;
		} // end switch
	}

	return userChoice;
} // end function displayWithdrawalMenu

void Withdrawal::cancelTransactionMessage() const {
	Screen* screen = getScreen(); // get local access to private member

	screen->displayMessageLine("\nAborting transaction.");
	screen->hold(1);
	screen->displayMessage(".");
	screen->hold(1);
	screen->displayMessage(".");
	// just some fancy 'graphics' as if "we are processing"
}
