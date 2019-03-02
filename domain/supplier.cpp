#include "supplier.h"

Supplier::Supplier(int id, string name)
{
    this->id = id;
    this->name = name;
    this->goodIDs = new vector<string>();
    this->buyingPrices = new vector<double>();
}

void Supplier::addGood(string goodID, double buyingPrice)
{
    this->goodIDs->push_back(goodID);
    this->buyingPrices->push_back(buyingPrice);
}
void Supplier::deleteGoodByGoodID(string goodID)
{
    for(int i = 0;i < (int)this->goodIDs->size();i++)
    {
        if(this->goodIDs->at(i) == goodID) {
            vector<string>::iterator goodIDIt = this->goodIDs->begin() + i;
            vector<double>::iterator buyingPriceIt = this->buyingPrices->begin() + i;
            this->goodIDs->erase(goodIDIt);
            this->buyingPrices->erase(buyingPriceIt);
            break;
        }
    }
}
