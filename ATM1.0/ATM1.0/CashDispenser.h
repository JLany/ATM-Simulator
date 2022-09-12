#ifndef CASH_DISPENSER_H
#define CASH_DISPENSER_H

class CashDispenser {
public:
	CashDispenser(); // default constructor

	void dispenseCash(int);
	bool isSufficientCashAvailable(int) const;
private:
	const static int INITIAL_COUNT = 500; // initial count of $20 bills
	int count; // actual count for an object
}; // end class CashDispenser

#endif // CASH_DISPENSER_H