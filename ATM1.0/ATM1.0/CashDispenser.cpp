#include <stdexcept>
#include "CashDispenser.h"
using namespace std;

CashDispenser::CashDispenser()
	: count{ INITIAL_COUNT } { /* empty body */
}
// end CashDispenser default constructor

void CashDispenser::dispenseCash(int amount) {
	int billsRequired = amount / 20;
	count -= billsRequired;
	if (count < 0)
		throw invalid_argument("cash dispenser bills count cannot go below 0");
} // end function dispenseCash

bool CashDispenser::isSufficientCashAvailable(int amount) const {
	int billsRequired = amount / 20;

	if (count >= billsRequired)
		return true;

	return false;
}
