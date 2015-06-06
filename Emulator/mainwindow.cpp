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
    
    if (this->nesFile){      
        delete this->nesFile;
    }
    
    if (this->dendy){
        delete this->dendy;
    }
    
    delete ui;
}

// открытие отладчика
void MainWindow::on_dendyDebuggerButton_clicked(){
    if (!this->dDebugger){
        this->dDebugger = new DendyDebugger(this->dendy);
    }
    this->dDebugger->exec ();
}

// выбор и открытие файла
void MainWindow::on_openFileNes_clicked(){    
    QFileDialog dialog(this);
    dialog.setViewMode (QFileDialog::Detail);
    dialog.setNameFilter (tr("ROM file(*.nes)"));
    
    QStringList fileNames;
    if (dialog.exec()){        
        fileNames = dialog.selectedFiles ();
        
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
        
        if (!this->dendy){
            delete this->dendy;
        }
        this->dendy = new Dendy(this->nesFile);
    }
}

void MainWindow::dendyRun (){
    // выполнять обновление экрана
    // полученным кадром
    
//    while (1){
//        this->dendy->getFrame ();
//    }
}
