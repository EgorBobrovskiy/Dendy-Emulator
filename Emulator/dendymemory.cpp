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
    
    // заполнение страниц памяти
    int offset; // смещение страницы относительно начала файла
    for (int i = 0; i < this->numberOfPages; i++){
        (*(this->pages + i)) = new QByteArray();
        (*(this->pages + i))->reserve (0x4000);
        offset = i * 0x4000 + 16;
        
        for (int j = 0; j < 0x4000; j++){
            (*(this->pages + i))->append (byteArray.at (offset + j));
        }
    }
    
    // заполнение страниц знакогенератора    
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
    
    this->ROM = *(this->pages + this->numberOfPages - 1); // последняя страница
    this->sROM = *(this->pages);// первая страница в переключаемом банке ПЗУ
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

void DendyMemory::writeMemory (unsigned short adress, unsigned char value){
    
    switch (adress>>13) {
    /* Запись во внутреннее ОЗУ */
    case 0:
        this->RAM->insert(adress & 0x07FF, value);
        break;
        
    /* Запись в ОЗУ картриджа */
    case 3:
        this->WRAM->insert(adress & 0x1FFF, value);
        break;
        
    /* Запись в регистры звукового процессора или видеопроцессора */
    case 1:
    case 2:
        break;
        
    /* Запись в переключаемый банк ПЗУ картриджа */
    case 4:
    case 5:
        this->sROM->insert (adress & 0x3FFF, value);
        break;
        
    /* Запись в непереключаемый банк ПЗУ картриджа */
    case 6:
    case 7:
        this->ROM->insert (adress & 0x3FFF, value);
    }
}

unsigned char DendyMemory::readMemory (unsigned short adress){
    
    switch (adress>>13) {
    /* Чтение из внутреннего ОЗУ приставки */
    case 0:
        return RAM->at (adress & 0x07FF);
        
    /* Чтение из ОЗУ картриджа */
    case 3:
        return WRAM->at(adress & 0x1FFF);
        
    /* Чтение из порта ввода/вывода */
    case 1:
    case 2:
        break;
        
    /* Чтение из переключаемого банка ПЗУ картриджа */
    case 4:
    case 5:
        return this->sROM->at (adress & 0x3FFF);
        
    /* Чтение из непереключаемого банка ПЗУ картриджа */
    case 6:
    case 7:
        return this->ROM->at (adress & 0x3FFF);
    }
    
    return 0;
}

QByteArray* DendyMemory::getRAM (){
    return this->RAM;
}

QByteArray** DendyMemory::getPages (){
    return this->pages;
}

QByteArray* DendyMemory::getROM (){
    return this->ROM;
}

QByteArray* DendyMemory::getSROM (){
    return this->sROM;
}

QByteArray** DendyMemory::getSignGeneratorData (){
    return this->signGeneratorData;
}

QByteArray* DendyMemory::getWRAM (){
    return this->WRAM;
}
