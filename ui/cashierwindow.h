#ifndef CASHIERWINDOW_H
#define CASHIERWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QMessageBox>
#include "ui/newitemdialog.h"
#include "ui/memberiddialog.h"
#include "ui/receiptdialog.h"
#include "domain/transaction.h"
#include "domain/member.h"
#include "util/idmanager.h"
#include "util/dateutil.h"
#include "util/receiptutil.h"
#include "repository/memberrepo.h"
#include "repository/transactionrepo.h"
#include "repository/cashierrepo.h"
#include "global.h"

namespace Ui {
class CashierWindow;
}

class CashierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashierWindow(QWidget *parent = 0);
    ~CashierWindow();
    void init(int cashierID);

private slots:
    void handle_newItem_signal(Good* good, int quantity);
    void handle_enterMemberID_signal(int memberID);
    void on_addItemButton_clicked();
    void on_removeItemButton_clicked();
    void on_memberNo_clicked(bool checked);
    void on_memberYes_clicked(bool checked);
    void on_finishButton_clicked();
    void on_registerMemberButton_clicked();
    void on_clearButton_clicked();
    void on_stageButton_clicked();
    void on_receiveInput_editingFinished();

private:
    Ui::CashierWindow *ui;
    Transaction* transaction;
    Transaction* pendingTransaction;
    Member* member;
    int cashierID;

    void createNewTransaction();
    void recoveryTransaction();
};

#endif // CASHIERWINDOW_H
