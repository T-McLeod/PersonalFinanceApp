#include "database.h"
#include <iostream>

Database::Database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS TRANSACTIONS("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "DATE TEXT NOT NULL, "
                      "AMOUNT REAL NOT NULL, "
                      "CATEGORY TEXT NOT NULL, "
                      "DESCRIPTION TEXT);";
    executeSQL(sql);
}

void Database::addTransaction(const Transaction& transaction) {
    std::string sql = "INSERT INTO TRANSACTIONS (DATE, AMOUNT, CATEGORY, DESCRIPTION) VALUES ('" +
                      transaction.date + "', " + std::to_string(transaction.amount) + ", '" +
                      transaction.category + "', '" + transaction.description + "');";
    executeSQL(sql);
}

std::vector<Transaction> Database::getTransactions() {
    std::vector<Transaction> transactions;
    std::string sql = "SELECT * FROM TRANSACTIONS;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Transaction transaction;
            transaction.id = sqlite3_column_int(stmt, 0);
            transaction.date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            transaction.amount = sqlite3_column_double(stmt, 2);
            transaction.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            transaction.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            transactions.push_back(transaction);
        }
    }
    sqlite3_finalize(stmt);
    return transactions;
}

void Database::executeSQL(const std::string& sql) {
    char* errorMessage = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

Database::Transaction()