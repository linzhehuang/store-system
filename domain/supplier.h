#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>
#include "good.h"
using namespace std;

class Supplier
{
public:
    Supplier(int id, string name);
    int id;
    string name;
    void addGood(string goodID, double buyingPrice);
    void deleteGoodByGoodID(string goodID);
    vector<string>* goodIDs;
    vector<double>* buyingPrices;
};

#endif // SUPPLIER_H
