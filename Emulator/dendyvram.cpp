#include "dendyvram.h"

DendyVRAM::DendyVRAM(QByteArray **signGeneratorData, short numberOfPages, uchar mirroring) {
    this->mirroring = mirroring;
    this->activeSP = 0;
    this->hGap = 0;
    this->vGap = 0;
    this->horv = 1;
    this->autoincrement = 1;
    this->allowNMI = true;
    this->sprites8x8 = true;
    this->bgrdVisible = true;
    this->sprVisible = true;
    
    this->signGeneratorData = signGeneratorData;
    this->numberOfPages = numberOfPages;
    
    // инициализация знакогенераторов
    this->signGenerator = new uchar*[2];
    *(this->signGenerator + 0) = new uchar[0x1000];
    *(this->signGenerator + 1) = new uchar[0x1000];
    if (numberOfPages == 1) {
        for (short i = 0; i < 0x1000; i++) {
            *(*(this->signGenerator + 0) + i) = (*(this->signGeneratorData + 0))->at (i);
            *(*(this->signGenerator + 1) + i) = (*(this->signGeneratorData + 0))->at (i);
        }
    } else if (numberOfPages == 2) {
        for (short i = 0; i < 2; i++) {
            for (short j = 0; j < 0x1000; j++) {
                *(*(this->signGenerator + i) + j) = (*(this->signGeneratorData + i))->at (j);
            }
        }
    }
    
    this->spSymb = new uchar*[4];
    this->spAttr = new uchar*[4];
    for (short i = 0; i < 4; i++) {
        *(this->spSymb + i) = new uchar[0x3C0];
        *(this->spAttr + i) = new uchar[0x040];
        std::memset(*(this->spSymb + i), 0, 0x3C0);
        std::memset(*(this->spAttr + i), 0, 0x040);
    }
    
    this->bgrdPalette = new uchar[0x010];
    this->spritePalette = new uchar[0x010];
    std::memset(this->bgrdPalette, 0, 0x010);
    std::memset(this->spritePalette, 0, 0x010);
    
    this->spriteMemory = new SpriteMemory;
    for (ushort i = 0; i < 256; i++) {
        this->spriteMemory->byte[i] = 0xFF;
    }
    
    for (short i = 0; i < 8; i++) {
        this->ppuRegister[i] = 0;
    }
    this->ppuRegister[2] |= 0x80;
}

DendyVRAM::~DendyVRAM() {
    short i;
    
// signGeneratorData
    for (i = 0; i < this->numberOfPages; i++) {
        delete *(this->signGeneratorData + i);
    }    
    delete[] this->signGeneratorData;

//signGenerator    
    for (i = 0; i < 2; i++) {
        delete[] *(this->signGenerator + i);
    }
    delete[] this->signGenerator;
    
//spAttr & spSymb
    for (i = 0; i < 4; i++) {
        delete[] *(this->spAttr + i);
        delete[] *(this->spSymb + i);
    }
    delete[] this->spAttr;
    delete[] this->spSymb;
    
//palettes
    delete[] this->bgrdPalette;
    delete[] this->spritePalette;
    
//spriteMemory
    delete this->spriteMemory;
}

void DendyVRAM::write(ushort adress, uchar value) {
    switch (adress>>12) {
    // запись в знакогенератор 0
    case 0:
        *(*(this->signGenerator + 0) + (adress & 0x0FFF)) = value;
        break;
        
    // запись в знакогнератор 1
    case 1:
        *(*(this->signGenerator + 1) + (adress & 0x0FFF)) = value;
        break;
        
    // запись в экранные страницы
    case 2:
        *(this->getSPByte (adress & 0x0FFF)) = value;
        break;
        
    case 3:
        if ((adress & 0xFF00) == 0x3F00) {
            // запись в палитры
            if ((adress & 0x0003) != 0) {
                if ((adress & 0x00F0) == 0x0000) *(this->bgrdPalette + (adress & 0x000F)) = value;
                if ((adress & 0x00F0) == 0x0010) *(this->spritePalette + (adress & 0x000F)) = value;
            } else {
                // отражение цветов с нулевыми младшими битами
                *(this->bgrdPalette + 0x00) = value;
            }
        } else {
            // запись в отражение экранных страниц
            *(this->getSPByte (adress & 0x0FFF)) = value;
        } break;
    
    default: 
        //do nothing
        break;
    }
}

uchar* DendyVRAM::getSPByte (ushort adress) {
    if ((adress & 0x03C0) == 0x03C0) {
        // это атрибуты страницы
        return *(this->spAttr + (adress >> 10)) + (adress & 0x003F);
    } else {
        // а это символы страницы
        ushort page = adress >> 10;
        // вертикальное отражение
        if (this->mirroring) {
            if (page == 2) page = 0;
            if (page == 3) page = 1;
        } else {
            // горизонтальное отражение
            if (page == 1) page = 0;
            if (page == 3) page = 2;
        }
        return *(this->spSymb + page) + (adress & 0x03BF);
    }
}

uchar DendyVRAM::read (ushort adress) {
    switch (adress>>12) {
    // чтение из знакогенератора 0
    case 0:
        return *(*(this->signGenerator + 0) + (adress & 0x0FFF));
        
    // чтение из знакогенератора 1
    case 1:
        return *(*(this->signGenerator + 1) + (adress & 0x0FFF));
        
    // чтение из экранных страниц
    case 2:
        return *(this->getSPByte (adress & 0x0FFF));
        
    case 3:
        if ((adress & 0xFF00) == 0x3F00) {
            // чтение из палитры
            if ((adress & 0x0003) != 0) {
                if ((adress & 0x00F0) == 0x0000) return *(this->bgrdPalette + (adress & 0x000F));
                if ((adress & 0x00F0) == 0x0010) return *(this->spritePalette + (adress & 0x000F));
            } else {
                // чтение из отражения палитры
                return *(this->bgrdPalette + 0x00);
            }
        } else {
            // чтение из отражения экранных страниц
            return *(this->getSPByte (adress & 0x0FFF));
        }
    
    default: 
        break;
    }
    return 0x00;
}

void DendyVRAM::writeReg (ushort regNumber, uchar value) {
    switch (regNumber) {
    
    // регистр управления 
    case 0:
        this->ppuRegister[0] = value;
        // номер активной страницы
        this->activeSP = value & 0x03;
        // указатели на знакогенераторы фона и спрайтов
        this->bgrdSG = *(this->signGenerator + ((value>>4) & 0x01));
        this->spriteSG = *(this->signGenerator + ((value>>3) & 0x01));
        
        // разрешение формирования NMI
        this->allowNMI = ((value & 0x80) == 0x80);
        // размер спрайтов
        this->sprites8x8 = ((value & 0x20) != 0x20);
        
        // 1 - автоинкремент на 32; 0 - на 1
        this->autoincrement = (value & 0x04) ? 32 : 1;
        break;
        
    // регистр управления
    case 1:
        this->ppuRegister[1] = value;
        this->sprVisible = ((value & 0x10) != 0);
        this->bgrdVisible = ((value & 0x08) != 0);
        break;
      
    // запись адреса в памяти спрайтов
    case 3:
        this->ppuRegister[3] = value;
        break;
        
    // запись в память спрайтов по адресу
    case 4:
        this->ppuRegister[4] = value;
        this->spriteMemory->byte[this->ppuRegister[3]++] = value;
        break;
        
    // аппаратный скроллинг фона
    case 5:
        if (this->horv++ % 2) {
            // вертикальный скроллинг
            this->vGap = value;
            this->ppuRegister[5] = value;
        } else {
            // горизонтальный скроллинг
            this->hGap = value;
            this->ppuRegister[5] = value;
        }
        break;
        
    // адрес для операций с видеопамятью
    case 6:
        this->adressReg6 = (adressReg6 << 8) + value;
        this->ppuRegister[6] = value;
        break;
        
    // запись в видеопамять по адресу, полученному через 6 регистр
    case 7:
        this->write (this->adressReg6, value);
        this->ppuRegister[7] = value;
        this->adressReg6 += this->autoincrement;
        break;
        
    default:
        break;
    }
}

uchar DendyVRAM::readReg (ushort regNumber) {
    uchar temp;
    
    switch (regNumber) {
    
    // состояние видеопроцессора
    case 2:
        temp = this->ppuRegister[2];
        // старшие биты сбрасываются при чтении
        this->ppuRegister[2] &= 0x3F;
        return temp;
        
    // чтение из памяти спрайтов
    case 4:
        this->ppuRegister[4] = this->spriteMemory->byte[this->ppuRegister[3]++];
        return this->ppuRegister[4];
        
    // чтение из видеопамяти
    case 7:
        if ((this->adressReg6 & 0x3F00) != 0x3F00) {
            // если чтение идёт из адресного пространства PPU,
            // используется буфер
            this->ppuRegister[7] = this->bufReg7;
            this->bufReg7 = this->read (this->adressReg6);
        } else {
            // палитры находятся в регистрах, поэтому буфер не нужен
            this->ppuRegister[7] = this->read (this->adressReg6);
        }
        // автоинкремент адреса
        this->adressReg6 += this->autoincrement;
        return this->ppuRegister[7];
        
    default:
        break;
    }
    
    return 0x00;
}

void DendyVRAM::synchImpuls () {
    // сброс бита вывода 0-го спрайта
    this->ppuRegister[2] &= 0xBF;
}

bool DendyVRAM::backgroundVisible (){
    return this->bgrdVisible;
}

bool DendyVRAM::spritesVisible () {
    return this->sprVisible;
}

bool DendyVRAM::isNMIAllowed () {
    return this->allowNMI;
}

bool DendyVRAM::spriteIs8x8 () {
    return this->sprites8x8;
}

void DendyVRAM::writeInSpriteMemory (uchar values[]) {
    for (ushort i = 0; i < 0x100; i++) {
        this->spriteMemory->byte[i] = values[i];
    }
}

void DendyVRAM::sprite0shown (){
    this->ppuRegister[2] |= 0x40;
}
