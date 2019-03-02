#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <string>
#include "cashierwindow.h"
#include "shoperwindow.h"
#include "util/dbutil.h"
#include "util/idmanager.h"
#include "util/identitymanager.h"
#include "global.h"
#include "util/receiptutil.h"

using namespace std;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_userPassword_textChanged(const QString &arg1);
    void on_userID_textChanged(const QString &arg1);

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
