#ifndef DENDYCPU_H
#define DENDYCPU_H

#include "dendymemory.h"
#include <iostream>

///
/// \brief The DendyCPU class -- �������� ������ ���������� (MOS 6502)
///

class DendyCPU
{
private:
    struct REG_6502
    {
        unsigned char a;     /* ����������� */
        unsigned char p;     /* ������� ������ */
        unsigned char x, y;  /* ��������� �������� */
        unsigned char s;     /* ��������� ����� */
        union
        {
            struct {unsigned char l, h;} B;  /* �������, ������� ����� ����� */
            unsigned short W; /* ����� */
        } pc;
    } cpuReg;       /* 16-��������� ������� ������ */
    
    DendyMemory *memory = NULL;

public:
    DendyCPU(DendyMemory* memory);
    ~DendyCPU();
    void resetCPU();
    char nmiCPU();
    char stepCPU();
    //void runCPU();
    
    // �������
    void comADC(unsigned char operand);
    void comAND(unsigned char operand);
    unsigned char comASL(unsigned char operand);
    void comBIT(unsigned char operand);
    char comBranch(bool condition);
    char comBRK();
    void comCMP(unsigned char operand);
    void comCPX(unsigned char operand);
    void comCPY(unsigned char operand);
    void comDEC(unsigned short adress);
    void comEOR(unsigned char operand);
    void comINC(unsigned short adress);
    char comJSR();
    void comLDA(unsigned char operand);
    void comLDX(unsigned char operand);
    void comLDY(unsigned char operand);
    unsigned char comLSR(unsigned char operand);
    void comORA(unsigned char operand);
    unsigned char comROL(unsigned char operand);
    unsigned char comROR(unsigned char operand);
    char comRTI();
    char comRTS();
    void comSBC(unsigned char operand);
    
    // ������ ���������
    unsigned short adrZP();
    unsigned short adrZPX();
    unsigned short adrZPY();
    unsigned short adrABS();
    unsigned short adrINDX();
    unsigned short adrINDY();
    unsigned short adrREL();
    
    // ������� �������� ���������
    unsigned char getRegA();
    unsigned char getRegP();
    unsigned char getRegX();
    unsigned char getRegY();
    unsigned char getRegS();
    short getRegPC();
    unsigned char getRegPCl();
    unsigned char getRegPCh();
    
    // ������� �������� ������
    bool getFlagN();
    bool getFlagV();
    bool getFlagB();
    bool getFlagD();
    bool getFlagI();
    bool getFlagZ();
    bool getFlagC();
    
    // ������� �������� ������
    void setFlagN(bool state);
    void setFlagV(bool state);
    void setFlagB(bool state);
    void setFlagD(bool state);
    void setFlagI(bool state);
    void setFlagZ(bool state);
    void setFlagC(bool state);
    
    // ������ �� ������
    void pushStack(unsigned char value);
    unsigned char popStack();
    
};

#endif // DENDYCPU_H
