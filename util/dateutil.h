#ifndef DATEUTIL_H
#define DATEUTIL_H

#include <QDate>
#include <QString>
#include <QTime>

class DateUtil
{
public:
    DateUtil();
    static QString currentTimeStamp();
    static QString toString(QDate &date);
    static QString formatDate(int y,int m,int d);
    static QString formatTime(int h,int m,int s);
    static QString dateFormat;
    static QString timeFormat;
};

#endif // DATEUTIL_H
