#include "BalanceInquiry.h"
#include "Screen.h"
#include "BankDatabase.h"
using namespace std;

BalanceInquiry::BalanceInquiry(int userAccountNumber,
	Screen* aScreen,
	BankDatabase* database)
	: Transaction(userAccountNumber, aScreen, database) { // empty body
} // end BalanceInquiry constructor

void BalanceInquiry::execute() {
	Screen* screen = getScreen();
	BankDatabase* bankDatabase = getBankDatabase();

	double availableBalance =
		bankDatabase->getAvailableBalance(getAccountNumber());
	double totalBalance =
		bankDatabase->getTotalBalance(getAccountNumber());

	screen->displayMessageLine("\nBalance Information:");
	screen->displayMessageLine("	- Available Balance: $", availableBalance);
	screen->displayMessageLine("	- Total Balance: $", totalBalance);
}
