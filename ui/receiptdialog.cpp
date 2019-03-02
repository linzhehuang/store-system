#include "receiptdialog.h"
#include "ui_receiptdialog.h"

ReceiptDialog::ReceiptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiptDialog)
{
    ui->setupUi(this);
}

ReceiptDialog::~ReceiptDialog()
{
    delete ui;
}

void ReceiptDialog::setImage(QImage* &image)
{
    this->resize(image->size());
    this->setFixedSize(image->size());
    ui->receiptView->resize(image->size());
    ui->receiptView->setGeometry(0,0,image->width(),image->height());
    ui->receiptView->setPixmap(QPixmap::fromImage(*image));
}
