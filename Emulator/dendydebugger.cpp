#include "dendydebugger.h"
#include "ui_dendydebugger.h"

DendyDebugger::DendyDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendyDebugger)
{
    ui->setupUi(this);
}

//DendyDebugger::DendyDebugger(QFile* nesFile, QWidget *parent) :
DendyDebugger::DendyDebugger(Dendy *dendy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendyDebugger)
{
    ui->setupUi(this);
    this->cpu = dendy->getCPU ();
    this->memory = dendy->getMemory ();
    
    this->initMemoryView ();
    this->initRegisters ();
}

DendyDebugger::~DendyDebugger()
{
    delete ui;
}

void DendyDebugger::showMemoryBlock (QByteArray *block, short startAdress){
    char* temp = new char[3];
    toHexString (temp, startAdress++, 3);
    QString row = QString::fromUtf8 (temp, 3) + "x:\t";
    
    for(int i = 0; i < block->size (); i++){
        toHexString (temp, block->at (i), 2);
        row += QString::fromUtf8 (temp, 2) + " ";
        
        if(i%16 == 15){
            this->ui->memoryView->addItem (row);
            toHexString (temp, startAdress++, 3);
            row = QString::fromUtf8 (temp, 3) + "x:\t";
        }
    }
    
    delete[] temp;
}

/* dest is ptr to char* array; num is hex number to convert; size is size of dest*/
void DendyDebugger::toHexString (char *dest, unsigned short num, int size){
    size--;
    
    if (dest == NULL || size < 0){
        return;
    }
    
    int temp = num%16;
    //temp = (temp < 0) ? (0x10 + temp) : temp;
    
    if (temp < 10){
        dest[size] = temp + '0';
    } else {
        dest[size] = temp - 10 + 'A';
    }
    
    DendyDebugger::toHexString (dest, num>>4, size);
}

// вывод содержимого памяти, находящейся в области видимости процессора
void DendyDebugger::initMemoryView (){
    
// вывод содержимого памяти
        
    // вывод RAM
    this->ui->memoryView->addItem ("RAM:");
    this->showMemoryBlock (this->memory->getRAM (), 0x000);
     
    this->ui->memoryView->addItem ("");
        
    // тут потом вывести регистры видеопроцессора(0x2000 - 0x2007)
    // и (0x4000 - 0x4017)
        
    // вывод WRAM (ОЗУ картриджа)
    this->ui->memoryView->addItem ("WRAM:");
    this->showMemoryBlock (this->memory->getWRAM (), 0x600);
    this->ui->memoryView->addItem ("");
        
    // вывод переключаемого банка ПЗУ картриджа
    this->ui->memoryView->addItem ("Switchable ROM:");
    this->showMemoryBlock (this->memory->getSROM (), 0x800);
    this->ui->memoryView->addItem ("");
        
    // вывод непереключаемого банка ПЗУ картриджа
    this->ui->memoryView->addItem ("Non-switchable ROM:");
    this->showMemoryBlock (this->memory->getROM (), 0xC00);
    this->ui->memoryView->addItem ("");
}

// вывод содержимого всех регистров
void DendyDebugger::initRegisters (){
    char* temp = new char[4];
    
    toHexString (temp, this->cpu->getRegPC (), 4);
    this->ui->pcValue->setText (QString::fromUtf8 (temp, 2) + ":" + QString::fromUtf8 (temp + 2, 2));
    
    toHexString (temp, this->cpu->getRegA (), 2);
    this->ui->aValue->setText (QString::fromUtf8 (temp, 2));
    
    toHexString (temp, this->cpu->getRegP (), 2);
    this->ui->pValue->setText (QString::fromUtf8 (temp, 2));
    
    toHexString (temp, this->cpu->getRegS (), 2);
    this->ui->sValue->setText (QString::fromUtf8 (temp, 2));
    
    toHexString (temp, this->cpu->getRegX (), 2);
    this->ui->xValue->setText (QString::fromUtf8 (temp, 2));
    
    toHexString (temp, this->cpu->getRegY (), 2);
    this->ui->yValue->setText (QString::fromUtf8 (temp, 2));
    
    (this->cpu->getFlagC ()) ? this->ui->C->setCheckState (Qt::Checked) : this->ui->C->setCheckState (Qt::Unchecked);
    (this->cpu->getFlagD ()) ? this->ui->D->setCheckState (Qt::Checked) : this->ui->D->setCheckState (Qt::Unchecked);
    (this->cpu->getFlagI ()) ? this->ui->I->setCheckState (Qt::Checked) : this->ui->I->setCheckState (Qt::Unchecked);
    (this->cpu->getFlagN ()) ? this->ui->N->setCheckState (Qt::Checked) : this->ui->N->setCheckState (Qt::Unchecked);
    (this->cpu->getFlagV ()) ? this->ui->V->setCheckState (Qt::Checked) : this->ui->V->setCheckState (Qt::Unchecked);
    (this->cpu->getFlagZ ()) ? this->ui->Z->setCheckState (Qt::Checked) : this->ui->Z->setCheckState (Qt::Unchecked);
    
    delete[] temp;
}

// обновление состояния регистра P
void DendyDebugger::updateRegP (){
    // set value of reg P in debugger
    char* temp = new char[2];
    toHexString (temp, this->cpu->getRegP (), 2);
    this->ui->pValue->setText (QString::fromUtf8 (temp, 2));
    
    delete[] temp;
}

// при изменении флажков изменить содержимое регистра P
void DendyDebugger::on_C_stateChanged(int state){
    // set flag C
    this->cpu->setFlagC (state == Qt::Checked);
    
    this->updateRegP ();
}

void DendyDebugger::on_Z_stateChanged(int state){
    // set flag Z
    this->cpu->setFlagZ (state == Qt::Checked);
    
    this->updateRegP ();
}

void DendyDebugger::on_I_stateChanged(int state){
    // set flag I
    this->cpu->setFlagI (state == Qt::Checked);
    
    this->updateRegP ();
}

void DendyDebugger::on_D_stateChanged(int state){
    // set flag D
    this->cpu->setFlagD (state == Qt::Checked);
    
    this->updateRegP ();
}

void DendyDebugger::on_V_stateChanged(int state){
    // set flag V
    this->cpu->setFlagV (state == Qt::Checked);
    
    this->updateRegP ();
}

void DendyDebugger::on_N_stateChanged(int state){
    // set flag N
    this->cpu->setFlagN (state == Qt::Checked);
    
    this->updateRegP ();
}

// сброс состояния процессора
void DendyDebugger::on_resetCPU_clicked()
{
    this->cpu->resetCPU ();
    this->initRegisters ();
}

void DendyDebugger::on_B_stateChanged(int state)
{
    // set flag B
    this->cpu->setFlagB (state == Qt::Checked);
    
    this->updateRegP ();
}
