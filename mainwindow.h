#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QLabel>
#include <QSqlQuery>
#include <QSettings>

#include "addandedit.h"
#include "thescript.h"
#include "database.h"
#include "createnewdb.h"
#include "chosedatabase.h"
#include "QModelIndex"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fillTable();
    void loadSettings();
    void saveSettings();

public slots:
    void slotCreateDB(QString DBPath);
    void slotRefreshTable();
    void openViewScript(QTableWidgetItem *item);

private slots:
    void createNewDB();
    void chooseNewDB();
    void on_addScript_clicked();
    void on_editScript_clicked();
    void on_deleteScript_clicked();

private:
    Ui::MainWindow *ui;
    TheScript* script;   
    Database database;
    AddAndEdit* addAndEdit = new AddAndEdit(this, &database);
    CreateNewDB* createDb = new CreateNewDB(this);
    ChoseDataBase* chooseDB = new ChoseDataBase(this);
    QSettings* settings = new QSettings("RT","TestingApp");


};
#endif // MAINWINDOW_H
