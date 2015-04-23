#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include "dendydebugger.h"
#include "dendymemory.h"
#include "dendycpu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DendyDebugger *dDebugger = NULL;
    QFile* nesFile = NULL; // .nes file
    DendyMemory* memory = NULL;
    DendyCPU* cpu = NULL;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dendyDebuggerButton_clicked();

    void on_openFileNes_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
