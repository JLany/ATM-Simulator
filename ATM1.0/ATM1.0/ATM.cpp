#include "ATM.h"
#include "Withdrawal.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "BankDatabase.h"

ATM::ATM(BankDatabase* DB)
	: bankDatabase{ DB },
	userAuthenticated{ false },
	currentAccountNumber{ 0 }
{ /* empty body */ }


