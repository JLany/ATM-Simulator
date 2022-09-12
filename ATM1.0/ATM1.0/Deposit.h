#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "Transaction.h" // Transaction class definition

// forward declarations
class Screen;
class Keypad;
class DepositSlot;
class BankDatabase;

class Deposit : public Transaction {
public:
	Deposit(int, Screen*, BankDatabase*, Keypad*, DepositSlot*);
	virtual void execute() override;
private:
	// pointers to associated objects
	Keypad* keypad; // gain access to a Keypad object
	DepositSlot* depositSlot; // gain access to a DepositSlot object
};

#endif // DEPOSIT_H
