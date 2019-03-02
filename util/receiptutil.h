#ifndef RECEIPTUTIL_H
#define RECEIPTUTIL_H

#include <QImage>
#include <QPainter>
#include "domain/transaction.h"
#include "global.h"

class ReceiptUtil
{
public:
    ReceiptUtil();
    static QImage* generate(Transaction* &transaction,
                            QString amount, QString receive, QString change);
private:
    const static int BASE_HEIGHT;
    const static int LINE_HEIGHT;
    static void drawText(QPainter &painter, QString text,int line);
};

#endif // RECEIPTUTIL_H
