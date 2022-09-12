#ifndef TRANSACTION_H
#define TRANSACTION_H

// forward declarations
class Screen;
class BankDatabase;

// abstract class Transaction
class Transaction {
public:
	Transaction(int, Screen*, BankDatabase*); // constructor
	virtual ~Transaction(); // virual destructor with empty body

	virtual void execute() = 0; // perform transaction, pure virtual

	// for derived classes to access base class members
	int getAccountNumber() const;
	Screen* getScreen() const;
	BankDatabase* getBankDatabase() const;
private:
	Screen* screen;
	BankDatabase* bankDatabase;
	int accountNumber; // account to which apply transaction
}; // end class Transaction

#endif // TRANSACTION_H
