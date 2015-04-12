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
    
    QByteArray** pages;//�������� ������ � ���������
    int numberOfPages;
    
    QByteArray** signGeneratorData;//��� ���������������
    int numberOfSign;
    
    QFile* nesFile;//���� � ������� ��������� (.nes)

public:
    DendyMemory(QFile* nesFile);
    ~DendyMemory();

    void writeMemory(short adress, char value);
    char readMemory(short adress);
};

#endif // DENDYMEMORY_H
