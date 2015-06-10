#include "dendyppu.h"

// палитра приставки
// (аналог в RGB представлении)
static QColor palette[0x40] = {
    QColor(117, 117, 117),
    QColor(39, 27, 143),
    QColor(0, 0, 171),
    QColor(71, 0, 59), 
    QColor(143, 0, 119),
    QColor(171, 0, 19),
    QColor(167, 0, 0),
    QColor(127, 11, 0),
    QColor(67, 47, 0),
    QColor(0, 71, 0),
    QColor(0, 81, 0),
    QColor(0, 63, 23),
    QColor(27, 63, 95),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    
    QColor(188, 188, 188),
    QColor(0, 115, 239),
    QColor(35, 59, 239),
    QColor(131, 0, 243),
    QColor(191, 0, 191),
    QColor(231, 0, 91),
    QColor(219, 43, 0),
    QColor(203, 79, 15),
    QColor(139, 115, 0),
    QColor(0, 151, 0),
    QColor(0, 171, 0),
    QColor(0, 147, 59),
    QColor(0, 131, 139),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    
    QColor(255, 255, 255),
    QColor(63, 191, 255),
    QColor(95, 151, 255),
    QColor(167, 139, 253),
    QColor(247, 123, 255),
    QColor(255, 119, 183),
    QColor(255, 119, 99),
    QColor(255, 155, 59),
    QColor(243, 191, 63),
    QColor(131, 211, 19),
    QColor(79, 223, 75),
    QColor(88, 248, 152),
    QColor(0, 235, 219),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    
    QColor(255, 255, 255),
    QColor(171, 231, 255),
    QColor(199, 215, 255),
    QColor(215, 203, 255),
    QColor(255, 199, 255),
    QColor(255, 199, 219),
    QColor(255, 191, 179),
    QColor(255, 219, 171),
    QColor(255, 231, 163),
    QColor(227, 255, 163),
    QColor(171, 243, 191),
    QColor(179, 255, 207),
    QColor(159, 255, 243),
    QColor(0, 0, 0),
    QColor(0, 0, 0),
    QColor(0, 0, 0)
};

DendyPPU::DendyPPU(DendyVRAM *vRAM) {
    this->vRAM = vRAM;
    this->painter = new QPainter();
    
}

DendyPPU::~DendyPPU() {  
    delete this->painter;
}

DendyPPU::SGSymbol* DendyPPU::getSymbol (uchar offsetX, uchar offsetY) {
    uchar number; // номер символа в знакогенераторе, определённый по смещению
    ushort baseX, baseY; // смещение активной страницы
    uchar resultTable; // полученная страница
    ushort x, y; // полученные координаты
    
    // смещение активной страницы
    baseX = ((this->vRAM->activeSP & 1) == 0) ? 0 : 256;
    baseY = ((this->vRAM->activeSP & 2) == 0) ? 0 : 240;
    
    x = baseX + this->vRAM->hGap + offsetX;
    y = baseY + this->vRAM->vGap + offsetY;
    
    // переход в другие страницы,
    // если используется вертикальное отражение
    if (this->vRAM->mirroring) {
        if (y >= (baseY + 240)) y -= 240;
        if (x >= 512) x -= 512;
    } else { // если горизонтальное
        if (x >= (baseX + 256)) x -= 256;
        if (y >= 480) y -= 480;
    }
    
    if (x < 256 && y < 240) {
        resultTable = 0;
    } else if (x < 256) {
        resultTable = 2;
    } else if (y < 240) {
        resultTable = 1;
    } else resultTable = 3;
    
    // смещения внутри экранной таблицы
    offsetX = (x - baseX)/8; 
    offsetY = (y - baseY)/8;
    // номер символа в знакогенераторе
    number = *(*(this->vRAM->spSymb + resultTable) + offsetX + offsetY*32);
    // начало записи символа в знакогенераторе
    uchar* bites = this->vRAM->bgrdSG + (number * 16);
    
    // получаем атрибут
    uchar attribute; // атрибут, соответствующий найденному символу
    uchar attrX; // смещение требуемого атрибута
    uchar attrY;
    
    attrX = (offsetX & 0x1C) >> 2;
    attrY = (offsetY & 0x1C) >> 2;
    attribute = *(*(this->vRAM->spAttr + resultTable) + attrX + attrY*8);
    
    // определяем местоположение иконки в сегменте(4x4) таблицы символов
    attrX = offsetX & 0x03;
    attrY = offsetY & 0x03;
    
    // определяем биты атрибута для добавления
    if (attrX < 2 && attrY < 2) {
        attribute = (attribute & 0x03) << 2;
    } else if (attrY < 2) {
        attribute &= 0x0C;
    } else if (attrX < 2) {
        attribute = (attribute & 0x30) >> 2;
    } else {
        attribute = (attribute & 0xC0) >> 4;
    }
    
    // расшифровка найденного символа
    DendyPPU::SGSymbol* symbol = new DendyPPU::SGSymbol;
    uchar bit0;
    uchar bit1;
    
    // получаем цвет
    for (ushort i = 0; i < 8; i++) {
        bit0 = *(bites + i + 0);
        bit1 = *(bites + i + 8);
        
        symbol->color[i][0] = attribute + ((bit1 & 0x80) ? 0x2 : 0) + ((bit0 & 0x80) ? 1 : 0);
        symbol->color[i][1] = attribute + ((bit1 & 0x40) ? 0x2 : 0) + ((bit0 & 0x40) ? 1 : 0);
        symbol->color[i][2] = attribute + ((bit1 & 0x20) ? 0x2 : 0) + ((bit0 & 0x20) ? 1 : 0);
        symbol->color[i][3] = attribute + ((bit1 & 0x10) ? 0x2 : 0) + ((bit0 & 0x10) ? 1 : 0);
        symbol->color[i][4] = attribute + ((bit1 & 0x08) ? 0x2 : 0) + ((bit0 & 0x08) ? 1 : 0);
        symbol->color[i][5] = attribute + ((bit1 & 0x04) ? 0x2 : 0) + ((bit0 & 0x04) ? 1 : 0);
        symbol->color[i][6] = attribute + ((bit1 & 0x02) ? 0x2 : 0) + ((bit0 & 0x02) ? 1 : 0);
        symbol->color[i][7] = attribute + ((bit1 & 0x01) ? 0x2 : 0) + ((bit0 & 0x01) ? 1 : 0);
    }
        
    return symbol;
}

DendyPPU::SGSymbol* DendyPPU::getSpriteView (uchar number, uchar attributes) {
    uchar* bites = this->vRAM->spriteSG + (number * 16);
    
    DendyPPU::SGSymbol* symbol = new DendyPPU::SGSymbol;
    uchar bit0;
    uchar bit1;
    ushort i;
    uchar colorAttribute = (attributes & 0x03) << 2;
    
    // проходим по байтам
    for (i = 0; i < 8; i++) {
        bit0 = *(bites + i + 0);
        bit1 = *(bites + i + 8);
        
        symbol->color[i][0] = ((bit1 & 0x80) ? 0x2 : 0) + ((bit0 & 0x80) ? 1 : 0) + colorAttribute;
        symbol->color[i][1] = ((bit1 & 0x40) ? 0x2 : 0) + ((bit0 & 0x40) ? 1 : 0) + colorAttribute;
        symbol->color[i][2] = ((bit1 & 0x20) ? 0x2 : 0) + ((bit0 & 0x20) ? 1 : 0) + colorAttribute;
        symbol->color[i][3] = ((bit1 & 0x10) ? 0x2 : 0) + ((bit0 & 0x10) ? 1 : 0) + colorAttribute;
        symbol->color[i][4] = ((bit1 & 0x08) ? 0x2 : 0) + ((bit0 & 0x08) ? 1 : 0) + colorAttribute;
        symbol->color[i][5] = ((bit1 & 0x04) ? 0x2 : 0) + ((bit0 & 0x04) ? 1 : 0) + colorAttribute;
        symbol->color[i][6] = ((bit1 & 0x02) ? 0x2 : 0) + ((bit0 & 0x02) ? 1 : 0) + colorAttribute;
        symbol->color[i][7] = ((bit1 & 0x01) ? 0x2 : 0) + ((bit0 & 0x01) ? 1 : 0) + colorAttribute;
    }

    // отражение относительно горизонтальной оси
    if (attributes & 0x40) {
        uchar temp;
        for (uchar h = 0, l = 7; h < l; h++, l--) {
            for (uchar o = 0; o < 8; o++) {
                temp = symbol->color[h][o];
                symbol->color[h][o] = symbol->color[l][o];
                symbol->color[l][o] = temp;
            }
        }
    }
    
    // отражение относительно вертикальной оси
    if (attributes & 0x80) {
        uchar temp;
        for (uchar h = 0, l = 7; h < l; h++, l--) {
            for (uchar o = 0; o < 8; o++) {
                temp = symbol->color[o][h];
                symbol->color[o][h] = symbol->color[o][l];
                symbol->color[o][l] = temp;
            }
        }
    }
    
    return symbol;
}

DendyVRAM::Sprite* DendyPPU::getSecondaryOAM (uchar lrange, uchar hrange) {
    DendyVRAM::Sprite* oam = new DendyVRAM::Sprite[8];
    
    // инициализация
    for (uchar i = 0; i < 8; i++) {
        (oam + i)->attributes = 0xFF;
        (oam + i)->number = 0xFF;
        (oam + i)->x = 0xFF;
        (oam + i)->y = 0xFF;
    }
    
    this->vRAM->ppuRegister[2] &= 0xDF;
    
    uchar prim, sec;
    
    // заполняем линию
    for (prim = 0, sec = 0; prim < 64 && sec < 8; prim++) {
        *(oam + sec) = this->vRAM->spriteMemory->sprite[prim];
        
        if ((oam + sec)->y >= lrange && (oam + sec)->y < hrange) {
            sec++;
        }
    }
    
    // ищем переполнение
    if (sec == 8) {
        for (; prim < 64; prim++) {
            if(this->vRAM->spriteMemory->sprite[prim].y >= lrange && this->vRAM->spriteMemory->sprite[prim].y < hrange) {
                this->vRAM->ppuRegister[2] |= 0x20;
                break;
            }
        }
    }
    
    return oam;
}

void DendyPPU::getScreenPageInPixels () {
    ushort i, j;
    
    // заполняем символами с вычисленными цветами
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 30; j++) {
            this->screenPage[j][i] = *(getSymbol (i, j));
        }
    }
}

void DendyPPU::drawFrame (QGraphicsPixmapItem* pixmapItem) {
    // выставляем флаг формирования изображения
    this->vRAM->ppuRegister[2] &= 0x7F;
    this->getScreenPageInPixels ();
    //std::cout << "image ready" << std::endl;
    
    QPixmap pixmap = pixmapItem->pixmap ();
    this->painter->begin (&pixmap);
    this->painter->scale (2, 2);
    
    // заполнение холста
    this->painter->fillRect (0, 0, 256, 240, palette[*(this->vRAM->bgrdPalette + 0x00)]);
    
    DendyVRAM::Sprite* oam;
    
    // отрисовка строк на экран
    for (uchar line = 0; line < 30; line++) {
        DendyPPU::SGSymbol temp;
        uchar colorNum;
        ushort x, y;
        
        oam = this->getSecondaryOAM (line * 8, (line + 1) * 8);
        
        // вывод спрайтов с приоритетом 0
        if (this->vRAM->spritesVisible ()) {
            for (uchar num = 0; num < 8; num++) {
                if ( (((oam + num)->attributes & 0x20) == 0x00) && ((oam + num)->y != 0xFF) ) {
                    temp = *(this->getSpriteView ((oam + num)->number, (oam + num)->attributes));
                    
                    if ((oam + num)->number == 0) this->vRAM->sprite0shown ();
                    
                    // отрисовка
                    for(uchar j = 0; j < 8; j++) {
                        for (uchar i = 0; i < 8; i++) {
                            colorNum = temp.color[j][i];
                            if ((colorNum & 0x03) != 0x00) {
                                this->painter->setPen (palette[*(this->vRAM->spritePalette + colorNum)]);
                                this->painter->drawPoint ((oam + num)->x + i, (oam + num)->y + j);
                            }
                        }
                    }
                }
            }
        }
        
        // вывод фона
        if (this->vRAM->backgroundVisible ()) {
            // координата строки
            y = line * 8;
                
            // столбец
            for (ushort xtile = 0; xtile < 32; xtile++) {
                // получение символа из таблицы
                temp = this->screenPage[line][xtile];
                x = xtile * 8;
                
                for (ushort j = 0; j < 8; j++) {
                    for (ushort i = 0; i < 8; i++) {
                        colorNum = temp.color[j][i];
                        if ((colorNum & 0x03) != 0x00) {
                            this->painter->setPen (palette[*(this->vRAM->bgrdPalette + colorNum)]);
                            this->painter->drawPoint (x + i, y + j);
                        }
                    }
                }
            }
        }
        
        // вывод спрайтов с приоритетом 1
        if (this->vRAM->spritesVisible ()) {
            for (ushort num = 0; num < 8; num++) {
                
                if ( (((oam + num)->attributes & 0x20) != 0x00) && ((oam + num)->y != 0xFF) ) {
                    temp = *(this->getSpriteView ((oam + num)->number, (oam + num)->attributes));
                    
                    if ((oam + num)->number == 0) this->vRAM->sprite0shown ();
                    
                    for(uchar j = 0; j < 8; j++) {
                        for (uchar i = 0; i < 8; i++) {
                            colorNum = temp.color[j][i];
                            if ((colorNum & 0x03) != 0x00) {
                                this->painter->setPen (palette[*(this->vRAM->spritePalette + colorNum)]);
                                this->painter->drawPoint ((oam + num)->x + i, (oam + num)->y + j);
                            }
                        }
                    }
                }
            }
        }
        
        delete[] oam;
    }
    
    this->painter->end ();
    pixmapItem->setPixmap (pixmap);
    
    // генерация кадрового синхроимпульса
    this->vRAM->ppuRegister[2] |= 0x80;
    this->vRAM->synchImpuls ();
}

bool DendyPPU::isNMIAllowed() {
    return this->vRAM->isNMIAllowed ();
}
