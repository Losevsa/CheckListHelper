#include "thescript.h"
#include "ui_thescript.h"

TheScript::TheScript(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheScript)
{
    ui->setupUi(this);
}

TheScript::~TheScript()
{
    delete ui;
}
