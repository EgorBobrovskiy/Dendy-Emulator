#ifndef DENDYDEBUGGER_H
#define DENDYDEBUGGER_H

#include <QDialog>
#include <QFile>

namespace Ui {
class DendyDebugger;
}

class DendyDebugger : public QDialog
{
    Q_OBJECT

public:
    explicit DendyDebugger(QWidget *parent = 0);
    explicit DendyDebugger(QFile* nesFile, QWidget *parent = 0);
    ~DendyDebugger();
    

private:
    Ui::DendyDebugger *ui;
    QFile* nesFile;
    
    void toHexString(char* dest, char num, int size);
};

#endif // DENDYDEBUGGER_H
