#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete this->dDebugger;
    delete ui;
    if (this->nesFile->isOpen ()){
        this->nesFile->close ();
    }
    delete this->nesFile;
}

// opening dendy debugger
void MainWindow::on_dendyDebuggerButton_clicked()
{
    this->dDebugger = new DendyDebugger(this->nesFile);
    this->dDebugger->open ();
}

void MainWindow::on_openFileNes_clicked()
{    
    QFileDialog dialog(this);
    dialog.setViewMode (QFileDialog::Detail);
    dialog.setNameFilter (tr("ROM file(*.nes)"));
    
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles ();
    }
    
    QString nesFileName = fileNames.first ();
    
    if (this->nesFile){
        if (this->nesFile->isOpen ()){
            this->nesFile->close ();
        }
        
        delete this->nesFile;
    }
    
    this->nesFile = new QFile(nesFileName);
    if (!this->nesFile->open (QIODevice::ReadOnly)){
        std::cout << "Error in opening file " << nesFileName.toStdString ();
    }
    
    /////////////////////////////////////////////////
    ////////// delete this after debugging //////////
    /////////////////////////////////////////////////
    
    if (!this->memory){
        delete this->memory;
    }
    this->memory = new DendyMemory(this->nesFile);
}
