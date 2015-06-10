#ifndef DENDYVRAM_H
#define DENDYVRAM_H

#include <QByteArray>
#include <QColor>
#include <cstring>
    
///
/// \brief The DendyVRAM class -- видеопамять приставки Денди
/// (находится в области видимости видеопроцессора (PPU))
///

class DendyPPU;

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
        Sprite sprite[0x40]; // или 64 спрайта
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
    
    bool sprVisible;
    bool bgrdVisible;
    bool allowNMI;
    bool sprites8x8;
    
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
    
    // спрайты отображаются
    bool spritesVisible();
    // фон отображается
    bool backgroundVisible();
    
    // видеопроцессор формирует NMI при кадровом импульсе
    bool isNMIAllowed();
    // размер спрайтов 8х8
    bool spriteIs8x8();
    
    // поступил синхроимпульс
    void synchImpuls();
    
    void sprite0shown();
    
    // данные, переданные контроллером ПДП
    void writeInSpriteMemory (uchar values[]);
    
    friend class DendyPPU;
};

#endif // DENDYVRAM_H
