#ifndef TRANSACTIONREPO_H
#define TRANSACTIONREPO_H

#include "repo.h"
#include "goodrepo.h"
#include "domain/transaction.h"

class TransactionRepo:public Repo
{
public:
    TransactionRepo();
    static bool saveTransaction(Transaction* transaction);
    static vector<Transaction*>* findByCashierID(int cashierID);
    static vector<Transaction*>* findByDate(string date);
private:
    static Transaction* formTransaction(int cashierID,string date);
};

#endif // TRANSACTIONREPO_H
