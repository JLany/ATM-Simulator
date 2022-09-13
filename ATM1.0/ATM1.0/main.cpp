#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "ATM.h"
#include "BankDatabase.h"
using namespace std;

int main() {
	BankDatabase database;

	ATM atm;

	atm.connectDatabase(&database);
	atm.run();

	return 0;
}

