#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
	bool validatePIN(int);

	double getAvailableBalance();
	double getTotalBalance();

	void credit(int);
	void debit(int);
private:
	int accountNumber;
	int pin;
	double availableBalance;
	double totalBalance;
}; // end class Account

#endif // ACCOUNT_H
