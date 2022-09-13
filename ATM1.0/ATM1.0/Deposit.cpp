#include "Deposit.h"
#include "Screen.h"
#include "Keypad.h"
#include "DepositSlot.h"
#include "BankDatabase.h"
using namespace std;

static const int CANCELED = 0;

Deposit::Deposit(int userAccountNumber, Screen* aScreen,
	BankDatabase* database, Keypad* aKeypad, DepositSlot* aDepositSlot)
	: Transaction(userAccountNumber, aScreen, database),
	amount{ 0.0 },
	keypad{ aKeypad },
	depositSlot{ aDepositSlot } { /* empty body */ }
// end Deposit constructor

void Deposit::execute() {
	// get access to private inherited members
	Screen* screen = getScreen();
	BankDatabase* bankDatabase = getBankDatabase();

	amount = promptForDepositAmount();

	if (amount == CANCELED) {
		screen->displayMessageLine("\nAborting transaction.");
		screen->hold(1);
		screen->displayMessage(".");
		screen->hold(1);
		screen->displayMessage(".");
		// just some fancy 'graphics' as if "we are processing"

		return;
	}

	screen->displayMessageLine("\nInsert deposit envelope.");
	screen->hold(3);

	if (depositSlot->isEnvelopeReceived()) {
		screen->displayMessageLine("\nYour envelope has been received."
			"\nNOTE: The money deposited will not not be available until we"
			"\nverify the amount of any enclosed cash, and any enclosed "
			"checks clear.");

		bankDatabase->credit(getAccountNumber(), amount);
	}
	else {
		screen->displayMessageLine("\nYou did not insert an envelope. "
			"\nYour transaction has been canceled.");
		screen->hold(3);
	}
} // end function execute

double Deposit::promptForDepositAmount() {
	Screen* screen = getScreen();

	screen->clear();
	screen->displayMessage("\nEnter deposit amount in CENTS "
		"(or Enter to Cancel): ");

	// getInput returns 0 if the user Enters nothing
	int input = keypad->getInput();

	if (input == 0)
		return CANCELED;
	else
		return static_cast<double>(input) / 100;
}
