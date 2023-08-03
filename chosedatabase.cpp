#include "chosedatabase.h"
#include "ui_chosedatabase.h"

ChoseDataBase::ChoseDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoseDataBase)
{
    ui->setupUi(this);
}

ChoseDataBase::~ChoseDataBase()
{
    delete ui;
}

void ChoseDataBase::on_toolButton_clicked()
{
    ui->newBD->setText(QFileDialog::getOpenFileName(0, "БД *.sqlite", "", "*.sqlite"));
}


void ChoseDataBase::on_buttonBox_accepted()
{
    qDebug() << "ChooseDataBase: " +  ui->newBD->text();
    emit signalChooseDB(ui->newBD->text());
}

