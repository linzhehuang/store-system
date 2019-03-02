#ifndef MEMBERIDDIALOG_H
#define MEMBERIDDIALOG_H

#include <QDialog>

namespace Ui {
class MemberIDDialog;
}

class MemberIDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberIDDialog(QWidget *parent = 0);
    ~MemberIDDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void enterMemberID_signal(int);

private:
    Ui::MemberIDDialog *ui;
};

#endif // MEMBERIDDIALOG_H
