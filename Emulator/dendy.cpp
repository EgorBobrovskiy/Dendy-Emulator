#include "dendy.h"
#define FRAME_PERIOD 35468 // ���������� ������ �� ������������ �����

Dendy::Dendy(QFile* nesFile, QObject *parent) : QObject(parent) {
    this->memory = new DendyMemory(nesFile);
    this->cpu = new DendyCPU(this->memory);
    this->ppu = new DendyPPU(this->memory->getDendyVRAM ());
    
    this->period = 0;
}

Dendy::~Dendy(){
    delete this->cpu;
    delete this->memory;
}

void Dendy::getFrame (QGraphicsPixmapItem* pixmap){
    this->period += FRAME_PERIOD;
    
    // ��������� ��������� �� ������������ �����
    do{
        this->period -= this->cpu->stepCPU ();    
    } while (this->period > 0);
    
    // �������� ����
    this->ppu->drawFrame (pixmap);
    
    // ����������� ������������� ����������
    if (this->ppu->isNMIAllowed ()) {
        this->period -= this->cpu->nmiCPU ();
    }
}

DendyCPU* Dendy::getCPU (){
    return this->cpu;
}

DendyMemory* Dendy::getMemory (){
    return this->memory;
}

void Dendy::setKeyState (uchar number, bool state) {
    this->memory->setKeyState (number, state);
}
