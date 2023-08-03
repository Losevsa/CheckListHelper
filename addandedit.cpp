#include "addandedit.h"
#include "ui_addandedit.h"

AddAndEdit::AddAndEdit(QWidget *parent, Database* database ) :
    QMainWindow(parent),
    ui(new Ui::AddAndEdit)
{
    ui->setupUi(this);
    this->database = database;

    ui->stepTable->setColumnCount(2);
    ui->stepTable->setColumnWidth(0,400);
    //ui->mainTable->resizeColumnsToContents();
    QTableWidgetItem* scriptName = new QTableWidgetItem("Шаг");
    ui->stepTable->setHorizontalHeaderItem(0,scriptName);
    QTableWidgetItem* status = new QTableWidgetItem("Фото");
    ui->stepTable->setHorizontalHeaderItem(1,status);
}

AddAndEdit::~AddAndEdit()
{
    //delete addNewStep;
    delete ui;
}

void AddAndEdit::fillStruct(QSqlQuery queryName, QSqlQuery querySteps)
{
    editMode = true;

    structName.clearName();
    backupSteps.clear();

    queryName.next();
    querySteps.next();

    ui->scriptName->setText(queryName.value(0).toString());
    ui->result->setText(queryName.value(2).toString());

    ui->stepTable->clear();

    int row = 0;
    ui->stepTable->setRowCount(row);

    structName.name = queryName.value(0).toString();
    structName.screenshot = queryName.value(1).toString();
    structName.expectResult = queryName.value(2).toString();
    structName.Result = queryName.value(3).toString();
    structName.status = queryName.value(4).toBool();

    //сделать через while - querySteps.size() - возвращает не то значение

    while (true)
    {
        if(!querySteps.isValid())
        {
            qDebug() << "Null";
            break;
        }

        ui->stepTable->setRowCount(row + 1);

        QTableWidgetItem* item = new QTableWidgetItem(querySteps.value(1).toString());
        ui->stepTable->setItem(row, 0, item);

        ui->stepTable->setItem(row, 1, new QTableWidgetItem(QIcon(":/OK/Icon/image.png"), ""));
        row++;

        StructStep structStep;
        structStep.name = querySteps.value(0).toString();
        structStep.step = querySteps.value(1).toString();
        structStep.screenshot = querySteps.value(2).toString();
        structStep.stepId= querySteps.value(0).toBool();

        backupSteps.push_back(structStep);

        querySteps.next();
    }
}

void AddAndEdit::clearGui()
{
    ui->scriptName->clear();
    ui->stepTable->clear();
    ui->stepTable->setRowCount(0);
    ui->result->clear();
}

void AddAndEdit::on_addStep_clicked()
{
    addNewStep = new addStep(this, ui->stepTable, false);
    addNewStep->show();
}


void AddAndEdit::on_toolButton_accepted()
{
    if(!editMode)
    {
        if (ui->scriptName->text() != "")
        {
            QString script = "INSERT INTO ScriptName ("
                             "Name,"
                             "Screenshot,"
                             "ExpectResult,"
                             "Result,"
                             "Status)"
                             "VALUES ("
                             "'";
            script+= ui->scriptName->text() + "','','" + ui->result->toPlainText() + "','','false');";

            database->doQuery(script);

            for (int i = 0; i < ui->stepTable->rowCount(); i++)
            {
                QString steps =  "INSERT INTO Steps ("
                                "Name,"
                                "Step,"
                                "Screenshot,"
                                "Stepid"
                                ")"
                                "VALUES ("
                                "'";
                steps+= ui->scriptName->text() + "','" + ui->stepTable->item(i,0)->text() + "','','" + QString::number(i) + "');";

                database->doQuery(steps);
            }
            emit signalRefreshMainTable();
            ui->stepTable->clear();
            ui->stepTable->setRowCount(0);
            ui->scriptName->clear();
            ui->result->clear();
            this->close();
        }
        else
        {
            ui->statusbar->showMessage("Добавьте название задачи");
        }
    }
    else
    {
        if (ui->scriptName->text() != "")
        {
            QString script = "UPDATE ScriptName "
                             "SET Name = '" + ui->scriptName->text() + "',"
                             "Screenshot = 'Screenshot',"
                             "ExpectResult = '" + ui->result->toPlainText() + "',"
                             "Result = 'Result',"
                             "Status = 'Status'"
                             "WHERE "
                             "Name = '" + structName.name + "';";
            qDebug() << script;

            database->doQuery(script);

            database->doQuery("DELETE FROM Steps WHERE Name = '" + structName.name + "';");

            for (int i = 0; i < ui->stepTable->rowCount(); i++)
            {
                QString steps =  "INSERT INTO Steps ("
                                "Name,"
                                "Step,"
                                "Screenshot,"
                                "Stepid"
                                ")"
                                "VALUES ("
                                "'";
                steps+= ui->scriptName->text() + "','" + ui->stepTable->item(i,0)->text() + "','','" + QString::number(i) + "');";

                database->doQuery(steps);
            }

            editMode = false;
            emit signalRefreshMainTable();
            this->close();
        }
        else
        {
            ui->statusbar->showMessage("Добавьте название задачи");
        }
    }
}


void AddAndEdit::on_deleteStep_clicked()
{
    //QTableWidgetItem* item = ui->stepTable->item(ui->stepTable->currentRow(), 0);
    ui->stepTable->removeRow(ui->stepTable->currentRow());
}


void AddAndEdit::on_editStep_clicked()
{
    addNewStep = new addStep(this, ui->stepTable, true);
    addNewStep->show();
}

