#ifndef DENDYDEBUGGER_H
#define DENDYDEBUGGER_H

#include <QDialog>

namespace Ui {
class DendyDebugger;
}

class DendyDebugger : public QDialog
{
    Q_OBJECT

public:
    explicit DendyDebugger(QWidget *parent = 0);
    ~DendyDebugger();

private:
    Ui::DendyDebugger *ui;
};

#endif // DENDYDEBUGGER_H
