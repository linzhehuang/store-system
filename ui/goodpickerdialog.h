#ifndef GOODPICKERDIALOG_H
#define GOODPICKERDIALOG_H

#include <QDialog>
#include "glob.h"
#include "repository/goodrepo.h"

namespace Ui {
class GoodPickerDialog;
}

class GoodPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoodPickerDialog(QWidget *parent = 0);
    ~GoodPickerDialog();

signals:
    void goodPicked_signal(Good*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GoodPickerDialog *ui;
    vector<Good*>* goods;
    void renderGoodsTable();
};

#endif // GOODPICKERDIALOG_H
