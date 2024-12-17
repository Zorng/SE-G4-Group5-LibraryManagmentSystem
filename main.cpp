#include "utils/Transaction.hpp"

int main() {
    TransactionList trList;
    trList.loadTransactionFromFile("database/TransactionDB.txt");
    trList.displayTransaction();
    

    return 0;
}