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
    
    // инициализация регистров видеопроцессора
    this->videoRegisters = new QByteArray(8, '\0');
    
    // инициализация регистров звукового процессора, контроллера ПДП и ввода/вывода
    this->ctrlRegisters = new QByteArray(0x17, '\0');
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
    
    delete this->videoRegisters;
    delete this->ctrlRegisters;
}

void DendyMemory::writeMemory (unsigned short adress, unsigned char value){
    
    switch (adress>>13) {
    /* Запись во внутреннее ОЗУ */
    case 0:
        this->RAM->remove (adress & 0x07FF, 1);
        this->RAM->insert(adress & 0x07FF, value);
        break;
        
    /* Запись в ОЗУ картриджа */
    case 3:
        this->WRAM->remove (adress & 0x1FFF, 1);
        this->WRAM->insert(adress & 0x1FFF, value);
        break;
        
    /* Запись в регистры видеопроцессора */
    case 1:
        if ((adress & 0xFFF8) == 0x2000){
            this->videoRegisters->remove (adress & 0x0007, 1);
            this->videoRegisters->insert (adress & 0x0007, value);
        }
        break;
        
    /* Запись в регистры звукового процессора, контроллера ПДП и ввода/вывода */
    case 2:
        if (adress >= 0x4000 && adress <= 0x4016){
            this->ctrlRegisters->remove (0x001F, 1);
            this->ctrlRegisters->insert (0x001F, value);
        }
        break;
        
    /* Запись в переключаемый банк ПЗУ картриджа */
    case 4:
    case 5:
        this->sROM->remove (adress & 0x3FFF, 1);
        this->sROM->insert (adress & 0x3FFF, value);
        break;
        
    /* Запись в непереключаемый банк ПЗУ картриджа */
    case 6:
    case 7:
        this->ROM->remove (adress & 0x3FFF, 1);
        this->ROM->insert (adress & 0x3FFF, value);
    }
}

unsigned char DendyMemory::readMemory (unsigned short adress){
    
    switch (adress>>13) {
    /* Чтение из внутреннего ОЗУ приставки */
    case 0:
        return this->RAM->at (adress & 0x07FF);
        
    /* Чтение из ОЗУ картриджа */
    case 3:
        return this->WRAM->at(adress & 0x1FFF);
        
    /* Чтение регистров видеопроцессора */
    case 1:
        if ((adress & 0xFFF8) == 0x2000){
            return this->videoRegisters->at (adress & 0x0007);
        }
        return 0x00;
    
    /* Чтение регистров звукового процессора, контроллера ПДП и ввода/вывода */            
    case 2:
        if (adress >= 0x4000 && adress <= 0x4016){
            return this->ctrlRegisters->at (adress & 0x001F);
        }
        return 0x00;
        
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
