#include "goodpickerdialog.h"
#include "ui_goodpickerdialog.h"

GoodPickerDialog::GoodPickerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoodPickerDialog)
{
    ui->setupUi(this);
    this->goods = GoodRepo::findAll();
    if(this->goods != NULL) {
        this->renderGoodsTable();
    }
}

GoodPickerDialog::~GoodPickerDialog()
{
    delete ui;
}

void GoodPickerDialog::renderGoodsTable()
{
    this->ui->goodsTable->clearContents();
    for(int i = 0;i < (int)this->goods->size();i++) {
        QTableWidgetItem  *idItem = new QTableWidgetItem(to_qstring(this->goods->at(i)->id)),
                          *nameItem = new QTableWidgetItem(to_qstring(this->goods->at(i)->name)),
                          *priceItem = new QTableWidgetItem(to_qstring(this->goods->at(i)->price));
        // Settings not editable.
        idItem->setFlags((Qt::ItemFlags) 32);
        nameItem->setFlags((Qt::ItemFlags) 32);
        priceItem->setFlags((Qt::ItemFlags) 32);

        this->ui->goodsTable->insertRow(i);
        this->ui->goodsTable->setItem(i, 0, idItem);
        this->ui->goodsTable->setItem(i, 1, nameItem);
        this->ui->goodsTable->setItem(i, 2, priceItem);
    }
}

void GoodPickerDialog::on_buttonBox_accepted()
{
    int index = this->ui->goodsTable->currentRow();
    if(index >= 0) {
        emit goodPicked_signal(this->goods->at(index));
    }
}
