#ifndef CASHIERREPO_H
#define CASHIERREPO_H

#include "repo.h"
#include "domain/cashier.h"

class CashierRepo:public Repo
{
public:
    CashierRepo();
    static vector<Cashier*>* findAll();
    static Cashier* findByID(int id);
    static void saveCashier(Cashier *cashier);
    static void deleteByID(int id);
};

#endif // CASHIERREPO_H
