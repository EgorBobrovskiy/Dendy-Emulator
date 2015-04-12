#include "dendymemory.h"

DendyMemory::DendyMemory(QFile *nesFile)
{
    this->RAM = new QByteArray(0x800, '\0');
    this->WRAM = new QByteArray(0x2000, '\0');
    
    this->nesFile = nesFile;
    QByteArray byteArray;
    
    if (this->nesFile->isOpen ()){
        byteArray = this->nesFile->readAll ();
    }
    
    this->numberOfPages = byteArray.at (4);
    this->pages = new QByteArray*[this->numberOfPages];
    
    // ���������� ������� ������
    int offset; // �������� �������� ������������ ������ �����
    for (int i = 0; i < this->numberOfPages; i++){
        (*(this->pages + i)) = new QByteArray();
        (*(this->pages + i))->reserve (0x4000);
        offset = i * 0x4000 + 16;
        
        for (int j = 0; j < 0x4000; j++){
            (*(this->pages + i))->append (byteArray.at (offset + j));
        }
    }
    
    // ���������� ������� ���������������    
    this->numberOfSign = byteArray.at (5);
    this->signGeneratorData = new QByteArray*[this->numberOfSign];
    
    for (int i = 0; i < this->numberOfSign; i++){        
        (*(this->signGeneratorData + i)) = new QByteArray();
        (*(this->signGeneratorData + i))->reserve (0x2000);
        offset = this->numberOfPages * 0x4000 + i * 0x2000 + 16;
        
        for (int j = 0; j < 0x2000; j++){
            (*(this->signGeneratorData + i))->append (byteArray.at (offset + j));
        }
    }
    
    this->ROM = *(this->pages + this->numberOfPages - 1); // ��������� ��������
    this->sROM = *(this->pages);// ������ �������� � ������������� ����� ���
}

DendyMemory::~DendyMemory()
{
    delete this->RAM;
    delete this->WRAM;
    
    for (int i = 0; i < this->numberOfPages; i++){
        delete *(this->pages + i);
    }
    
    for (int i = 0; i < this->numberOfSign; i++){
        delete *(this->signGeneratorData);
    }
    
    delete[] this->pages;
    delete[] this->signGeneratorData;
}

void DendyMemory::writeMemory (short adress, char value){
    switch (adress>>13) {
    /* ������ �� ���������� ��� */
    case 0:
        RAM->insert(adress & 0x07FF, value);
        break;
        
    /* ������ � ��� ��������� */
    case 3:
        WRAM->insert(adress & 0x1FFF, value);
        break;
        
    /* ������ � �������� ��������� ���������� ��� ��������������� */
    case 1:
    case 2:
        break;
        
    /* ������ � ������� ����������� ������� ������ � ��������� */
    default:
        break;
    }
}

char DendyMemory::readMemory (short adress){
    switch (adress>>13) {
    /* ������ �� ����������� ��� ��������� */
    case 0:
        return RAM->at (adress & 0x07FF);
        
    /* ������ �� ��� ��������� */
    case 3:
        return WRAM->at(adress & 0x1FFF);
        
    /* ������ �� ����� �����/������ */
    case 1:
    case 2:
        break;
        
    /* ������ �� ��� ��������� */
    default:
        break;
    }
    
    return 0;
}

