#ifndef CHOSEDATABASE_H
#define CHOSEDATABASE_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class ChoseDataBase;
}

class ChoseDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit ChoseDataBase(QWidget *parent = nullptr);
    ~ChoseDataBase();

signals:
    void signalChooseDB(QString);

private slots:
    void on_toolButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::ChoseDataBase *ui;
};

#endif // CHOSEDATABASE_H
