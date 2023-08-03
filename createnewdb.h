#ifndef CREATENEWDB_H
#define CREATENEWDB_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class CreateNewDB;
}

class CreateNewDB : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewDB(QWidget *parent = nullptr);
    ~CreateNewDB();

signals:
    void signalCreateDB(QString);

private slots:
    void on_choosePath_clicked();
    void on_buttonBox_accepted();

private:
    Ui::CreateNewDB *ui;
    QString path = "";
};

#endif // CREATENEWDB_H
