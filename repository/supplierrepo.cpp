#include "supplierrepo.h"

SupplierRepo::SupplierRepo()
{

}

vector<Supplier*>* SupplierRepo::findAll()
{
    vector<Supplier*>* suppliers = new vector<Supplier*>();
    QSqlQuery* resultSet = dbUtil->query("select * from supplier_info;");
    while(resultSet->next()) {
        suppliers->push_back(formSupplier(
                                 resultSet->value(0).toInt(),
                                 resultSet->value(1).toString().toStdString()));
    }
    if((int)suppliers->size() == 0) return NULL;
    return suppliers;
}

vector<Supplier*>* SupplierRepo::findByGoodID(string goodID)
{
    vector<Supplier*>* suppliers = new vector<Supplier*>();
    QSqlQuery* resultSet = dbUtil->query("select * from supply_chain where good_id='" +
                                         goodID +
                                         "' group by supplier_id;");
    while(resultSet->next()) {
        suppliers->push_back(findByID(resultSet->value(0).toInt()));
    }
    if((int)suppliers->size() == 0) return NULL;
    return suppliers;
}

Supplier* SupplierRepo::findByID(int id)
{
    QSqlQuery* resultSet = dbUtil->query("select * from supplier_info where id=" +
                                         to_string(id) + ";");
    if(!resultSet->next()) return NULL;

    return formSupplier(resultSet->value(0).toInt(),
                        resultSet->value(1).toString().toStdString());
}

void SupplierRepo::saveSupplier(Supplier* &supplier)
{
    dbUtil->execute("insert into supplier_info values(" +
                    to_string(supplier->id) + ",'" +
                    supplier->name + "');");
    for(int i = 0;i < (int)supplier->goodIDs->size();i++) {
        string goodID = supplier->goodIDs->at(i);
        string buyingPrice = to_string(supplier->buyingPrices->at(i));
        dbUtil->execute("insert into supply_chain values(" +
                        to_string(supplier->id) + ",'" +
                        goodID + "'," +
                        buyingPrice + ");");
    }
}

void SupplierRepo::deleteByID(int id)
{
    dbUtil->execute("delete from supplier_info where id=" +
                    to_string(id) + ";");
    dbUtil->execute("delete from supply_chain where supplier_id=" +
                    to_string(id) + ";");
}

Supplier* SupplierRepo::formSupplier(int id,string name)
{
    Supplier* supplier = new Supplier(id, name);
    QSqlQuery* resultSet = dbUtil->query("select * from supply_chain where supplier_id="
                                         + to_string(id) + ";");
    if(!resultSet) return supplier;
    while(resultSet->next()) {
        supplier->addGood(resultSet->value(1).toString().toStdString(),
                          resultSet->value(2).toDouble());
    }

    delete resultSet;
    return supplier;
}
