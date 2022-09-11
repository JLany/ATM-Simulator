#include <iostream>
#include <string>
#include <sqlite3.h>
#include <stdexcept>
#include "BankDatabase.h"
using namespace std;

#define DEBUG 0 // for debugging and testing the class

#define BANK_DATABASE_PATH "" // add path for database here here

BankDatabase::BankDatabase() : filePath{ BANK_DATABASE_PATH } {
	initializeConnection();
}

BankDatabase::~BankDatabase() {
	sqlite3_close(Database);
}

bool BankDatabase::authenticateUser(int userAccountNumber, int userPIN) {
	bool userAuthenticated = false;
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;
	static string sql =
		"SELECT * "
		"FROM bank_accounts "
		"WHERE account_number = ? "
		"AND account_pin = ?;";

	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	rc = sqlite3_bind_int(sqliteStatement, 1, userAccountNumber);
	rc = sqlite3_bind_int(sqliteStatement, 2, userPIN);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);
	if (rc == SQLITE_ROW) { // means there is new result obtained by step
		int columns = sqlite3_column_count(sqliteStatement);

#if DEBUG
		cout << "\n\ncolumns: " << columns << "\n\n";
#endif

		if (columns == 4)
			userAuthenticated = true;
		else if (columns > 4)
			throw invalid_argument("more than one account matches in database");
	}

	if (rc == SQLITE_DONE)
		sqlite3_reset(sqliteStatement);

	rc = sqlite3_finalize(sqliteStatement);
	if (rc != SQLITE_OK)
		throw invalid_argument("statmenet finalization failed");

	return userAuthenticated;
}

// this function is assumed to be used after it has been made sure
// that userAccountNumber exists in database, otherwise it throws 
// an exception in case account was not found in database, 
// rather than indicating in some rc that it does not exist
double BankDatabase::getAvailableBalance(int userAccountNumber) {
	double availableBalance;
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;
	string sql =
		"SELECT available_balance "
		"FROM bank_accounts "
		"WHERE account_number = ?;";

	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	rc = sqlite3_bind_int(sqliteStatement, 1, userAccountNumber);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);
	if (rc == SQLITE_ROW) {
		// this query should return only one column in normal cases
		if (sqlite3_column_count(sqliteStatement) > 1)
			throw invalid_argument(
				"query corrupted, more than one column returned");

		availableBalance = sqlite3_column_double(sqliteStatement, 0);
	}
	else
		throw invalid_argument("no account exists with such account number");

	sqlite3_finalize(sqliteStatement);

	return availableBalance;
}

// this function is assumed to be used after it has been made sure
// that userAccountNumber exists in database, otherwise it throws 
// an exception in case account was not found in database, 
// rather than indicating in some rc that it does not exist
double BankDatabase::getTotalBalance(int userAccountNumber) {
	double totalBalance;
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;
	string sql =
		"SELECT total_balance FROM bank_accounts "
		"WHERE account_number = ?;";

	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	rc = sqlite3_bind_int(sqliteStatement, 1, userAccountNumber);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);
	if (rc == SQLITE_ROW) {
		// this query should return only one column in normal cases
		if (sqlite3_column_count(sqliteStatement) > 1)
			throw invalid_argument(
				"query corrupted, more than one column returned");

		totalBalance = sqlite3_column_double(sqliteStatement, 0);
	}
	else
		throw invalid_argument("no account exists with such account number");

	sqlite3_finalize(sqliteStatement);

	return totalBalance;
}

void BankDatabase::credit(int userAccountNumber, double amount) {
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;

	// sql parameters
	// 1: newTotalBalance
	// 2: accountNumber
	string sql =
		"UPDATE bank_accounts "
		"SET total_balance = ? "
		"WHERE account_number = ?;";


	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	double newTotalBalance = getTotalBalance(userAccountNumber) + amount;

	rc = sqlite3_bind_double(sqliteStatement, 1, newTotalBalance);
	rc = sqlite3_bind_int(sqliteStatement, 2, userAccountNumber);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);

#if DEBUG
	cout << "\n\nrc: " << rc
		<< "\nSQLITE_DONE: " << SQLITE_DONE << "\n\n";
#endif
	if (rc != SQLITE_DONE) // in normal cases, UPDATE returns SQLITE_DONE
		throw invalid_argument("step function corrupted");

	sqlite3_finalize(sqliteStatement);
}

// CAUTION: this function assumes that amount has been validated
// that it's less than or equal to account's available balance
// before it's passed as an argument.
// undefined behavior otherwise
void BankDatabase::debit(int userAccountNumber, double amount) {
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;

	// sql parameters
	// 1: newAvailableBalance
	// 2: newTotalBalance
	// 3: accountNumber
	string sql =
		"UPDATE bank_accounts "
		"SET available_balance = ?, total_balance = ? "
		"WHERE account_number = ?;";

	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	double newAvailableBalance = getAvailableBalance(userAccountNumber) - amount;
	double newTotalBalance = getTotalBalance(userAccountNumber) - amount;

	rc = sqlite3_bind_double(sqliteStatement, 1, newAvailableBalance);
	rc = sqlite3_bind_double(sqliteStatement, 2, newTotalBalance);
	rc = sqlite3_bind_int(sqliteStatement, 3, userAccountNumber);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);
	if (rc != SQLITE_DONE) // in normal cases, UPDATE returns SQLITE_DONE
		throw invalid_argument("step function corrupted");

	sqlite3_finalize(sqliteStatement);
}

void BankDatabase::initializeConnection() {
	int rc;
	rc = sqlite3_open(filePath, &Database);
	if (rc != SQLITE_OK)
		throw invalid_argument(
			"an error occurred while connecting to database");
}
