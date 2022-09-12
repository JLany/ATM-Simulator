#include <stdexcept>
#include "Transaction.h"
using namespace std;

Transaction::Transaction(
	int userAccountNumber,
	Screen* aScreen,
	BankDatabase* database)
	: accountNumber{ (userAccountNumber == 0 ? throw
		invalid_argument{"invalid initializer account number for Transaction"}
		: userAccountNumber) },
	screen{ aScreen },
	bankDatabase{ database } { /* empty body */ }

int Transaction::getAccountNumber() const { return accountNumber; }

Screen* Transaction::getScreen() const { return screen; }

BankDatabase* Transaction::getBankDatabase() const { return bankDatabase; }
