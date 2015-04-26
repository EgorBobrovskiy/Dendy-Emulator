#ifndef DENDYMEMORY_H
#define DENDYMEMORY_H

#include <QFile>

using namespace std;

class DendyMemory
{
private:
    QByteArray* RAM; //���������� ���(0000h - 07FFh)
    QByteArray* WRAM;//��� ���������(6000h - 7FFFh)
    QByteArray* sROM;//������������� ���� ��� ���������(8000h - BFFFh)
    QByteArray* ROM; //��������������� ���� ��� ���������(C000h - FFFFh). ������ ��������� ��������
    QByteArray* videoRegisters; // �������� ��������������� (2000h - 2007h)
    QByteArray* ctrlRegisters;  // �������� ��������� ����������, ����������� ������� ������� � ������
                                // � ����������� �����/������ (4000h - 4016h)
    
    QByteArray** pages;//�������� ������ � ���������
    int numberOfPages;
    
    QByteArray** signGeneratorData;//��� ���������������
    int numberOfSign;
    
    QFile* nesFile;//���� � ������� ��������� (.nes)

public:
    DendyMemory(QFile* nesFile);
    ~DendyMemory();

    void writeMemory(unsigned short adress, unsigned char value);
    unsigned char readMemory(unsigned short adress);
    
    QByteArray* getRAM();
    QByteArray* getWRAM();
    QByteArray* getSROM();
    QByteArray* getROM();
    
    QByteArray** getPages();
    QByteArray** getSignGeneratorData();
};

#endif // DENDYMEMORY_H
