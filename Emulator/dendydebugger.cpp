#include "dendydebugger.h"
#include "ui_dendydebugger.h"

DendyDebugger::DendyDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendyDebugger)
{
    ui->setupUi(this);
}

DendyDebugger::DendyDebugger(QFile* nesFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendyDebugger)
{
    ui->setupUi(this);
    this->nesFile = nesFile;
    
    QByteArray byteArray;
    
    if (this->nesFile->isOpen ()){
        // reading .nes file and show it containment
        QString row = "800x:\t";
        char* temp = new char[3];
        
        byteArray = this->nesFile->readAll ();        
        
        for (int i = 16, rowNum = 0x801; i < byteArray.size (); i++){
//            toHexString (temp, byteArray.at (i));
            toHexString (temp, byteArray.at (i), 2);
            row += QString::fromUtf8 (temp, 2) + " ";
            
            if(i%16 == 15){
                this->ui->memoryView->addItem (row);
                sprintf(temp, "%X", rowNum++);
                row = QString::fromUtf8 (temp, 3) + "x:\t";
            }
        }
        
        row = "";
    }
}

DendyDebugger::~DendyDebugger()
{
    delete ui;
    this->nesFile = NULL;
    delete this->nesFile;
}

/* dest is ptr to char* array; num is hex number to convert; size is size of dest*/
void DendyDebugger::toHexString (char *dest, char num, int size){
    size--;
    
    if (dest == NULL || size < 0){
        return;
    }
    
    int temp = num%16;
    temp = (temp < 0) ? (0x10 + temp) : temp;
    
    if (temp < 10){
        dest[size] = temp + '0';
    } else {
        dest[size] = temp - 10 + 'A';
    }
    
    DendyDebugger::toHexString (dest, num>>4, size);
}
