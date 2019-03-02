#include "memberiddialog.h"
#include "ui_memberiddialog.h"

MemberIDDialog::MemberIDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberIDDialog)
{
    ui->setupUi(this);
}

MemberIDDialog::~MemberIDDialog()
{
    delete ui;
}

void MemberIDDialog::on_buttonBox_accepted()
{
    QString idText = this->ui->idInput->text();
    if(idText != "") {
        emit enterMemberID_signal(idText.toInt());
    }
}
