#ifndef BANK_DATABASE_H
#define BANK_DATABASE_H

// forward declarations
class sqlite3;

class BankDatabase {
public:
	BankDatabase(); // constructor	
	~BankDatabase(); // destructor

	bool authenticateUser(int, int); // takes userAccountNumber, userPIN
	double getAvailableBalance(int); // takes userAccountNumber
	double getTotalBalance(int); // takes userAccountNumber
	void credit(int, double); // takes userAccountNumber, amount
	void debit(int, double); // takes userAccountNumber, amount
private:
	sqlite3* Database;
	const char* filePath;

	void initializeConnection();
}; // end class BankDatabase

#endif // BANK_DATABASE_H