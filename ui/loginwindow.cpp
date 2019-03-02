#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    /*
    // An example of querying from the database.
    DBUtil* dbUtil = DBUtil::newInstance("./test.db");
    ResultSet* resultSet = dbUtil->query("select * from test;");
    if(resultSet != NULL) {
        printf("Query done.\n");
        vector<int>* nums = resultSet->getIntergeRows("num");
        vector<int>* ages = resultSet->getIntergeRows("age");
        vector<string>* names = resultSet->getStringRows("name");
        for(int i = 0; i < (int)nums->size(); i++) {
            printf("%d\t%d\t%s\n", nums->at(i), ages->at(i), names->at(i).c_str());
        }
    }
    */
    /*
    // An example of getting a new id.
    IDManager* idManager = IDManager::newInstance(G_DB_FILE, "id_storage");
    idManager->getNextID("good_id");
    */
    this->setFixedSize(400, 234);
    ui->setupUi(this);

    /*Transaction *transaction = new Transaction(12);
    transaction->addGood(new Good("978222","cup",21.6),1);
    transaction->date = "2019/01/01_14:38:00";
    QImage* image = ReceiptUtil::generate(transaction,"12.00","20.00","80.00");
    this->resize(image->size());
    ui->label->resize(image->size());
    ui->label->setPixmap(QPixmap::fromImage(*image));*/
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString typeText = this->ui->userSwitcher->currentText();
    int type = 0;
    if(typeText == "Cashier") type = 1;
    else if(typeText == "Shoper") type = 0;

    int id = this->ui->userID->text().toInt();
    int password = this->ui->userPassword->text().toInt();
    if(IdentityManager::validate(id, password, type)) {
        switch(type) {
        case 0: {
                ShoperWindow* shoperWindow = new ShoperWindow();
                shoperWindow->show();
                break;
            }
        case 1: {
                CashierWindow* cashierWindow = new CashierWindow();
                // The cashier window should be initial before show.
                cashierWindow->init(id);
                cashierWindow->show();
                break;
            }
        }
        this->close();
    }
    else {
        this->ui->tipsLabel->setText("Unknown ID or wrong password!");

        // Delay 2000ms.
        QTime timer = QTime::currentTime().addMSecs(2000);
        while(QTime::currentTime() < timer )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        this->ui->tipsLabel->setText("");
    }
}

void LoginWindow::on_userPassword_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || this->ui->userID->text().isEmpty())
        this->ui->loginButton->setEnabled(false);
    else
        this->ui->loginButton->setEnabled(true);
}

void LoginWindow::on_userID_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || this->ui->userPassword->text().isEmpty())
        this->ui->loginButton->setEnabled(false);
    else
        this->ui->loginButton->setEnabled(true);
}
