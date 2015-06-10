#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->dendyDebuggerButton->setEnabled (false);
    this->ui->console->setCurrentIndex (0);
    this->timer = new QTimer(this);
    QObject::connect (this->timer, SIGNAL(timeout()), this, SLOT(dendyUpdate()));
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
    
    if (this->timer) {
        this->timer->stop ();
        delete this->timer;
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
        QObject::connect (this, SIGNAL(synchSignal(QGraphicsPixmapItem*)), this->dendy, SLOT(getFrame (QGraphicsPixmapItem*)));
        this->dendyRun ();
    }
}

void MainWindow::dendyRun (){
    // выполнять обновление экрана
    // полученным кадром
    this->dendyGraphics = new QGraphicsScene(0, 0, 512, 480);
    this->pixmap = this->dendyGraphics->addPixmap (QPixmap(512, 480));
    this->ui->dendyOutput->setScene (this->dendyGraphics);
    this->timer->start (TIMER_STEP);
}

void MainWindow::dendyUpdate (){
    emit synchSignal (this->pixmap);
    this->dendyGraphics->update (0, 0, 512, 480);
}

void MainWindow::keyPressEvent (QKeyEvent *keyEvent) {
    if (this->dendy) {
        switch (keyEvent->key ()) {
                    
            // UP
        case Qt::Key_Up:
            this->dendy->setKeyState (4, true);
            break;
            
            // LEFT
        case Qt::Key_Left:
            this->dendy->setKeyState (6, true);
            break;
            
            // DOWN
        case Qt::Key_Down:
            this->dendy->setKeyState (5, true);
            break;
            
            // RIGHT
        case Qt::Key_Right:
            this->dendy->setKeyState (7, true);
            break;
            
            // START
        case Qt::Key_Enter:
            this->dendy->setKeyState (3, true);
            break;
            
            // SELECT
        case Qt::Key_Tab:
            this->dendy->setKeyState (2, true);
            break;
            
            // B
        case Qt::Key_Control:
            this->dendy->setKeyState (1, true);
            break;
            
            // A
        case Qt::Key_Alt:
            this->dendy->setKeyState (0, true);
            break;
        }
    }
}

void MainWindow::keyReleaseEvent (QKeyEvent *keyEvent) {
    if (this->dendy) {
        switch (keyEvent->key ()) {
            // pause game
        case Qt::Key_Escape:
            if (this->timer->isActive ()) {
                this->timer->stop ();
            } else {
                this->timer->start (TIMER_STEP);
            }
            break;
            
            // UP
        case Qt::Key_Up:
            this->dendy->setKeyState (4, false);
            break;
            
            // LEFT
        case Qt::Key_Left:
            this->dendy->setKeyState (6, false);
            break;
            
            // DOWN
        case Qt::Key_Down:
            this->dendy->setKeyState (5, false);
            break;
            
            // RIGHT
        case Qt::Key_Right:
            this->dendy->setKeyState (7, false);
            break;
            
            // START
        case Qt::Key_Enter:
            this->dendy->setKeyState (3, false);
            break;
            
            // SELECT
        case Qt::Key_Tab:
            this->dendy->setKeyState (2, false);
            break;
            
            // B
        case Qt::Key_Control:
            this->dendy->setKeyState (1, false);
            break;
            
            // A
        case Qt::Key_Alt:
            this->dendy->setKeyState (0, false);
            break;
        }
    }
}
