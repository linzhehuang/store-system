#ifndef NEWITEMDIALOG_H
#define NEWITEMDIALOG_H

#include <QDialog>
#include "global.h"
#include "domain/good.h"
#include "ui/goodpickerdialog.h"
#include "ui/scandialog.h"

namespace Ui {
class NewItemDialog;
}

class NewItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewItemDialog(QWidget *parent = 0);
    ~NewItemDialog();
private slots:
    void on_goodPickerButton_clicked();
    void handle_goodPicked_signal(Good*);
    void on_buttonBox_accepted();
    void on_scanButton_clicked();

signals:
    void newItem_signal(Good*,int);

private:
    Ui::NewItemDialog *ui;
    Good* pickedGood;
};

#endif // NEWITEMDIALOG_H
