#include "dendymemory.h"

DendyMemory::DendyMemory(QFile *nesFile) {
    for (uchar i = 0; i < 8; i++) {
        this->keyPressed[i] = false;
    }
    this->previous4016 = 0;
    this->register4016 = 0x00;
    this->register4017 = 0x00;
    
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
        *(this->pages + i) = new uchar[0x4000];
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
    this->vRAM = new DendyVRAM(signGeneratorData, numberOfSign, byteArray.at (6) & 0x01);
    
    this->ROM = *(this->pages + this->numberOfPages - 1); // ��������� ��������
    this->sROM = *(this->pages);// ������ �������� � ������������� ����� ���
}

DendyMemory::~DendyMemory() {    
    for (int i = 0; i < this->numberOfPages; i++) {
        delete[] *(this->pages + i);
    }
    delete[] this->pages;
    
    delete[] this->RAM;
    delete[] this->WRAM;
    
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
        this->vRAM->writeReg (adress & 0x0007, value);
        break;
        
    /* ������ � �������� ��������� ����������, ����������� ��� � �����/������ */
    case 2:
        if (adress == 0x4014) {
            //���������� ���
            this->writeDMA (adress);
        }
        break;
        
        // ������ � ������� ���������� ��������
        // (��������� ��� ������)
        if (adress == 0x4016) {
            // ���� ��� ������ ������������� ������� ��� �������� 
            // ��������� ������
            if ((previous4016 & 0x01) == 0x01 && (value & 0x01) == 0x00) {
                this->fixKeyState ();
            }
            previous4016 = value;
        }
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
        return this->vRAM->readReg (adress & 0x0007);
    
    /* ������ ��������� ��������� ����������, ����������� ��� � �����/������ */            
    case 2:
        // ������ ��������� 1 ������
        if (adress == 0x4016) {
            // ����� �� �����, ���� �� ��������
            this->register4016 = this->joy1 & 0x01;
            this->register4016 |= 0xF6;
            this->joy1 = this->joy1 >> 1;
            return this->register4016;
        }
        
        // ������ ��������� 2 ������
        if (adress == 0x4017) {
            // ����� �� �����, ���� �� ��������
            this->register4017 = this->joy2 & 0x01;
            this->register4017 |= 0xF6;
            this->joy2 = this->joy2 >> 1;
            return this->register4017;
        }
        
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

DendyVRAM* DendyMemory::getDendyVRAM () {
    return this->vRAM;
}

void DendyMemory::writeDMA (ushort adress){
    uchar data[0x100];
    adress = adress << 8;
    
    for (ushort i = 0; i < 0x100; i++) {
        data[i] = this->readMemory (adress + i);
    }
    
    this->vRAM->writeInSpriteMemory (data);
}

void DendyMemory::setKeyState (uchar number, bool state) {
    if (number < 8) {
        this->keyPressed[number] = state;
    }
}

void DendyMemory::fixKeyState () {
    this->joy1 = 0x00;
    this->joy2 = 0x00;
    
    uchar temp = 0x01;
    for (uchar i = 0; i < 8; i++){
        if (this->keyPressed[i]) joy1 |= temp;
        temp = temp << 1;
    }
    
    this->joy1 ^= 0xFF;
    this->joy2 ^= 0xFF;
}
