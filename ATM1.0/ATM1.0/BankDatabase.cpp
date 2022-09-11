#include <string>
#include <sqlite3.h>
#include <stdexcept>
#include "BankDatabase.h"
using namespace std;

#define PATH ""

BankDatabase::BankDatabase() : filePath{ PATH } {
	initializeConnection();
}

BankDatabase::~BankDatabase() {
	sqlite3_close(Database);
}

bool BankDatabase::authenticateUser(int userAccountNumber, int userPIN) {
	bool userAuthenticated = false;
	sqlite3_stmt* sqliteStatement = NULL;
	int rc;
	static string sql = "SELECT * FROM table_name "
		"WHERE column1_name = ? "
		"AND culumn2_name = ?;";

	rc = sqlite3_prepare_v2(Database, sql.c_str(), -1, &sqliteStatement, NULL);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement preparation failed");

	rc = sqlite3_bind_int(sqliteStatement, 1, userAccountNumber);
	rc = sqlite3_bind_int(sqliteStatement, 2, userPIN);
	if (rc != SQLITE_OK)
		throw invalid_argument("statement binding failed");

	rc = sqlite3_step(sqliteStatement);
	if (rc == SQLITE_ROW) {
		int columns = sqlite3_column_count(sqliteStatement);
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

void BankDatabase::initializeConnection() {
	int rc;
	rc = sqlite3_open(filePath, &Database);
	if (rc != SQLITE_OK) {
		throw invalid_argument(
			"an error occurred while connecting to database");
	}
}
