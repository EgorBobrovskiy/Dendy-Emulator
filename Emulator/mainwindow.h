#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include "dendydebugger.h"
#include "dendy.h"

namespace Ui {
class MainWindow;
}

///
/// \brief The MainWindow class -- главное окно приложения
///

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DendyDebugger *dDebugger = NULL;
    QFile* nesFile = NULL; // .nes file
    Dendy* dendy = NULL;   // dendy console
    
    void dendyRun();

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
