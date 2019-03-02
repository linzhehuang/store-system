#include "identitymanager.h"

DBUtil* IdentityManager::dbUtil = DBUtil::newInstance(G_DB_FILE);

IdentityManager::IdentityManager()
{

}

bool IdentityManager::validate(int id, int password, int type)
{
    // TYPE:0-shoper 1-cashier
    QSqlQuery* resultSet = dbUtil->query(
                "select * from user_info where id=" +
                to_string(id) +
                " and password=" + to_string(password) +
                " and type=" + to_string(type));
    if(!resultSet->next()) return false;

    int retID = resultSet->value(0).toInt();
    int retPassword = resultSet->value(1).toInt();

    if(retID != id || retPassword != password) return false;

    return true;
}

void IdentityManager::addNewUser(int id,int password,int type)
{
    dbUtil->execute("insert into user_info values(" +
                    to_string(id) + "," +
                    to_string(password) + "," +
                    to_string(type) + ");");
}

void IdentityManager::deleteUser(int id,int type)
{
    dbUtil->execute("delete from user_info where id=" +
                    to_string(id) + " and type=" +
                    to_string(type) + ";");
}
