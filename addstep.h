#ifndef ADDSTEP_H
#define ADDSTEP_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class addStep;
}

class addStep : public QDialog
{
    Q_OBJECT

public:
    explicit addStep(QWidget *parent = nullptr, QTableWidget* table = nullptr, bool edit = false);

    ~addStep();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addStep *ui;
    QTableWidget* table;
    bool edit;
};

#endif // ADDSTEP_H
