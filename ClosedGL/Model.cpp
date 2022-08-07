#pragma once
#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;



static class Model {

public:

	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	static int expectedVals[6][12];
	static int actualVals[6][12];
	static int iDs[20];
	static int cnt;
	static int cnt1;

	Model() {
		create();
	}
	
	void create() {
		openCustomerDatabase();
		openExpectedPaymentDatabase();
		openActualPaymentDatabase();
		read();
		readExpectedValues();
	}

	void readAll() {
		
		/* Open database */
		rc = sqlite3_open("test.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stdout, "readAll() Opened database successfully\n");
			//return(0);
		}
		/* Read all tables SQL statement */
		const char* sql = "PRAGMA table_info(CUSTOMER);";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "readAll() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Contents read successfully\n");
		}
		//sqlite3_close(db);

	}
	void read() {
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;
		const char* data = "read() Callback function called";

		/* Open database */
		rc = sqlite3_open("customer.db", &db);

		if (rc) {
			fprintf(stderr, "read() Can't open database: %s\n", sqlite3_errmsg(db));
			//return(0);
		}
		else {
			fprintf(stderr, "read() Opened database successfully\n");
		}

		/* Create SQL statement */
		const char* sql = "SELECT * from ACTUAL;";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, readCallback, (void*)data, &zErrMsg);
	
		if (rc != SQLITE_OK) {
			fprintf(stderr, "read() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "read() Operation done successfully\n");
		}
		//sqlite3_close(db);
	}
	void readExpectedValues() {
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;
		const char* data = "read() Callback function called";

		/* Open database */
		rc = sqlite3_open("customer.db", &db);

		if (rc) {
			fprintf(stderr, "read() Can't open database: %s\n", sqlite3_errmsg(db));
			//return(0);
		}
		else {
			fprintf(stderr, "read() Opened database successfully\n");
		}

		/* Create SQL statement */
		const char* sql = "SELECT * from EXPECTED;";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, expectedReadCallback, (void*)data, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "read() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "read() Operation done successfully\n");
		}
		//sqlite3_close(db);
	}

	void update(int ID, string NAME, int AGE, string ADDRESS,int SALARY) {
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;
		

		/* Open database */
		rc = sqlite3_open("test.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}

		/* Create SQL statement */
		const char* sql = "INSERT INTO CUSTOMER (ID,NAME,AGE,ADDRESS,SALARY) "  \
			"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
			"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
			"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
			"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
			"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
			"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
			"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Records created successfully\n");
		}
		sqlite3_close(db);
	}//tables are not correctly defined
	void remove() {}
	static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		cout << "callback called";
		return 0;
	}

	static int readCallback(void* NotUsed, int argc, char** argv, char** azColName) {// reads for values
		
		static std::ostringstream columns;
		std::ostringstream tmpValues;
		std::ostringstream allTmpValues;

		for (int i = 0; i  < argc; i++) {
			tmpValues << argv[i];
			allTmpValues << argv [i] <<",";
			if (i % 13 != 0) {
					actualVals[cnt-1][i-1] = stoi(tmpValues.str());
			}
			else {
				iDs[cnt] = stoi(tmpValues.str());
				cnt++;
			}
			tmpValues.str("");
		}
		return 0;
	}
	static int expectedReadCallback(void* NotUsed, int argc, char** argv, char** azColName) {// reads for values

		static std::ostringstream columns;
		std::ostringstream tmpValues;
		std::ostringstream allTmpValues;

		for (int i = 0; i < argc; i++) {
			tmpValues << argv[i];
			allTmpValues << argv[i] << ",";
			if (i % 13 != 0) {
				expectedVals[cnt1 - 1][i - 1] = stoi(tmpValues.str());
			}
			else {
				iDs[cnt1] = stoi(tmpValues.str());
				cnt1++;
			}
			tmpValues.str("");
		}
		return 0;
	}

	private:
	void openCustomerDatabase() {
		/* Open customer database */
		rc = sqlite3_open("customer.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stdout, "create() Opened database successfully\n");
			//return(0);
		}
		/* Create SQL statement */
		const char* sql = "CREATE TABLE CUSTOMER ("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"NAME           TEXT    NOT NULL," \
			"AGE            INT     NOT NULL," \
			"ADDRESS        CHAR(50)," \
			"PAYMENT        REAL );";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "create() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Table created successfully\n");
		}
		//sqlite3_close(db);
	}
	void openExpectedPaymentDatabase() {
		/* Open expected payment database */
		rc = sqlite3_open("customer.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stdout, "create() Opened database successfully\n");
			//return(0);
		}
		/* Create SQL statement */
		const char* sql = "CREATE TABLE EXPECTED ("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"P1            INT     NOT NULL," \
			"P2            INT     NOT NULL," \
			"P3            INT     NOT NULL," \
			"P4            INT     NOT NULL," \
			"P5            INT     NOT NULL," \
			"P6            INT     NOT NULL," \
			"P7            INT     NOT NULL," \
			"P8            INT     NOT NULL," \
			"P9            INT     NOT NULL," \
			"P10            INT     NOT NULL," \
			"P11           INT     NOT NULL," \
			"P12        INT		NOT NULL );";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "create() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Table created successfully\n");
		}
		//sqlite3_close(db);
	}
	void openActualPaymentDatabase() {
		/* Open actual payment database */
		rc = sqlite3_open("customer.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stdout, "create() Opened database successfully\n");
			//return(0);
		}
		/* Create SQL statement */
		const char* sql = "CREATE TABLE ACTUAL ("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"P1            INT     NOT NULL," \
			"P2            INT     NOT NULL," \
			"P3            INT     NOT NULL," \
			"P4            INT     NOT NULL," \
			"P5            INT     NOT NULL," \
			"P6            INT     NOT NULL," \
			"P7            INT     NOT NULL," \
			"P8            INT     NOT NULL," \
			"P9            INT     NOT NULL," \
			"P10            INT     NOT NULL," \
			"P11           INT     NOT NULL," \
			"P12        INT		NOT NULL );";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "create() SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Table created successfully\n");
		}
		//sqlite3_close(db);
	}

};


