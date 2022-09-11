#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include "Transaction.h" // class Transaction definition

class BalanceInquiry : public Transaction {
public:
	virtual void execute() override;
}; // end class BalanceInquiry

#endif // BALANCE_INQUIRY_H