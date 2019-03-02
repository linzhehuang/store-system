#include "cashierwindow.h"
#include "ui_cashierwindow.h"

CashierWindow::CashierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierWindow)
{
    this->transaction = NULL;
    this->pendingTransaction = NULL;
    this->member = NULL;
    ui->setupUi(this);
}

CashierWindow::~CashierWindow()
{
    delete ui;
    if(this->transaction != NULL) {
        delete this->transaction;
    }
}

void CashierWindow::init(int cashierID)
{
    this->cashierID =cashierID;
    Cashier* cashier = CashierRepo::findByID(cashierID);
    this->ui->cashierName->setText(to_qstring(cashier->name));
    delete cashier;

    this->createNewTransaction();
    this->member = NULL;

    while(this->ui->orderTable->rowCount())
        this->ui->orderTable->removeRow(0);
    this->ui->memberNo->setChecked(true);
    this->ui->memberYes->setChecked(false);
    this->ui->amountLabel->setText("0.00");
    this->ui->changeLabel->setText("0.00");
    this->ui->receiveInput->setText("");
    emit on_memberNo_clicked(true);
}

void CashierWindow::on_addItemButton_clicked()
{
    NewItemDialog* newItemDialog = new NewItemDialog(this);
    connect(newItemDialog,
            SIGNAL(newItem_signal(Good*,int)),
            this,
            SLOT(handle_newItem_signal(Good*,int))
            );
    newItemDialog->setModal(true);
    newItemDialog->show();
}

void CashierWindow::handle_newItem_signal(Good* good, int quantity)
{
    transaction->addGood(good, quantity);
    QTableWidgetItem  *nameItem = new QTableWidgetItem(to_qstring(good->name)),
                      *priceItem = new QTableWidgetItem(to_qstring(good->price)),
                      *quantityItem = new QTableWidgetItem(to_qstring(quantity));

    // Set not editable.
    nameItem->setFlags((Qt::ItemFlags) 32);
    priceItem->setFlags((Qt::ItemFlags) 32);
    quantityItem->setFlags((Qt::ItemFlags) 32);

    int index = this->ui->orderTable->rowCount();

    this->ui->orderTable->insertRow(index);
    this->ui->orderTable->setItem(index, 0, nameItem);
    this->ui->orderTable->setItem(index, 1, priceItem);
    this->ui->orderTable->setItem(index, 2, quantityItem);
    // Update amount label.
    this->ui->amountLabel->setText(
                to_qstring(this->transaction->getAmount(this->member))
                );
}

void CashierWindow::handle_enterMemberID_signal(int memberID)
{
    Member* member = MemberRepo::findByMemberID(memberID);
    //qDebug("%d", memberID);
    if(member == NULL) {
        this->ui->memberNo->setChecked(true);
        this->ui->memberYes->setChecked(false);
        emit on_memberNo_clicked(true);
        this->ui->statusbar->showMessage("No the member id '" +
                                         to_qstring(memberID) + "'.",
                                         6000);
    }
    this->member = member;
}

void CashierWindow::on_removeItemButton_clicked()
{
    int index = this->ui->orderTable->currentRow();
    if(index >= 0) {
        this->ui->orderTable->removeRow(index);
        this->transaction->deleteGoodByIndex(index);
        this->ui->amountLabel->setText(
                    to_qstring(this->transaction->getAmount(this->member))
                    );
    }
}

void CashierWindow::on_memberNo_clicked(bool checked)
{
    if(checked) {
        if(this->member != NULL) {
            delete member;
            this->member = NULL;
        }
        this->ui->amountLabel->setText(
                    to_qstring(this->transaction->getAmount(this->member))
                    );
    }
}

void CashierWindow::on_memberYes_clicked(bool checked)
{
    if(checked) {
        MemberIDDialog* memberIDDialog = new MemberIDDialog(this);
        connect(memberIDDialog,
                SIGNAL(enterMemberID_signal(int)),
                this,
                SLOT(handle_enterMemberID_signal(int))
                );
        memberIDDialog->setModal(true);
        memberIDDialog->show();

        if(memberIDDialog->exec() == QDialog::Rejected) {
            this->ui->memberNo->setChecked(true);
            this->ui->memberYes->setChecked(false);
            emit on_memberNo_clicked(true);
        }

        this->ui->amountLabel->setText(
                    to_qstring(this->transaction->getAmount(this->member))
                    );
    }
}

void CashierWindow::on_finishButton_clicked()
{
    // Do nothing when no item is added.
    if((int)this->transaction->goods->size() == 0) return;
    if(this->ui->receiveInput->text() == "") return;

    this->transaction->date = DateUtil::currentTimeStamp().toStdString();
    if(!TransactionRepo::saveTransaction(transaction)) {
        this->ui->statusbar->showMessage("Can't finish the transaction!",
                                          6000);
        return;
    }
    this->ui->statusbar->showMessage("Finish the transaction at " +
                                      to_qstring(this->transaction->date)
                                      + ".",
                                     6000);
    // Display the receipt dialog.
    ReceiptDialog* receiptDialog = new ReceiptDialog(this);
    QImage* receiptImage = ReceiptUtil::generate(
                transaction,
                ui->amountLabel->text(),
                to_qstring(ui->receiveInput->text().toStdString()),
                ui->changeLabel->text());
    receiptDialog->setImage(receiptImage);
    receiptDialog->setModal(true);
    receiptDialog->show();

    this->init(this->cashierID);
}

void CashierWindow::createNewTransaction()
{
    if(this->transaction != NULL) {
        delete this->transaction;
        this->transaction = NULL;
    }
    this->transaction = new Transaction(this->cashierID);
}

void CashierWindow::on_registerMemberButton_clicked()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(
                this,
                "Confirm",
                "Are you sure to create new member?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes);
    if(ret == QMessageBox::No) return;

    IDManager* idManager = IDManager::newInstance(G_DB_FILE, G_ID_TABLE);
    int id = idManager->getNextID("member");
    Member* member = new Member(id);
    MemberRepo::saveMember(member);
    QMessageBox::about(this, "Success", "The member ID is " + to_qstring(member->id) + ".");
    delete member;
}

void CashierWindow::on_clearButton_clicked()
{
    if(this->pendingTransaction != NULL) {
        delete this->pendingTransaction;
        this->pendingTransaction = NULL;
        this->ui->clearButton->setEnabled(false);
        this->ui->stageButton->setText("Stage");
    }
}

void CashierWindow::on_stageButton_clicked()
{
    if(this->pendingTransaction == NULL) {
        // Stage the transaction.
        if(this->transaction == NULL) return;
        if((int)this->transaction->goods->size() == 0) {
            this->ui->statusbar->showMessage("Can't stage a empty transaction.",
                                             6000);
            return;
        }
        this->pendingTransaction = this->transaction;

        // Avoid the init method delete the transaction.
        this->transaction = NULL;

        //qDebug("%p", this->pendingTransaction);

        // Create a new transaction.
        this->init(this->cashierID);

        this->ui->clearButton->setEnabled(true);
        this->ui->stageButton->setText("Take out");

        // Display the success message.
        this->ui->statusbar->showMessage("Stage the transaction success.",
                                         6000);
    }
    else {
        // Take out the pending transaction.
        if(this->transaction != NULL) {
            delete this->transaction;
        }
        this->transaction = this->pendingTransaction;
        this->pendingTransaction = NULL;

        //qDebug("%p", this->transaction);

        this->recoveryTransaction();
        this->ui->clearButton->setEnabled(false);
        this->ui->stageButton->setText("Stage");
    }
}

void CashierWindow::recoveryTransaction()
{
    while(this->ui->orderTable->rowCount())
        this->ui->orderTable->removeRow(0);

    for(int i = 0;i < (int)this->transaction->goods->size();i++) {
        Good* good = this->transaction->goods->at(i);
        int quantity = this->transaction->quantities->at(i);

        QTableWidgetItem  *nameItem = new QTableWidgetItem(to_qstring(good->name)),
                          *priceItem = new QTableWidgetItem(to_qstring(good->price)),
                          *quantityItem = new QTableWidgetItem(to_qstring(quantity));

        // Set not editable.
        nameItem->setFlags((Qt::ItemFlags) 32);
        priceItem->setFlags((Qt::ItemFlags) 32);
        quantityItem->setFlags((Qt::ItemFlags) 32);

        this->ui->orderTable->insertRow(i);
        this->ui->orderTable->setItem(i, 0, nameItem);
        this->ui->orderTable->setItem(i, 1, priceItem);
        this->ui->orderTable->setItem(i, 2, quantityItem);
    }
    // Update amount label.
    this->ui->amountLabel->setText(
                to_qstring(this->transaction->getAmount(this->member))
                );

    this->ui->memberNo->setChecked(true);
    this->ui->memberYes->setChecked(false);
    this->ui->changeLabel->setText("0.00");
    this->ui->receiveInput->setText("");
    emit on_memberNo_clicked(true);
}

void CashierWindow::on_receiveInput_editingFinished()
{
    QString receiveText = this->ui->receiveInput->text();
    if(receiveText.isEmpty()) {
        this->ui->changeLabel->setText(to_qstring(0.0));
        return;
    }

    double amount = this->ui->amountLabel->text().toDouble();
    double receive = receiveText.toDouble();
    if(receive < amount) {
        this->ui->receiveInput->setText("");
        this->ui->statusbar->showMessage("The receive is lower than amount.",
                                         6000);
        return;
    }

    double change = receive - amount;
    this->ui->changeLabel->setText(to_qstring(change));
}
