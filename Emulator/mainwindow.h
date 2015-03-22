#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dendydebugger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DendyDebugger *dDebugger;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dendyDebuggerButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
