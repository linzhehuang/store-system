#include "ui/loginwindow.h"
#include "ui/cashierwindow.h"
#include "ui/goodpickerdialog.h"
#include "ui/shoperwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //*
    //*/
    QApplication a(argc, argv);
    /*ShoperWindow shoperWindow;
    shoperWindow.show();*/
    //*
    // The cashier window should be initial before show.
    /*CashierWindow cashierWindow;
    cashierWindow.init(2);
    cashierWindow.show();*/
    //*/
    LoginWindow w;
    w.show();

    return a.exec();
}
