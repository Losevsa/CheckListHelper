#ifndef ADDANDEDIT_H
#define ADDANDEDIT_H

#include <QMainWindow>
#include <QVector>

#include "addstep.h"
#include "database.h"

struct StructStep
{
    QString name;
    QString step;
    QString screenshot;
    int stepId;

};

struct StructName
{
    QString name;
    QString screenshot;
    QString expectResult;
    QString Result;
    bool status;

    void clearName()
    {
        name = "";
        screenshot = "";
        expectResult = "";
        Result = "";
        status = false;
    }
};

namespace Ui {
class AddAndEdit;
}

class AddAndEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddAndEdit(QWidget *parent = nullptr, Database* database = nullptr);
    ~AddAndEdit();

    void fillStruct(QSqlQuery queryName, QSqlQuery querySteps);
    void clearGui();

signals:
    void signalRefreshMainTable();

private slots:
    void on_addStep_clicked();
    void on_toolButton_accepted();
    void on_deleteStep_clicked();
    void on_editStep_clicked();

private:
    Ui::AddAndEdit *ui;
    addStep* addNewStep;
    Database* database;
    bool editMode = false;
    QVector<StructStep> backupSteps;
    StructName structName;
};

#endif // ADDANDEDIT_H
