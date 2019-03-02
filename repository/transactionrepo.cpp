#include "transactionrepo.h"

TransactionRepo::TransactionRepo()
{

}

bool TransactionRepo::saveTransaction(Transaction* transaction)
{
    try {
        // TODO: Add database transaction here.
        int size = (int)transaction->goods->size();
        for(int i = 0;i < size;i++) {
            QString goodIDStr = to_qstring(transaction->goods->at(i)->id);
            QString quantityStr = to_qstring(transaction->quantities->at(i));
            QString cashierIDStr = to_qstring(transaction->cashierID);
            QString dateStr = to_qstring(transaction->date);
            QString insertValues = "(" +  cashierIDStr +
                                   ", '" +  dateStr +
                                   "' , '" + goodIDStr +
                                   "'," + quantityStr + ")";
            dbUtil->execute("insert into transaction_info values" +
                            insertValues.toStdString() + ";");
        }
    } catch(QSqlError e) {
        qDebug() << e.text();
        return false;
    }
    return true;
}

vector<Transaction*>* TransactionRepo::findByCashierID(int cashierID)
{

    QSqlQuery* resultSet = dbUtil->query(
                "select date from transaction_info where cashier_id=" +
                to_string(cashierID) +
                " group by date;");
    vector<string> dates;
    while(resultSet->next()) {
        dates.push_back(resultSet->value(0).toString().toStdString());
    }
    // The cashier does not have any transaction.
    if((int)dates.size() == 0) return NULL;

    vector<Transaction*>* transactions = new vector<Transaction*>();
    for(int i = 0;i < (int)dates.size();i++) {
        transactions->push_back(formTransaction(
                                    cashierID,
                                    dates.at(i)));
    }
    return transactions;
}
vector<Transaction*>* TransactionRepo::findByDate(string date)
{
    QSqlQuery* resultSet = dbUtil->query(
                "select * from transaction_info where date like '" +
                date +
                "%';");
    vector<Transaction*>* transactions = new vector<Transaction*>;
    while(resultSet->next()) {
        transactions->push_back(formTransaction(
                                    resultSet->value(0).toInt(),
                                    resultSet->value(1).toString().toStdString())
                                );
    }
    if((int)transactions->size() == 0) {
        delete transactions;
        return NULL;
    }
    return transactions;
}

Transaction* TransactionRepo::formTransaction(int cashierID,string date)
{
    QSqlQuery* resultSet = dbUtil->query(
                "select * from transaction_info where cashier_id=" +
                to_string(cashierID) + " and " +
                "date='" + date + "';");
    Transaction* transaction = new Transaction(cashierID);
    transaction->date = date;
    while(resultSet->next()) {
        transaction->addGood(
                    GoodRepo::findByGoodID(resultSet->value(2).toString().toStdString()),
                    resultSet->value(3).toInt());
    }
    return transaction;
}
