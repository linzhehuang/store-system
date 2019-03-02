#include "dbutil.h"

DBUtil* DBUtil::instance = NULL;

DBUtil::DBUtil(string dbFile)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(QString::fromStdString(dbFile));
    if(!(this->db.open())) throw this->db.lastError();
}

DBUtil::~DBUtil()
{
    this->db.close();
}

DBUtil* DBUtil::newInstance(string dbFile)
{
    if(instance == NULL) {
        try {
            instance = new DBUtil(dbFile);
        } catch(QSqlError e) {
            qDebug() << e.text();
        }
    }
    return instance;
}

void DBUtil::execute(string statement)
{
    QSqlQuery sql;
    sql.prepare(QString::fromStdString(statement));
    if(!sql.exec()) {
        qDebug() << "DBUtli execute '" << QString::fromStdString(statement) << "' failed!";
        throw sql.lastError();
    }
}

QSqlQuery* DBUtil::query(string statement)
{
    QSqlQuery* sql = new QSqlQuery();
    sql->prepare(QString::fromStdString(statement));
    if(!sql->exec()) {
        qDebug() << sql->lastError();
        qDebug() << "DBUtli query '" << QString::fromStdString(statement) << "' failed!";
        return NULL;
    }
    return sql;
}
