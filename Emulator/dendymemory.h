#ifndef DENDYMEMORY_H
#define DENDYMEMORY_H

#include <QFile>
#include "dendyvram.h"

using namespace std;

///
/// \brief The DendyMemory class -- ������, ����������� � ������� ��������� ����������
///

class DendyMemory
{
private:
    uchar* RAM; //���������� ���(0000h - 07FFh)
    uchar* WRAM;//��� ���������(6000h - 7FFFh)
    uchar* sROM;//������������� ���� ��� ���������(8000h - BFFFh)
    uchar* ROM; //��������������� ���� ��� ���������(C000h - FFFFh). ������ ��������� ��������
    
    uchar ctrlRegisters[0x17];  // �������� ��������� ����������, ����������� ������� ������� � ������
                                // � ����������� �����/������ (4000h - 4016h)
    
    uchar** pages; //�������� ������ � ���������
    short numberOfPages;
    
    DendyVRAM* vRAM;
    
    QFile* nesFile;//���� � ������� ��������� (.nes)

public:
    DendyMemory(QFile* nesFile);
    ~DendyMemory();

    void writeMemory(unsigned short adress, unsigned char value);
    unsigned char readMemory(unsigned short adress);
    
    uchar* getRAM();
    uchar* getWRAM();
    uchar *getSROM();
    uchar *getROM();
    
    uchar **getPages();
};

#endif // DENDYMEMORY_H
