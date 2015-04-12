#ifndef DENDYCPU_H
#define DENDYCPU_H

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
            struct {signed char l, h;} B;  /* �������, ������� ����� ����� */
            short W; /* ����� */
        } pc;
    } cpuReg;       /* 16-��������� ������� ������ */

    int iPeriod;    /* ���������� ������ �� ������������ ����. ����� */
    int iTact;      /* ����� ������, ����������� �� ���������� ������� */

public:
    DendyCPU();
    ~DendyCPU();
    void ResetCPU();

};

#endif // DENDYCPU_H
