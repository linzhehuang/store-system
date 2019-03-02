#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <QString>
using namespace std;

extern const string G_DB_FILE;
extern const string G_ID_TABLE;
extern QString to_qstring(int src);
extern QString to_qstring(double src);
extern QString to_qstring(string src);

#endif // GLOBAL_H
