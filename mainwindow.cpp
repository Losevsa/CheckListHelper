#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    if (database.connectDB(0,""))
    {
        ui->statusbar->showMessage("База подключена");
    }
    else
    {
        ui->statusbar->showMessage("Нет базы данных, выберите базу данных в меню БД");
    }

    connect(ui->createNewDatabase, SIGNAL(triggered(bool)), this, SLOT(createNewDB()));
    connect(ui->choseDatabase, SIGNAL(triggered(bool)), this, SLOT(chooseNewDB()));

    connect(createDb, &CreateNewDB::signalCreateDB, this, &MainWindow::slotCreateDB);
    connect(chooseDB, &ChoseDataBase::signalChooseDB, this, &MainWindow::slotCreateDB);
    connect(addAndEdit, &AddAndEdit::signalRefreshMainTable, this, &MainWindow::slotRefreshTable);

    connect(ui->mainTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(openViewScript(QTableWidgetItem*)));

    fillTable();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete addAndEdit;
    //delete script;
    delete ui;
}

void MainWindow::fillTable()
{
    ui->mainTable->clear();
    ui->mainTable->setRowCount(0);

    ui->mainTable->setColumnCount(2);
    ui->mainTable->setColumnWidth(0,450);
    //ui->mainTable->resizeColumnsToContents();
    QTableWidgetItem* scriptName = new QTableWidgetItem("Сценарий");
    ui->mainTable->setHorizontalHeaderItem(0,scriptName);
    QTableWidgetItem* status = new QTableWidgetItem("Статус");
    ui->mainTable->setHorizontalHeaderItem(1,status);

    QString request = "SELECT * FROM 'ScriptName';";

    QSqlQuery sqlRequest = database.getRequest(request);
    sqlRequest.next();

    //qDebug() << sqlRequest.value(0).toString();


    //ui->mainTable->insertRow(0);

    for (int rowCount = -1; rowCount < ui->mainTable->rowCount(); rowCount++)
    {
        if (sqlRequest.value(0).toString() != "")
        {
            ui->mainTable->insertRow(rowCount + 1);
            //table->setItem(currentCoutRows, 1, new QTableWidgetItem(QIcon(":/OK/Icon/image.png"), ""));
            ui->mainTable->setItem(rowCount + 1, 0, new QTableWidgetItem(sqlRequest.value(0).toString()));

            if (sqlRequest.value(5).toBool())
            {
                ui->mainTable->setItem(rowCount + 1, 1, new QTableWidgetItem("Проверено"));
            }
            else
            {
                ui->mainTable->setItem(rowCount + 1, 1, new QTableWidgetItem("Ожидает проверки"));
            }
        }
        sqlRequest.next();
    }
}

void MainWindow::loadSettings()
{
    database.setDBPath(settings->value("database/dbpath").toString());
    qDebug() << settings->value("database/dbpath").toString();
    //database.connectDB(0, settings->value("database/dbpath").toString());
}

void MainWindow::saveSettings()
{
    settings->setValue("database/dbpath", database.getDBPath());
    qDebug() << database.getDBPath();
}

void MainWindow::slotCreateDB(QString DBPath)
{
    qDebug() << "DBPath: " + DBPath;

    if(database.connectDB(1,DBPath))
    {
        ui->statusbar->showMessage("База подключена");
        fillTable();
    }
    else
    {
        ui->statusbar->showMessage("Проблемы с базой данных");
    }
}

void MainWindow::slotRefreshTable()
{
    fillTable();
}

void MainWindow::openViewScript(QTableWidgetItem *item)
{
    qDebug() << "Test1";
}

void MainWindow::createNewDB()
{
    createDb->show();
}

void MainWindow::chooseNewDB()
{
    chooseDB->show();
}

void MainWindow::on_addScript_clicked()
{
    addAndEdit->clearGui();
    addAndEdit->show();
}


void MainWindow::on_editScript_clicked()
{
    if (!ui->mainTable->selectedItems().isEmpty())
    {
        QTableWidgetItem* item = ui->mainTable->item(ui->mainTable->currentRow(), 0);
        QString queryName = "SELECT * FROM 'ScriptName' WHERE Name = '" + item->text() + "';";
        QString querySteps = "SELECT * FROM 'Steps' WHERE Name = '" + item->text() + "';";

        //qDebug() << "SELECT * FROM 'Steps' WHERE Name = '" + item->text() + "';";

        addAndEdit->fillStruct(database.getRequest(queryName), database.getRequest(querySteps));
        addAndEdit->show();
    }

}

void MainWindow::on_deleteScript_clicked()
{
    QTableWidgetItem* item = ui->mainTable->item(ui->mainTable->currentRow(), ui->mainTable->currentColumn());

    if(item)
    {
        QString deleteQuery = "DELETE FROM 'ScriptName' "
                              "WHERE Name = '"
                              + item->text() + ""
                                               "';";

        database.doQuery(deleteQuery);

        deleteQuery = "DELETE FROM 'Steps' "
                      "WHERE Name = '"
                      + item->text() + ""
                                       "';";

        database.doQuery(deleteQuery);
        fillTable();
    }
}

