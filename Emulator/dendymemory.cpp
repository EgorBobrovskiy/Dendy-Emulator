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
    
    // заполнение страниц памяти
    int offset; // смещение страницы относительно начала файла
    for (int i = 0; i < this->numberOfPages; i++){
        (*(this->pages + i)) = new uchar[0x4000];
        offset = i * 0x4000 + 16;
        
        for (int j = 0; j < 0x4000; j++){
            *(*(this->pages + i) + j) = (byteArray.at (offset + j));
        }
    }
    
    // заполнение страниц знакогенератора    
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
    
    // инициализация видеопамяти
    this->vRAM = new DendyVRAM(signGeneratorData, numberOfSign);
    
    this->ROM = *(this->pages + this->numberOfPages - 1); // последняя страница
    this->sROM = *(this->pages);// первая страница в переключаемом банке ПЗУ
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
    /* Запись во внутреннее ОЗУ */
    case 0:
        *(this->RAM + (adress & 0x07FF)) = value;
        break;
        
    /* Запись в ОЗУ картриджа */
    case 3:
        *(this->WRAM + (adress & 0x1FFF)) = value;
        break;
        
    /* Запись в регистры видеопроцессора */
    case 1:
//            this->cpu.videoRegisters->remove (adress & 0x0007, 1);
//            this->cpu.videoRegisters->insert (adress & 0x0007, value);
        break;
        
    /* Запись в регистры звукового процессора, контроллера ПДП и ввода/вывода */
    case 2:
//            this->cpu.ctrlRegisters->remove (0x001F, 1);
//            this->cpu.ctrlRegisters->insert (0x001F, value);
        break;
        
    /* Запись в переключаемый банк ПЗУ картриджа */
    case 4:
    case 5:
        *(this->sROM + (adress & 0x3FFF)) = value;
        break;
        
    /* Запись в непереключаемый банк ПЗУ картриджа */
    case 6:
    case 7:
        *(this->ROM + (adress & 0x3FFF)) = value;
    }
}

unsigned char DendyMemory::readMemory (unsigned short adress){
    
    switch (adress>>13) {
    /* Чтение из внутреннего ОЗУ приставки */
    case 0:
        return *(this->RAM + (adress & 0x07FF));
        
    /* Чтение из ОЗУ картриджа */
    case 3:
        return *(this->WRAM + (adress & 0x1FFF));
        
    /* Чтение регистров видеопроцессора */
    case 1:
        return 0x00;
        //return this->cpu.videoRegisters->at (adress & 0x0007);
    
    /* Чтение регистров звукового процессора, контроллера ПДП и ввода/вывода */            
    case 2:
//        if (adress >= 0x4000 && adress <= 0x4016){
//            return this->cpu.ctrlRegisters->at (adress & 0x001F);
//        }
        return 0x00;
        
    /* Чтение из переключаемого банка ПЗУ картриджа */
    case 4:
    case 5:
        return *(this->sROM + (adress & 0x3FFF));
        
    /* Чтение из непереключаемого банка ПЗУ картриджа */
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
