#include <iostream>
#include <database.h>

int main() {
    Database* db = new Database("mydatabase.db");
    std::cout << "Hello World" << std::endl;

    db->createTable();
    Transaction* t = new Transaction();

    //db->addTransaction(t)

    return 0;
}
