#include "idmanager.h"

IDManager::IDManager(string dbFile, string tableName)
{
    this->dbFile = dbFile;
    this->tableName = tableName;
    this->idStorage = new map<string, int>();
    // Recovery id storage from database.
    DBUtil* dbUtil = DBUtil::newInstance(this->dbFile);
    QSqlQuery* resultSet = dbUtil->query("select * from " + this->tableName + ";");
    if(resultSet != NULL) {
        while(resultSet->next()) {
            this->idStorage->insert(
                        pair<string, int>(
                            resultSet->value(0).toString().toStdString(),
                            resultSet->value(1).toInt())
                        );
        }
        delete resultSet;
    }
}

IDManager* IDManager::instance = NULL;

IDManager* IDManager::newInstance(string dbFile, string tableName)
{
    if(instance == NULL) {
        instance = new IDManager(dbFile, tableName);
    }
    return instance;
}

int IDManager::getNextID(string idName)
{
    int nextID = this->idStorage->find(idName)->second;
    this->idStorage->find(idName)->second = nextID+1;
    this->saveIDs();
    return nextID;
}

void IDManager::saveIDs()
{
    DBUtil* dbUtil = DBUtil::newInstance(this->dbFile);
    map<string, int>::iterator it = this->idStorage->begin();
    while(it != this->idStorage->end()) {
        dbUtil->execute("update " +
                      this->tableName +
                      " set current_id=" +
                      to_string(it->second) +
                      " where id_name='" +
                      it->first + "';");
        it++;
    }
}
