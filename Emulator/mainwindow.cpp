#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->dendyDebuggerButton->setEnabled (false);
    this->ui->console->setCurrentIndex (0);
}

MainWindow::~MainWindow()
{
    if (this->dDebugger){
        delete this->dDebugger;
    }
    
    if (this->nesFile && this->nesFile->isOpen ()){
        this->nesFile->close ();        
        delete this->nesFile;
    }
    
    if (this->memory){
        delete this->memory;
    }
    
    if (this->memory){
        delete this->cpu;
    }
    
    delete ui;
}

// opening dendy debugger
void MainWindow::on_dendyDebuggerButton_clicked(){
    if (!this->dDebugger){
        this->dDebugger = new DendyDebugger(this->cpu, this->memory);
    }
    this->dDebugger->exec ();
}

void MainWindow::on_openFileNes_clicked(){    
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
            delete this->dDebugger;
            this->dDebugger = NULL;
        }
        
        delete this->nesFile;
    }
    
    this->nesFile = new QFile(nesFileName);
    if (!this->nesFile->open (QIODevice::ReadOnly)){
        std::cout << "Error in opening file " << nesFileName.toStdString ();
        return;
    }
    
    this->ui->dendyDebuggerButton->setEnabled (true);
    
    /////////////////////////////////////////////////
    ////////// delete this after debugging //////////
    /////////////////////////////////////////////////
    
    if (!this->memory){
        delete this->memory;
    }
    this->memory = new DendyMemory(this->nesFile);
    
    if (!this->cpu){
        delete this->cpu;
    }
    this->cpu = new DendyCPU(this->memory);
}
