#ifndef DENDYMEMORY_H
#define DENDYMEMORY_H

#include <QFile>

using namespace std;

class DendyMemory
{
private:
    QByteArray* RAM; //встроенное ОЗУ(0000h - 07FFh)
    QByteArray* WRAM;//ОЗУ картриджа(6000h - 7FFFh)
    QByteArray* sROM;//переключаемый банк ПЗУ картриджа(8000h - BFFFh)
    QByteArray* ROM; //непереключаемый банк ПЗУ картриджа(C000h - FFFFh). всегда последняя страница
    
    QByteArray** pages;//страницы памяти в картридже
    int numberOfPages;
    
    QByteArray** signGeneratorData;//для знакогенератора
    int numberOfSign;
    
    QFile* nesFile;//файл с данными картриджа (.nes)

public:
    DendyMemory(QFile* nesFile);
    ~DendyMemory();

    void writeMemory(short adress, char value);
    char readMemory(short adress);
};

#endif // DENDYMEMORY_H
