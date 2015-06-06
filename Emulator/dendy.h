#ifndef DENDY_H
#define DENDY_H

#include "dendycpu.h"
#include "dendymemory.h"

///
/// \brief The Dendy class -- ��������� ������������� �������
///

class Dendy
{
private:
    DendyCPU* cpu;
    DendyMemory* memory;
    
    int period;
    
public:
    Dendy(QFile *nesFile);
    ~Dendy();
    
    void getFrame();
    DendyCPU* getCPU();
    DendyMemory* getMemory();
};

#endif // DENDY_H
