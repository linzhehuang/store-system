#ifndef GOODREPO_H
#define GOODREPO_H

#include "repo.h"
#include "domain/good.h"

class GoodRepo:public Repo
{
public:
    GoodRepo();
    static vector<Good*>* findAll();
    static Good* findByGoodID(string goodID);
    static void saveGood(Good* &good);
    static void deleteByID(string id);
private:
    static vector<Good*>* resultSetToGoods(QSqlQuery *&resultSet);
    static Good* resultSetToGood(QSqlQuery* &resultSet);
};

#endif // GOODREPO_H
