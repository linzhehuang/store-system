#include "goodrepo.h"

GoodRepo::GoodRepo()
{

}

vector<Good*>* GoodRepo::findAll()
{
    QSqlQuery* resultSet = dbUtil->query("select * from good_info;");
    return resultSetToGoods(resultSet);
}

Good* GoodRepo::findByGoodID(string goodID)
{
    QSqlQuery* resultSet = dbUtil->query("select * from good_info where id='" +
                                         goodID + "';");
    if(!resultSet->next()) return NULL;
    return resultSetToGood(resultSet);
}

void GoodRepo::saveGood(Good* &good)
{
    dbUtil->execute("insert into good_info values('" +
                    good->id + "','" +
                    good->name + "'," +
                    to_string(good->price) + ");");
}

void GoodRepo::deleteByID(string id)
{
    dbUtil->execute("delete from good_info where id='" +
                    id + "';");
}

Good* GoodRepo::resultSetToGood(QSqlQuery* &resultSet)
{
    return new Good(
                resultSet->value(0).toString().toStdString(),
                resultSet->value(1).toString().toStdString(),
                resultSet->value(2).toDouble());
}

vector<Good*>* GoodRepo::resultSetToGoods(QSqlQuery* &resultSet)
{
    vector<Good*>* goods = new vector<Good*>();
    while(resultSet->next()) {
        goods->push_back(resultSetToGood(resultSet));
    }
    delete resultSet;
    if((int)goods->size() == 0) {
        delete goods;
        return NULL;
    }
    return goods;
}
