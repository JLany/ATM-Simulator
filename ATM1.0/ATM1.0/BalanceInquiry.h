#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include "Transaction.h" // class Transaction definition

// forward declarations
class Screen;
class BankDatabase;

class BalanceInquiry : public Transaction {
public:
	BalanceInquiry(int, Screen*, BankDatabase*);
	virtual void execute() override;
}; // end class BalanceInquiry

#endif // BALANCE_INQUIRY_H