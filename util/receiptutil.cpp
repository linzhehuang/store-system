#include "receiptutil.h"

const int ReceiptUtil::BASE_HEIGHT = 240;
const int ReceiptUtil::LINE_HEIGHT = 20;

ReceiptUtil::ReceiptUtil()
{

}

QImage* ReceiptUtil::generate(Transaction *&transaction,
                              QString amount,QString receive,QString change)
{
    int currentLine = 1;
    int itemLen = (int)transaction->goods->size();
    QImage* image = new QImage(240,BASE_HEIGHT+(itemLen*LINE_HEIGHT),
                               QImage::Format_Mono);
    QPainter painter(image);
    // Draw the background.
    QPen pen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(QRect(QPoint(0,0),image->size()));
    // Draw the header.
    drawText(painter,"BEAR STORE",currentLine++);
    drawText(painter,"",currentLine++);
    drawText(painter,"NAME\t\tQTY",currentLine++);
    drawText(painter,"------------------------",currentLine++);
    // Draw the item.
    for(int i = 0;i < itemLen;i++) {
        Good* good = transaction->goods->at(i);
        int quantity = transaction->quantities->at(i);
        drawText(painter,
                 to_qstring(good->name) + "\t\t" + to_qstring(quantity),
                 currentLine++);
    }
    // Draw the foot.
    drawText(painter,"------------------------",currentLine++);
    drawText(painter,"AMOUNT:"+amount,currentLine++);
    drawText(painter,"RECEIVE:"+receive,currentLine++);
    drawText(painter,"CHANGE:"+change,currentLine++);
    drawText(painter,"TIME:"+to_qstring(transaction->date),currentLine++);
    drawText(painter,"",currentLine++);
    drawText(painter,"Thanks for coming!",currentLine++);
    return image;
}

void ReceiptUtil::drawText(QPainter &painter, QString text, int line)
{
    QPen oldPen = painter.pen();
    // Configure font style.
    QFont font;
    font.setFamily("SimHei");
    font.setPointSize(12);
    painter.setFont(font);
    // Draw the text.
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawText(0, (line*LINE_HEIGHT),text);
    painter.setPen(oldPen);
}
