#include "dendycpu.h"

DendyCPU::DendyCPU()
{

}

DendyCPU::~DendyCPU()
{

}

void DendyCPU::ResetCPU (){
    /* init accumulator and index registers */
    this->cpuReg.a = this->cpuReg.x = this->cpuReg.y = 0;

    /* init flag register:
    * D5 = 1
    * Z(D1) = 1 (coz cpuReg.a = 0)
    */
    this->cpuReg.p = 0x22;

    /* init stack ptr */
    this->cpuReg.s = 0xFF;

    /* init command counter.
    * after RESET writing adress from
    * memory FFFCh & FFFDh
    */
    //this->cpuReg.pc.B.l = ReadMemory(0xFFFCh);
    //this->cpuReg.pc.B.h = ReadMemory(0xFFFDh);

    /* init iPeriod */
    //iPeriod = FRAME_PERIOD
}

