#include "addstep.h"
#include "ui_addstep.h"

addStep::addStep(QWidget *parent, QTableWidget* table, bool edit) :
    QDialog(parent),
    ui(new Ui::addStep)
{
    ui->setupUi(this);
    this->table = table;
    this->edit = edit;

    if(edit)
    {
        QTableWidgetItem* itemStepName = table->item(table->currentRow(), 0);
        ui->lineEdit->setText(itemStepName->text());
    }
}

addStep::~addStep()
{
    delete ui;
}

void addStep::on_buttonBox_accepted()
{
    if (!edit)
    {
        int currentCoutRows = table->rowCount();
        table->setRowCount(currentCoutRows + 1);

        QTableWidgetItem* item = new QTableWidgetItem(ui->lineEdit->text());
        table->setItem(currentCoutRows, 0, item);


        table->setItem(currentCoutRows, 1, new QTableWidgetItem(QIcon(":/OK/Icon/image.png"), ""));
    }
    else
    {
        QTableWidgetItem* itemStepName = table->item(table->currentRow(), 0);
        QTableWidgetItem* itemScreenshot = table->item(table->currentRow(), 1);

        itemStepName->setText(ui->lineEdit->text());

    }
}

