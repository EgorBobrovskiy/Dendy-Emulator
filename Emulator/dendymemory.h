#ifndef DENDYMEMORY_H
#define DENDYMEMORY_H

#include <QFile>
#include "dendyvram.h"

using namespace std;

///
/// \brief The DendyMemory class -- память, находящаяся в области видимости процессора
///

class DendyMemory
{
private:
    uchar* RAM; //встроенное ОЗУ(0000h - 07FFh)
    uchar* WRAM;//ОЗУ картриджа(6000h - 7FFFh)
    uchar* sROM;//переключаемый банк ПЗУ картриджа(8000h - BFFFh)
    uchar* ROM; //непереключаемый банк ПЗУ картриджа(C000h - FFFFh). всегда последняя страница
    
    uchar ctrlRegisters[0x17];  // регистры звукового процессора, контроллера прямого доступа к памяти
                                // и контроллера ввода/вывода (4000h - 4016h)
    
    uchar** pages; //страницы памяти в картридже
    short numberOfPages;
    
    DendyVRAM* vRAM;
    
    QFile* nesFile;//файл с данными картриджа (.nes)
    
    uchar register4016;
    uchar register4017;
    uchar previous4016;
    uchar joy1;
    uchar joy2;
    // 0 - A; 1 - B; 2 - SELECT; 3 - START
    // 4 - UP; 5 - DOWN; 6 - LEFT; 7 - RIGHT
    bool keyPressed[8];
    void fixKeyState();

public:
    DendyMemory(QFile* nesFile);
    ~DendyMemory();

    void writeMemory(unsigned short adress, unsigned char value);
    unsigned char readMemory(unsigned short adress);
    
    void writeDMA(ushort adress);
    void setKeyState(uchar number, bool state);
    
    DendyVRAM* getDendyVRAM();
    
    uchar* getRAM();
    uchar* getWRAM();
    uchar* getSROM();
    uchar* getROM();
    uchar** getPages();
};

#endif // DENDYMEMORY_H
