#include "ATM.h"
#include "BankDatabase.h"

int main() {
	BankDatabase database;

	ATM atm;

	atm.connectDatabase(&database);
	atm.run();

	return 0;
}

