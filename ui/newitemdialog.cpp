#include "newitemdialog.h"
#include "ui_newitemdialog.h"

NewItemDialog::NewItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewItemDialog)
{
    ui->setupUi(this);
    this->pickedGood = NULL;

}

NewItemDialog::~NewItemDialog()
{
    delete ui;
}

void NewItemDialog::on_goodPickerButton_clicked()
{
    GoodPickerDialog* goodPickerDialog = new GoodPickerDialog(this);
    connect(goodPickerDialog,
            SIGNAL(goodPicked_signal(Good*)),
            this,
            SLOT(handle_goodPicked_signal(Good*))
            );
    goodPickerDialog->setModal(true);
    goodPickerDialog->show();
}

void NewItemDialog::handle_goodPicked_signal(Good* good)
{
    this->pickedGood = good;
    this->ui->goodNameInput->setText(to_qstring(good->name));
    this->ui->priceInput->setText(to_qstring(good->price));
}

void NewItemDialog::on_buttonBox_accepted()
{
    if((this->ui->quantityInput->text() != "") &&
            (this->ui->goodNameInput->text() != "") &&
            (this->ui->priceInput->text() != "")
            ) {
        emit newItem_signal(this->pickedGood, this->ui->quantityInput->text().toInt());
    }
}

void NewItemDialog::on_scanButton_clicked()
{
    ScanDialog* scanDialog = new ScanDialog(this);
    connect(scanDialog,
            SIGNAL(goodPicked_signal(Good*)),
            this,
            SLOT(handle_goodPicked_signal(Good*))
            );
    scanDialog->setModal(true);
    scanDialog->show();
}
