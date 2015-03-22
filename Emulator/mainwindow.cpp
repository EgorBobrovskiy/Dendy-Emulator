#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dDebugger = new DendyDebugger();
}

MainWindow::~MainWindow()
{
    delete dDebugger;
    delete ui;
}

// opening dendy debugger
void MainWindow::on_dendyDebuggerButton_clicked()
{
    dDebugger->open ();
}
