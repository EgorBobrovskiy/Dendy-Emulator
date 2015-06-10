#ifndef DENDYVRAM_H
#define DENDYVRAM_H

#include <QByteArray>
#include <QColor>
#include <cstring>
    
///
/// \brief The DendyVRAM class -- ����������� ��������� �����
/// (��������� � ������� ��������� ��������������� (PPU))
///

class DendyPPU;

class DendyVRAM {
private:
    uchar** signGenerator; // ��������������� [2][0x1000]
    uchar* bgrdSG; // �������������� ����
    uchar* spriteSG; // �������������� ��������
    
    uchar** spSymb; // ������� �������� �������� [4][0x3C0]
    uchar** spAttr; // �������� �������� �������� [4][0x040]
    
    uchar* bgrdPalette; // ������� ���� [0x010]
    uchar* spritePalette; // ������� �������� [0x010]
    
    QByteArray** signGeneratorData; // ��������������� � ���������
    short numberOfPages;
    
    // ������ ������ ���������� � �������
    struct Sprite {
        uchar y; // ���������� ������ �������� ���� �� ���������
        uchar number; // ���������� ����� � ���������������
        uchar attributes; // �������� �������
        uchar x; // ���������� ������ �������� ���� �� �����������
    };
    
    // ������ ��������
    union SpriteMemory {
        uchar byte[0x100]; // 256 ����
        Sprite sprite[0x40]; // ��� 64 �������
    };
    SpriteMemory* spriteMemory;
    
    // �������� ���������������
    uchar ppuRegister[0x08]; 
    
////////////////////////////////////////////////////////////////////////    
    
    // ��������� �������
    // 0 - ��������������
    // 1 - ������������
    uchar mirroring;
    
    // �������� ��������
    ushort activeSP;
    
    // ��������
    ushort hGap;
    ushort vGap;
    // ��� ����������� ������
    // 1 - ������������ ���������
    // 0 - �������������� ���������
    uchar horv;
    
    // ����� �������� �������� ��������
    // (��� ������ �� 7 ��������)
    uchar bufReg7;
    // �����, ���������� � 6 �������
    ushort adressReg6;
    ushort autoincrement;
    
    bool sprVisible;
    bool bgrdVisible;
    bool allowNMI;
    bool sprites8x8;
    
////////////////////////////////////////////////////////////////////////
    
    // ������/������ ��������� ������������ PPU
    void write(ushort adress, uchar value);
    uchar read(ushort adress);
    
    // ��������� �� ���� �������� ��������
    uchar* getSPByte(ushort adress);
    
public:
    DendyVRAM(QByteArray** signGeneratorData, short numberOfPages, uchar mirroring);
    ~DendyVRAM();

    // ��������� CPU �������� PPU
    void writeReg(ushort regNumber, uchar value);
    uchar readReg(ushort regNumber);
    
    // ������� ������������
    bool spritesVisible();
    // ��� ������������
    bool backgroundVisible();
    
    // �������������� ��������� NMI ��� �������� ��������
    bool isNMIAllowed();
    // ������ �������� 8�8
    bool spriteIs8x8();
    
    // �������� �������������
    void synchImpuls();
    
    void sprite0shown();
    
    // ������, ���������� ������������ ���
    void writeInSpriteMemory (uchar values[]);
    
    friend class DendyPPU;
};

#endif // DENDYVRAM_H
