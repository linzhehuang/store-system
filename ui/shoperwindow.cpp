#include "shoperwindow.h"
#include "ui_shoperwindow.h"

ShoperWindow::ShoperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShoperWindow)
{
    ui->setupUi(this);
    this->selectedSupplier = NULL;
    this->showLastWeekTranscation();
    this->showCashiers();
    this->showSuppliers();
    this->showGoods();
    this->showAllGoods();
}

ShoperWindow::~ShoperWindow()
{
    delete ui;
}

void ShoperWindow::showLastWeekTranscation()
{
    QString output = "";
    output += "LAST WEEK TRANSCATION\n\n";
    QDate currentDate = QDate::currentDate();
    qint64 currentDay = currentDate.toJulianDay();
    for(qint64 diff = 0;diff < 7;diff++) {
        QDate tmpDate = QDate::fromJulianDay(currentDay-diff);
        QString currentDateStr = DateUtil::toString(tmpDate);
        vector<Transaction*>* transactions = TransactionRepo::findByDate(
                    currentDateStr.toStdString());
        output += "--------------------------" +
                currentDateStr +
                "--------------------------\n";
        if(!transactions) {
            output += "NOTHING\n\n";
            continue;
        }
        for(int i = 0;i < (int)transactions->size();i++) {
            output += "----------------------------------\n";
            output += "|Name\tQuantity\n";
            vector<Good*>* goods = transactions->at(i)->goods;
            vector<int>* quantities = transactions->at(i)->quantities;
            for(int j = 0;j < (int)goods->size();j++) {
                output += "|";
                output += to_qstring(goods->at(j)->name) + "\t";
                output += to_qstring(quantities->at(j)) + "\n";
            }
            output += "----------------------------------\n";
        }
        output += "\n";
    }
    this->ui->transactionOutput->setText(output);
    //this->ui->transactionOutput->setHtml(output);
}

void ShoperWindow::showCashiers()
{
    while(this->ui->cashierTable->rowCount())
        this->ui->cashierTable->removeRow(0);

    vector<Cashier*>* cashiers = CashierRepo::findAll();
    if(cashiers == NULL) return;
    for(int i = 0;i < (int)cashiers->size();i++) {
        QTableWidgetItem  *idItem = new QTableWidgetItem(to_qstring(cashiers->at(i)->id)),
                          *nameItem = new QTableWidgetItem(to_qstring(cashiers->at(i)->name));
        // Settings not editable.
        idItem->setFlags((Qt::ItemFlags) 32);
        nameItem->setFlags((Qt::ItemFlags) 32);

        this->ui->cashierTable->insertRow(i);
        this->ui->cashierTable->setItem(i, 0, idItem);
        this->ui->cashierTable->setItem(i, 1, nameItem);

        delete cashiers->at(i);
    }
    delete cashiers;
}

void ShoperWindow::showSuppliers()
{
    while(this->ui->supplierList->count())
        this->ui->supplierList->takeItem(0);

    this->suppliers = SupplierRepo::findAll();
    if(this->suppliers == NULL) return;
    for(int i = 0;i < (int)this->suppliers->size();i++) {
        this->ui->supplierList->addItem(
                    to_qstring(this->suppliers->at(i)->name));
    }
}
void ShoperWindow::showGoods()
{
    if(this->selectedSupplier == NULL) return;

    while(this->ui->goodTable->rowCount())
        this->ui->goodTable->removeRow(0);

    vector<string>* goodIDs = this->selectedSupplier->goodIDs;
    vector<double>* buyingPrice = this->selectedSupplier->buyingPrices;
    for(int i = 0;i < (int)goodIDs->size();i++) {
        Good* good = GoodRepo::findByGoodID(goodIDs->at(i));
        if(good == NULL) return;
        QTableWidgetItem  *idItem = new QTableWidgetItem(to_qstring(good->id)),
                          *nameItem = new QTableWidgetItem(to_qstring(good->name)),
                          *priceItem = new QTableWidgetItem(to_qstring(good->price)),
                          *buyingPriceItem = new QTableWidgetItem(to_qstring(buyingPrice->at(i)));

        // Settings not editable.
        idItem->setFlags((Qt::ItemFlags) 32);
        nameItem->setFlags((Qt::ItemFlags) 32);
        priceItem->setFlags((Qt::ItemFlags) 32);
        buyingPriceItem->setFlags((Qt::ItemFlags) 32);

        this->ui->goodTable->insertRow(i);
        this->ui->goodTable->setItem(i, 0, idItem);
        this->ui->goodTable->setItem(i, 1, nameItem);
        this->ui->goodTable->setItem(i, 2, priceItem);
        this->ui->goodTable->setItem(i, 3, buyingPriceItem);
    }
}

void ShoperWindow::on_addCashierButton_clicked()
{
    QString name = this->ui->cashierNameInput->text();
    if(name == "") return;

    IDManager* idManger = IDManager::newInstance(G_DB_FILE, G_ID_TABLE);
    Cashier* cashier = new Cashier(
                idManger->getNextID("cashier"),
                name.toStdString());
    CashierRepo::saveCashier(cashier);
    // Create a new user(cashier type) with the password that is the same as id.
    IdentityManager::addNewUser(cashier->id,cashier->id,1);

    // Refresh the cashiers table.
    this->ui->cashierNameInput->setText("");
    this->showCashiers();
}

void ShoperWindow::on_cashierTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString output = "";
    if(row < 0) return;
    int id = this->ui->cashierTable->item(row,0)->text().toInt();
    QString name = this->ui->cashierTable->item(row,1)->text();

    vector<Transaction*>* transactions = TransactionRepo::findByCashierID(id);
    if(transactions == NULL) {
        output += "ID:" + to_qstring(id) + "\n";
        output += "Name:" + name + "\n";
        output += "Work Capacity:" + to_qstring(0) + "\n";
        output += "Transaction Number: " + to_qstring(0);

        this->ui->cashierOutput->setText(output);
        return;
    }
    // Calculate the work capacity.
    double amount = 0;
    for(int i = 0;i < (int)transactions->size();i++) {
        amount += transactions->at(i)->getAmount(NULL);
    }
    int transactionNum = (int)transactions->size();

    output += "ID: " + to_qstring(id) + "\n";
    output += "Name: " + name + "\n";
    output += "Work Capacity: " + to_qstring(amount) + "\n";
    output += "Transaction Number: " + to_qstring(transactionNum);

    this->ui->cashierOutput->setText(output);
}

void ShoperWindow::on_deleteCashierButton_clicked()
{
    int row = this->ui->cashierTable->currentRow();
    if(row < 0) return;

    QMessageBox::StandardButton ret = QMessageBox::warning(
                this,
                "Confirm",
                "Are you sure to delete the cashier?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes);
    if(ret == QMessageBox::No) return;

    int id = this->ui->cashierTable->item(row,0)->text().toInt();
    CashierRepo::deleteByID(id);
    IdentityManager::deleteUser(id,0);
    this->ui->cashierTable->removeRow(row);
}

void ShoperWindow::on_addSupplierButton_clicked()
{
    string name = this->ui->supplierNameInput->text().toStdString();
    if(name == "") return;

    IDManager* idManager = IDManager::newInstance(G_DB_FILE, G_ID_TABLE);
    Supplier* supplier = new Supplier(idManager->getNextID("supplier"),
                                       name);

    SupplierRepo::saveSupplier(supplier);
    this->suppliers->push_back(supplier);
    // Refresh the ui.
    this->showSuppliers();
    this->ui->supplierNameInput->setText("");
}

void ShoperWindow::on_deleteSupplierButton_clicked()
{
    int row = this->ui->supplierList->currentRow();
    if(row < 0) return;

    QMessageBox::StandardButton ret = QMessageBox::warning(
                this,
                "Confirm",
                "Are you sure to delete the supplier?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes);
    if(ret == QMessageBox::No) return;

    int id = this->suppliers->at(row)->id;

    vector<Supplier*>::iterator it = this->suppliers->begin() + row;
    SupplierRepo::deleteByID(id);
    this->suppliers->erase(it);

    this->showSuppliers();
}

void ShoperWindow::on_supplierList_clicked(const QModelIndex &index)
{
    int row = index.row();
    if(row < 0 ) return;

    this->selectedSupplier = this->suppliers->at(row);
    this->showGoods();
}

void ShoperWindow::on_moreGoodButton_clicked()
{
    GoodPickerDialog* goodPickerDialog = new GoodPickerDialog(this);
    connect(goodPickerDialog,
            SIGNAL(goodPicked_signal(Good*)),
            this,
            SLOT(handle_goodPicked_signal(Good*))
            );
    goodPickerDialog->setModal(true);
    goodPickerDialog->show();
}

void ShoperWindow::handle_goodPicked_signal(Good* good)
{
    this->selectedGood = good;
    this->ui->goodNameInput->setText(to_qstring(good->name));
    this->ui->priceInput->setText(to_qstring(good->price));
}

void ShoperWindow::on_addGoodButton_clicked()
{
    if(this->selectedSupplier == NULL) return;
    if(this->ui->goodNameInput->text() == "" ||
            this->ui->buyingPriceInput->text() == "") return;

    SupplierRepo::deleteByID(this->selectedSupplier->id);
    this->selectedSupplier->addGood(this->selectedGood->id,
                                    this->ui->buyingPriceInput->text().toDouble());
    SupplierRepo::saveSupplier(this->selectedSupplier);

    this->selectedGood = NULL;
    this->ui->goodNameInput->setText("");
    this->ui->priceInput->setText("");
    this->ui->buyingPriceInput->setText("");
    this->showGoods();
}

void ShoperWindow::on_deleteGoodButton_clicked()
{
    if(this->selectedSupplier == NULL) return;
    int row = this->ui->goodTable->currentRow();
    if(row < 0) return;

    string id = this->ui->goodTable->item(row,0)->text().toStdString();
    SupplierRepo::deleteByID(this->selectedSupplier->id);
    this->selectedSupplier->deleteGoodByGoodID(id);
    SupplierRepo::saveSupplier(this->selectedSupplier);

    this->showGoods();
}

void ShoperWindow::on_addGoodsButton_clicked()
{
    QString name = this->ui->goodsNameInput->text();
    QString price = this->ui->goodsPriceInput->text();
    QString id = this->ui->goodsIDInput->text();

    if(name.isEmpty() || price.isEmpty() || id.isEmpty()) return;

    Good* good = new Good(id.toStdString(),
                          name.toStdString(),
                          price.toDouble());
    GoodRepo::saveGood(good);
    delete good;

    this->ui->goodsIDInput->setText("");
    this->ui->goodsNameInput->setText("");
    this->ui->goodsPriceInput->setText("");
    this->showAllGoods();
}

void ShoperWindow::showAllGoods()
{
    while(this->ui->goodsTable->rowCount())
        this->ui->goodsTable->removeRow(0);

    vector<Good*>* goods = GoodRepo::findAll();
    if(goods == NULL) return;

    for(int i = 0;i < (int)goods->size();i++) {
        Good* good = goods->at(i);
        QTableWidgetItem  *idItem = new QTableWidgetItem(to_qstring(good->id)),
                          *nameItem = new QTableWidgetItem(to_qstring(good->name)),
                          *priceItem = new QTableWidgetItem(to_qstring(good->price));

        // Settings not editable.
        idItem->setFlags((Qt::ItemFlags) 32);
        nameItem->setFlags((Qt::ItemFlags) 32);
        priceItem->setFlags((Qt::ItemFlags) 32);

        this->ui->goodsTable->insertRow(i);
        this->ui->goodsTable->setItem(i, 0, idItem);
        this->ui->goodsTable->setItem(i, 1, nameItem);
        this->ui->goodsTable->setItem(i, 2, priceItem);
    }
}

void ShoperWindow::on_deleteGoodsButton_clicked()
{
    int row = this->ui->goodsTable->currentRow();
    if(row < 0) return;

    QMessageBox::StandardButton ret = QMessageBox::warning(
                this,
                "Confirm",
                "Deleting the goods will change supply chain, are you sure to delete?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes);
    if(ret == QMessageBox::No) return;

    string goodID = this->ui->goodsTable->item(row, 0)->text().toStdString();
    GoodRepo::deleteByID(goodID);

    // Update supply chain.
    vector<Supplier*>* suppliers = SupplierRepo::findByGoodID(goodID);
    if(suppliers != NULL) {
        for(int i = 0;i < (int)suppliers->size();i++) {
            Supplier* supplier = suppliers->at(i);
            supplier->deleteGoodByGoodID(goodID);
            SupplierRepo::deleteByID(supplier->id);
            SupplierRepo::saveSupplier(supplier);
            delete supplier;
        }
        delete suppliers;
    }

    this->showAllGoods();
    this->showSuppliers();
}


void ShoperWindow::on_updateGoodsButton_clicked()
{
    int row = this->ui->goodsTable->currentRow();
    if(row < 0) return;

    QString name = this->ui->goodsNameInput->text();
    QString price = this->ui->goodsPriceInput->text();
    if(name == "" || price == "") return;

    string id = this->ui->goodsTable->item(row, 0)->text().toStdString();
    Good* good = new Good(id,
                          name.toStdString(),
                          price.toDouble());
    GoodRepo::deleteByID(good->id);
    GoodRepo::saveGood(good);
    delete good;

    this->ui->goodsIDInput->setText("");
    this->ui->goodsNameInput->setText("");
    this->ui->goodsPriceInput->setText("");
    this->showAllGoods();
}

void ShoperWindow::on_goodsTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    if(row < 0) return;

    QString id = this->ui->goodsTable->item(row, 0)->text();
    QString name = this->ui->goodsTable->item(row, 1)->text();
    QString price = this->ui->goodsTable->item(row, 2)->text();

    this->ui->goodsIDInput->setText(id);
    this->ui->goodsNameInput->setText(name);
    this->ui->goodsPriceInput->setText(price);
}


void ShoperWindow::on_clearButton_clicked()
{
    this->ui->goodsIDInput->setText("");
    this->ui->goodsNameInput->setText("");
    this->ui->goodsPriceInput->setText("");
}
