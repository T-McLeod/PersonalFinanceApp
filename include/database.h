#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <chrono>

typedef struct Transaction {
    int id;
    std::string date;
    double amount;
    std::string category;
    std::string description;

    Transaction(const std::string& desc = "Default Description", double amt = 0.0, const std::string& cat = "Default Category", std::string d)
        : description(desc), amount(amt), category(cat), date(d) {}

};

class Database {
public:
    Database(const std::string& db_name);
    ~Database();
    void createTable();
    void addTransaction(const Transaction& transaction);
    std::vector<Transaction> getTransactions();

private:
    sqlite3* db;
    void executeSQL(const std::string& sql);
};

#endif // DATABASE_H