#include "dateutil.h"

QString DateUtil::dateFormat = "yyyy-MM-dd";
QString DateUtil::timeFormat = "hh:mm:ss";

DateUtil::DateUtil()
{

}

QString DateUtil::currentTimeStamp()
{
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    QString strDate = currentDate.toString(dateFormat);
    QString strTime = currentTime.toString(timeFormat);
    return strDate + "_" + strTime;
}
QString DateUtil::toString(QDate &date)
{
    return date.toString(dateFormat);
}

QString DateUtil::formatDate(int y,int m,int d)
{
    return QDate(y,m,d).toString(dateFormat);
}

QString DateUtil::formatTime(int h,int m,int s)
{
    return QDate(h,m,s).toString(timeFormat);
}

