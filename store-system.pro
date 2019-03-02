#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T20:31:25
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = storesystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
\ # root
    main.cpp \
    global.cpp \
\ # ui
    ui/loginwindow.cpp \
    ui/cashierwindow.cpp \
    ui/goodpickerdialog.cpp \
    ui/newitemdialog.cpp \
    ui/memberiddialog.cpp \
    ui/shoperwindow.cpp \
    ui/scandialog.cpp \
    ui/receiptdialog.cpp \
\ # util
    util/dbutil.cpp \
    util/idmanager.cpp \
    util/identitymanager.cpp \
    util/dateutil.cpp \
    util/barcodeutil.cpp \
    util/camerautil.cpp \
    util/videosurface.cpp \
    util/receiptutil.cpp \
\ # domain
    domain/good.cpp \
    domain/transaction.cpp \
    domain/cashier.cpp \
    domain/member.cpp \
    domain/supplier.cpp \
\ # repository
    repository/goodrepo.cpp \
    repository/repo.cpp \
    repository/memberrepo.cpp \
    repository/transactionrepo.cpp \
    repository/cashierrepo.cpp \
    repository/supplierrepo.cpp \

HEADERS += \
\ # root
    global.h \
\ # ui
    ui/cashierwindow.h \
    ui/loginwindow.h \
    ui/goodpickerdialog.h \
    ui/newitemdialog.h \
    ui/memberiddialog.h \
    ui/shoperwindow.h \
    ui/scandialog.h \
    ui/receiptdialog.h \
\ # util
    util/dbutil.h \
    util/identitymanager.h \
    util/idmanager.h \
    util/dateutil.h \
    util/barcodeutil.h \
    util/camerautil.h \
    util/videosurface.h \
    util/receiptutil.h \
\ # domain
    domain/cashier.h \
    domain/good.h \
    domain/member.h \
    domain/supplier.h \
    domain/transaction.h \
\ # repository
    repository/goodrepo.h \
    repository/repo.h \
    repository/memberrepo.h \
    repository/transactionrepo.h \
    repository/cashierrepo.h \
    repository/supplierrepo.h \

FORMS += \
    ui/loginwindow.ui \
    ui/cashierwindow.ui \
    ui/goodpickerdialog.ui \
    ui/newitemdialog.ui \
    ui/memberiddialog.ui \
    ui/shoperwindow.ui \
    ui/scandialog.ui \
    ui/receiptdialog.ui

LIBS += -lsqlite3 \
        `pkg-config --libs opencv` \
        -lzbar

QT += testlib \
      sql
