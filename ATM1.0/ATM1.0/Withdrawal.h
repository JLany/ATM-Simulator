#ifndef WITHDRAWAWL_H
#define WITHDRAWAWL_H

#include "Transaction.h" // class Transaction definition

// forward declarations
class Keypad;
class CashDispenser;

class Withdrawal : public Transaction {
public:
	// operations
	virtual void execute() override; // perform the transaction

private:
	double amount; // amount to withdraw

	// pointers to associated objects
	Keypad* keypad;
	CashDispenser* cashDispenser;
}; // end class Withdrawal


#endif // WITHDRAWAWL_H
