#ifndef IDMANAGER_H
#define IDMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <QString>
#include "util/dbutil.h"

using namespace std;

class IDManager
{
public:
    static IDManager* newInstance(string dbFile, string tableName);
    int getNextID(string idName);
private:
    IDManager(string dbFile, string tableName);
    static IDManager* instance;
    map<string, int>* idStorage;
    string dbFile, tableName;
    void saveIDs();
};

#endif // IDMANAGER_H
