#ifndef THESCRIPT_H
#define THESCRIPT_H

#include <QMainWindow>

namespace Ui {
class TheScript;
}

class TheScript : public QMainWindow
{
    Q_OBJECT

public:
    explicit TheScript(QWidget *parent = nullptr,);
    ~TheScript();

private:
    Ui::TheScript *ui;
};

#endif // THESCRIPT_H
