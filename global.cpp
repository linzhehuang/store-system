#include "global.h"

const string G_DB_FILE = "./core.db";
const string G_ID_TABLE = "id_storage";

QString to_qstring(int src)
{
    return QString(to_string(src).c_str());
}

QString to_qstring(double src)
{
    string str;
    sprintf((char*)str.c_str(), "%.2f", src);
    return QString(str.c_str());
}

QString to_qstring(string src)
{
    return QString(src.c_str());
}
