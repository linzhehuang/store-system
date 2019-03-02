#include "transaction.h"

Transaction::Transaction(int cashierID)
{
    this->cashierID = cashierID;
    this->goods = new vector<Good*>();
    this->quantities = new vector<int>();
}

Transaction::~Transaction()
{
    delete this->goods;
    delete this->quantities;
}

void Transaction::addGood(Good* good, int quantity)
{
    this->goods->push_back(good);
    this->quantities->push_back(quantity);
}

void Transaction::deleteGoodByIndex(int index)
{
    if((index<0) && (index>(int)this->goods->size()))
        throw "Out of range.";
    vector<Good*>::iterator goodsIt = this->goods->begin()+index;
    vector<int>::iterator quantitiesIt = this->quantities->begin()+index;
    this->goods->erase(goodsIt);
    this->quantities->erase(quantitiesIt);
}

double Transaction::getAmount(Member *member)
{
    double amount = 0;
    for(int i = 0;i < (int)this->goods->size();i++) {
        //qDebug("%d * %f", this->goods->at(i)->price,this->quantities->at(i));
        amount += ((this->goods->at(i)->price) * (this->quantities->at(i)));
    }
    if(member != NULL) {
        amount = member->discount(amount);
    }
    return amount;
}
