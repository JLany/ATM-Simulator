#ifndef TRANSACTION_H
#define TRANSACTION_H

// forward declarations
class Screen;
class BankDatabase;

// abstract class Transaction
class Transaction {
public:
	Transaction(int, Screen*, BankDatabase*); // constructor
	virtual void execute() = 0; // perform transaction
	int getAccountNumber() const; // for derived classes to access 
								  // accountNumber data member
private:
	int accountNumber; // account to which apply transaction
	Screen* screen;
	BankDatabase* bankDatabase;
}; // end class Transaction

#endif // TRANSACTION_H
