#ifndef DENDYCPU_H
#define DENDYCPU_H

class DendyCPU
{
private:
    struct REG_6502
    {
        unsigned char a;     /* аккумулятор */
        unsigned char p;     /* регистр флагов */
        unsigned char x, y;  /* индексные регистры */
        unsigned char s;     /* указатель стека */
        union
        {
            struct {signed char l, h;} B;  /* старший, младший байты слова */
            short W; /* слово */
        } pc;
    } cpuReg;       /* 16-разрядный счётчик команд */

    int iPeriod;    /* количество тактов до формирования след. кадра */
    int iTact;      /* число тактов, затраченных на выполнение команды */

public:
    DendyCPU();
    ~DendyCPU();
    void ResetCPU();

};

#endif // DENDYCPU_H
