#ifndef RECEIPTDIALOG_H
#define RECEIPTDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QDebug>

namespace Ui {
class ReceiptDialog;
}

class ReceiptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiptDialog(QWidget *parent = 0);
    ~ReceiptDialog();
    void setImage(QImage* &image);

private:
    Ui::ReceiptDialog *ui;
};

#endif // RECEIPTDIALOG_H
