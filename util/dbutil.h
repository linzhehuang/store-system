#ifndef DBUTIL_H
#define DBUTIL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <string>
using namespace std;

class DBUtil
{
public:
    ~DBUtil();
    static DBUtil* newInstance(string dbFile);
    void execute(string statement);
    QSqlQuery* query(string statement);
private:
    DBUtil(string dbFile);
    static DBUtil* instance;
    QSqlDatabase db;
};

#endif // DBUTIL_H
