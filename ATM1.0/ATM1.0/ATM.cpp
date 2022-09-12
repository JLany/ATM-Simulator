#include "ATM.h"
#include "Withdrawal.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "BankDatabase.h"

enum MenuChoice { BALANCE_INQUIRY = 1, WITHDRAWAL, DEPOSIT, EXIT };

ATM::ATM(BankDatabase* DB)
	: bankDatabase{ DB },
	userAuthenticated{ false },
	currentAccountNumber{ 0 }
{ /* empty body */ }

ATM::ATM() {
	delete bankDatabase;
}

void ATM::run() {
	while (true) {
		// loop until user is authenticated
		while (!userAuthenticated) {
			screen.displayMessageLine("Welcome!");
			authenticateUser();
		} // end inner while

		// start user session
		performTransactions();
		// end user session 
		userAuthenticated = false;
		currentAccountNumber = 0;

		system("clear");
	} // end while
} // end function run

void ATM::authenticateUser() {
	screen.displayMessage("\nPlease Enter your account number: ");
	int accountNumber = keypad.getInput();

	screen.displayMessage("\nEnter your PIN: ");
	int pin = keypad.getInput();

	userAuthenticated = bankDatabase->
		authenticateUser(accountNumber, pin);

	if (userAuthenticated)
		currentAccountNumber = accountNumber;
	else
		screen.displayMessageLine(
			"Invalid account number of PIN. Please try again");
}// end function authenticateUser

void ATM::performTransactions() {
	Transaction* currentTransaction = nullptr;

	bool userExited = false;

	while (!userExited) {
		int mainMenuChoice = displayMainMenu();

		switch (mainMenuChoice) {
		case BALANCE_INQUIRY:
		case WITHDRAWAL:
		case DEPOSIT:
			currentTransaction = createTransaction(mainMenuChoice);
			// start transaction
			currentTransaction->execute();
			// end transaction
			delete currentTransaction;
			currentTransaction = nullptr;

			break;
		case EXIT:
			screen.displayMessageLine("\nEnding session...");
			screen.displayMessageLine(
				"\nThank you for banking with us! Goodbye!");
			userExited = true;
			break;
		default: // user did not enter a an integer from 1 - 4
			screen.displayMessageLine(
				"\nYou did not enter a valid selection. Try again.");
			break;
		}
	}
}

int ATM::displayMainMenu() const {
	system("clear");
	screen.displayMessageLine("Main Menu:");
	screen.displayMessageLine("		1 - View my balance");
	screen.displayMessageLine("		2 - Withdraw cash");
	screen.displayMessageLine("		3 - Deposit funds");
	screen.displayMessageLine("		4 - Exit");
	screen.displayMessage("Enter a choice");
	return keypad.getInput();
}

Transaction* ATM::createTransaction(int type) {
	Transaction* transaction;

	switch (type) {
	case BALANCE_INQUIRY:
		transaction =
			new BalanceInquiry(currentAccountNumber, &screen, bankDatabase);
		break;
	case WITHDRAWAL:
		transaction =
			new Withdrawal(currentAccountNumber, &screen,
				bankDatabase, &keypad, &cashDispenser);
		break;
	case DEPOSIT:
		transaction =
			new Deposit(currentAccountNumber, &screen,
				bankDatabase, &keypad, &depositSlot);
		break;
	}

	return transaction;
}
