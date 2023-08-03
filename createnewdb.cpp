#include "createnewdb.h"
#include "ui_createnewdb.h"

CreateNewDB::CreateNewDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewDB)
{
    ui->setupUi(this);
}

CreateNewDB::~CreateNewDB()
{
    delete ui;
}

void CreateNewDB::on_choosePath_clicked()
{
    path = QFileDialog::getExistingDirectory(this, tr("Выбрать папку"),
                                             "",
                                             QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->newPath->setText(path);
}


void CreateNewDB::on_buttonBox_accepted()
{
    emit signalCreateDB(path + "/" + ui->DBName->text() + ".sqlite");
}

