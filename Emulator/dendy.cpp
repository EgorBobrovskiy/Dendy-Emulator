#include "dendy.h"
#define FRAME_PERIOD 70938 // ���������� ������ �� ������������ �����

Dendy::Dendy(QFile* nesFile){
    this->memory = new DendyMemory(nesFile);
    this->cpu = new DendyCPU(this->memory);
    
    this->period = 0;
}

Dendy::~Dendy(){
    delete this->cpu;
    delete this->memory;
}

// �������� 
void Dendy::getFrame (){
    this->cpu->resetCPU ();
    this->period += FRAME_PERIOD;
    
    // ��������� ��������� �� ������������ �����
    do{
        this->period -= this->cpu->stepCPU ();    
    } while (this->period > 0);
    
    // �������� ����
    
    // ��������� �������
    
    // ����������� ������������� ����������
    this->period -= this->cpu->nmiCPU ();
}

DendyCPU* Dendy::getCPU (){
    return this->cpu;
}

DendyMemory* Dendy::getMemory (){
    return this->memory;
}

