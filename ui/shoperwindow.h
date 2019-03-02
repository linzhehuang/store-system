#ifndef SHOPERWINDOW_H
#define SHOPERWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QMessageBox>
#include "goodpickerdialog.h"
#include "util/dateutil.h"
#include "util/idmanager.h"
#include "util/identitymanager.h"
#include "repository/transactionrepo.h"
#include "repository/cashierrepo.h"
#include "repository/supplierrepo.h"

namespace Ui {
class ShoperWindow;
}

class ShoperWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShoperWindow(QWidget *parent = 0);
    ~ShoperWindow();

private slots:
    void handle_goodPicked_signal(Good* good);
    void on_addCashierButton_clicked();
    void on_cashierTable_clicked(const QModelIndex &index);
    void on_deleteCashierButton_clicked();
    void on_addSupplierButton_clicked();
    void on_deleteSupplierButton_clicked();
    void on_supplierList_clicked(const QModelIndex &index);
    void on_moreGoodButton_clicked();
    void on_addGoodButton_clicked();
    void on_deleteGoodButton_clicked();
    void on_addGoodsButton_clicked();
    void on_deleteGoodsButton_clicked();
    void on_updateGoodsButton_clicked();
    void on_goodsTable_clicked(const QModelIndex &index);
    void on_clearButton_clicked();

private:
    Ui::ShoperWindow *ui;
    void showLastWeekTranscation();
    void showCashiers();
    void showSuppliers();
    void showGoods();
    void showAllGoods();
    vector<Supplier*>* suppliers;
    Supplier* selectedSupplier;
    Good* selectedGood;
};

#endif // SHOPERWINDOW_H
