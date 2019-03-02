#ifndef SUPPLIERREPO_H
#define SUPPLIERREPO_H

#include "repo.h"
#include "domain/supplier.h"

class SupplierRepo:public Repo
{
public:
    SupplierRepo();
    static vector<Supplier*>* findAll();
    static vector<Supplier*>* findByGoodID(string goodID);
    static Supplier* findByID(int id);
    static void saveSupplier(Supplier* &supplier);
    static void deleteByID(int id);
private:
    static Supplier* formSupplier(int id,string name);
};

#endif // SUPPLIERREPO_H
