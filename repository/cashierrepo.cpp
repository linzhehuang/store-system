#include "cashierrepo.h"

CashierRepo::CashierRepo()
{

}

vector<Cashier*>* CashierRepo::findAll()
{
    QSqlQuery* resultSet = dbUtil->query("select * from cashier_info;");
    vector<Cashier*>* cashiers = new vector<Cashier*>();
    while(resultSet->next()) {
        cashiers->push_back(new Cashier(
                                resultSet->value(0).toInt(),
                                resultSet->value(1).toString().toStdString()));
    }
    if((int)cashiers->size() == 0) {
        delete cashiers;
        return NULL;
    }
    return cashiers;
}

Cashier* CashierRepo::findByID(int id)
{
    QSqlQuery* resultSet = dbUtil->query("select * from cashier_info where id=" +
                                         to_string(id) + ";");
    if(!resultSet->next()) return NULL;
    return new Cashier(id,
                       resultSet->value(1).toString().toStdString());
}

void CashierRepo::saveCashier(Cashier* cashier)
{
    dbUtil->execute("insert into cashier_info values("
                    + to_string(cashier->id) + ",'"
                    + cashier->name + "');");
}

void CashierRepo::deleteByID(int id)
{
    dbUtil->execute("delete from cashier_info where id="
                    + to_string(id) + ";");
}
