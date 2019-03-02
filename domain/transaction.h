#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <QDebug>
#include "good.h"
#include "member.h"

class Transaction
{
public:
    Transaction(int cashierID);
    ~Transaction();
    string date;
    void addGood(Good* good, int quantity);
    void deleteGoodByIndex(int index);
    double getAmount(Member *member);
    vector<Good*>* goods;
    vector<int>* quantities;
    int cashierID;
};

#endif // TRANSACTION_H
