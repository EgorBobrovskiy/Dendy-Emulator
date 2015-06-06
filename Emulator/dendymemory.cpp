#include "dendymemory.h"

DendyMemory::DendyMemory(QFile *nesFile) {
    this->RAM = new uchar[0x800];
    this->WRAM = new uchar[0x2000];
    std::memset(this->RAM, 0, 0x800);
    std::memset(this->WRAM, 0, 0x2000);
    
    this->nesFile = nesFile;
    QByteArray byteArray;
    
    if (this->nesFile->isOpen ()){
        byteArray = this->nesFile->readAll ();
    }
    
    this->numberOfPages = byteArray.at (4);
    this->pages = new uchar*[this->numberOfPages];
    
    // ���������� ������� ������
    int offset; // �������� �������� ������������ ������ �����
    for (int i = 0; i < this->numberOfPages; i++){
        (*(this->pages + i)) = new uchar[0x4000];
        offset = i * 0x4000 + 16;
        
        for (int j = 0; j < 0x4000; j++){
            *(*(this->pages + i) + j) = (byteArray.at (offset + j));
        }
    }
    
    // ���������� ������� ���������������    
    short numberOfSign = byteArray.at (5);
    QByteArray** signGeneratorData = new QByteArray*[numberOfSign];
    
    for (int i = 0; i < numberOfSign; i++){        
        (*(signGeneratorData + i)) = new QByteArray();
        (*(signGeneratorData + i))->reserve (0x2000);
        offset = this->numberOfPages * 0x4000 + i * 0x2000 + 16;
        
        for (int j = 0; j < 0x2000; j++){
            (*(signGeneratorData + i))->append (byteArray.at (offset + j));
        }
    }
    
    // ������������� �����������
    this->vRAM = new DendyVRAM(signGeneratorData, numberOfSign);
    
    this->ROM = *(this->pages + this->numberOfPages - 1); // ��������� ��������
    this->sROM = *(this->pages);// ������ �������� � ������������� ����� ���
}

DendyMemory::~DendyMemory() {    
    for (int i = 0; i < this->numberOfPages; i++) {
        delete *(this->pages + i);
    }
    delete[] this->pages;
    
    delete this->RAM;
    delete this->WRAM;
    
    delete this->vRAM;
}

void DendyMemory::writeMemory (unsigned short adress, unsigned char value){
    
    switch (adress>>13) {
    /* ������ �� ���������� ��� */
    case 0:
        *(this->RAM + (adress & 0x07FF)) = value;
        break;
        
    /* ������ � ��� ��������� */
    case 3:
        *(this->WRAM + (adress & 0x1FFF)) = value;
        break;
        
    /* ������ � �������� ��������������� */
    case 1:
//            this->cpu.videoRegisters->remove (adress & 0x0007, 1);
//            this->cpu.videoRegisters->insert (adress & 0x0007, value);
        break;
        
    /* ������ � �������� ��������� ����������, ����������� ��� � �����/������ */
    case 2:
//            this->cpu.ctrlRegisters->remove (0x001F, 1);
//            this->cpu.ctrlRegisters->insert (0x001F, value);
        break;
        
    /* ������ � ������������� ���� ��� ��������� */
    case 4:
    case 5:
        *(this->sROM + (adress & 0x3FFF)) = value;
        break;
        
    /* ������ � ��������������� ���� ��� ��������� */
    case 6:
    case 7:
        *(this->ROM + (adress & 0x3FFF)) = value;
    }
}

unsigned char DendyMemory::readMemory (unsigned short adress){
    
    switch (adress>>13) {
    /* ������ �� ����������� ��� ��������� */
    case 0:
        return *(this->RAM + (adress & 0x07FF));
        
    /* ������ �� ��� ��������� */
    case 3:
        return *(this->WRAM + (adress & 0x1FFF));
        
    /* ������ ��������� ��������������� */
    case 1:
        return 0x00;
        //return this->cpu.videoRegisters->at (adress & 0x0007);
    
    /* ������ ��������� ��������� ����������, ����������� ��� � �����/������ */            
    case 2:
//        if (adress >= 0x4000 && adress <= 0x4016){
//            return this->cpu.ctrlRegisters->at (adress & 0x001F);
//        }
        return 0x00;
        
    /* ������ �� �������������� ����� ��� ��������� */
    case 4:
    case 5:
        return *(this->sROM + (adress & 0x3FFF));
        
    /* ������ �� ���������������� ����� ��� ��������� */
    case 6:
    case 7:
        return *(this->ROM + (adress & 0x3FFF));
    }
    
    return 0;
}

uchar *DendyMemory::getRAM(){
    return this->RAM;
}

uchar** DendyMemory::getPages (){
    return this->pages;
}

uchar* DendyMemory::getROM (){
    return this->ROM;
}

uchar* DendyMemory::getSROM (){
    return this->sROM;
}

uchar* DendyMemory::getWRAM (){
    return this->WRAM;
}
