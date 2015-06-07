#ifndef DENDYVRAM_H
#define DENDYVRAM_H

#include <QByteArray>
#include <QColor>
#include <cstring>

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
    
///
/// \brief The DendyVRAM class -- видеопамять приставки Денди
/// (находится в области видимости видеопроцессора (PPU))
///

class DendyVRAM {
private:
    uchar** signGenerator; // знакогенераторы [2][0x1000]
    uchar* bgrdSG; // знакогенератор фона
    uchar* spriteSG; // знакогенератор спрайтов
    
    uchar** spSymb; // символы экранной страницы [4][0x3C0]
    uchar** spAttr; // атрибуты экранной страницы [4][0x040]
    
    uchar* bgrdPalette; // палитра фона [0x010]
    uchar* spritePalette; // палитра спрайтов [0x010]
    
    QByteArray** signGeneratorData; // знакогенераторы в картридже
    short numberOfPages;
    
    // формат записи информации о спрайте
    struct Sprite {
        uchar y; // координата левого верхнего угла по вертикали
        uchar number; // порядковый номер в знакогенераторе
        uchar attributes; // атрибуты спрайта
        uchar x; // координата левого верхнего угла по горизонтали
    };
    
    // память спрайтов
    union SpriteMemory {
        uchar byte[0x100]; // 256 байт
        Sprite* sprite[0x40]; // или 64 спрайта
    };
    SpriteMemory* spriteMemory;
    
    // регистры видеопроцессора
    uchar ppuRegister[0x08]; 
    
////////////////////////////////////////////////////////////////////////    
    
    // отражение страниц
    // 0 - горизонтальное
    // 1 - вертикальное
    uchar mirroring;
    
    // активная страница
    ushort activeSP;
    
    // смещения
    ushort hGap;
    ushort vGap;
    // для определения записи
    // 1 - вертикальный скроллинг
    // 0 - горизонтальный скроллинг
    uchar horv;
    
    // буфер хранения текущего значения
    // (для чтения из 7 регистра)
    uchar bufReg7;
    // адрес, записанный в 6 регистр
    ushort adressReg6;
    ushort autoincrement;
    
////////////////////////////////////////////////////////////////////////
    
    // запись/чтение адресного пространства PPU
    void write(ushort adress, uchar value);
    uchar read(ushort adress);
    
    // указатель на байт экранной страницы
    uchar* getSPByte(ushort adress);
    
public:
    DendyVRAM(QByteArray** signGeneratorData, short numberOfPages, uchar mirroring);
    ~DendyVRAM();

    // доступные CPU регистры PPU
    void writeReg(ushort regNumber, uchar value);
    uchar readReg(ushort regNumber);
};

#endif // DENDYVRAM_H
