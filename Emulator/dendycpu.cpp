#include "dendycpu.h"

DendyCPU::DendyCPU(DendyMemory *memory)
{
    this->memory = memory;
    this->ResetCPU ();
}

DendyCPU::~DendyCPU()
{
    this->memory = NULL;
}

void DendyCPU::ResetCPU (){
    /* init accumulator and index registers */
    this->cpuReg.a = this->cpuReg.x = this->cpuReg.y = 0;

    /* init flag register:
    * D5 = 1 (always)
    * Z(D1) = 1 (coz cpuReg.a = 0)
    */
    this->cpuReg.p = 0x22;

    /* init stack ptr */
    this->cpuReg.s = 0xFF;

    /* init command counter.
    * after RESET writing adress from
    * memory FFFDh:FFFCh
    */
    this->cpuReg.pc.B.l = this->memory->readMemory ((unsigned short)0xFFFC);
    this->cpuReg.pc.B.h = this->memory->readMemory ((unsigned short)0xFFFD);

    /* init iPeriod */
    //iPeriod = FRAME_PERIOD
}

char DendyCPU::stepCPU (){
    unsigned char opCode = this->memory->readMemory (this->cpuReg.pc.W++);
    short result = 0;
    unsigned char sign = 0;
    unsigned short adress = 0;
    unsigned short highByte = 0;
    
    switch(opCode){

//----------------------------------------------------------------------------------------------ADC//
    
    // ADC #d8
    case 0x69:    
        this->comADC (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 такта
        
    // ADC a8
    case 0x65:
        adress = this->adrZP ();       
        this->comADC (this->memory->readMemory (adress));
        return 0x03; // 3 такта
        
    // ADC a8, X
    case 0x75:
        adress = this->adrZPX ();
        this->comADC (this->memory->readMemory (adress));
        return 0x04; // 4 такта
        
    // ADC a16    
    case 0x6D:
        adress = this->adrABS ();
        this->comADC (this->memory->readMemory (adress));
        return 0x04; // 4 такта
        
    // ADC o16, X    
    case 0x7D:
        adress = this->adrABS ();
        highByte = adress & 0x0100;
        adress += this->cpuReg.x;
        this->comADC (this->memory->readMemory (adress));
        // 4 такта + 1, если была переключена страница
        return ((adress & 0x0100) == highByte) ? 0x04 : 0x05;
        
    // ADC o16, Y
    case 0x79:
        adress = this->adrABS ();
        highByte = adress & 0x0100;
        adress += this->cpuReg.y;
        this->comADC (this->memory->readMemory (adress));
        // 4 такта + 1, если была переключена страница
        return ((adress & 0x0100) == highByte) ? 0x04 : 0x05;
        
    // ADC (a8, x)
    case 0x61:
        adress = this->adrINDX ();
        this->comADC (this->memory->readMemory (adress));
        return 0x06; // 6 тактов
        
    // ADC (a8), Y
    case 0x71:
        adress = this->adrINDY ();
        highByte = adress & 0x0100;
        adress += this->cpuReg.y;
        this->comADC (this->memory->readMemory (adress));
        // 5 тактов + 1, если была переключена страница
        return ((adress & 0x0100) == highByte) ? 0x05 : 0x06;
        
//----------------------------------------------------------------------------------------------AND//
        
    // AND #d8
    case 0x29:
        this->comAND (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 такта
        
    // AND a8
    case 0x25:
        adress = this->adrZP ();       
        this->comAND (this->memory->readMemory (adress));
        return 0x03; // 3 такта
            
    // AND a8, X
    case 0x35:
        adress = this->adrZPX ();
        this->comAND (this->memory->readMemory (adress));
        return 0x04; // 4 такта
            
    // AND a16    
    case 0x2D:    
        adress = this->adrABS ();
        this->comAND (this->memory->readMemory (adress));
        return 0x04; // 4 такта
            
    // AND o16, X    
    case 0x3D:
        adress = this->adrABS ();
        highByte = adress & 0x0100;
        adress += this->cpuReg.x;
        this->comAND (this->memory->readMemory (adress));
        // 4 такта + 1, если была переключена страница
        return ((adress & 0x0100) == highByte) ? 0x04 : 0x05;
            
    // AND o16, Y
    case 0x39:
        adress = this->adrABS ();
        highByte = adress & 0x0100;
        adress += this->cpuReg.y;
        this->comAND (this->memory->readMemory (adress));
        // 4 такта + 1, если была переключена страница
        return ((adress & 0x0100) == highByte) ? 0x04 : 0x05;
            
    // AND (a8, x)
    case 0x21:
        adress = this->adrINDX ();
        this->comAND (this->memory->readMemory (adress));
        return 0x06; // 6 тактов
            
    // AND (a8), Y
    case 0x31:
        adress = this->adrINDY ();
        adress += this->cpuReg.y;
        this->comAND (this->memory->readMemory (adress));
        return 0x05; // 5 тактов
        
//----------------------------------------------------------------------------------------------ASL//
        
    // ASL A
    case 0x0A:
        this->cpuReg.a = this->comASL (this->cpuReg.a);
        return 0x02;
        
    // ASL a8    
    case 0x06:
        adress = this->adrZP ();
        this->memory->writeMemory (adress, this->comASL (this->memory->readMemory (adress)));
        return 0x05;
        
    // ASL a8, X
    case 0x16:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->comASL (this->memory->readMemory (adress)));
        return 0x06;
        
    // ASL a16
    case 0x0E:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->comASL (this->memory->readMemory (adress)));
        return 0x06;
        
    // ASL o16, X
    case 0x1E:
        adress = this->adrABS ();
        adress += this->cpuReg.x;
        this->memory->writeMemory (adress, this->comASL (this->memory->readMemory (adress)));
        return 0x07;
        
//----------------------------------------------------------------------------------------------BCC//
        
    // BCC i8
    case 0x90:
        if (!this->getFlagC ()){
            adress = this->cpuReg.pc.W;
            this->cpuReg.pc.W = this->adrREL ();
            return ((adress & 0x1100) == (this->cpuReg.pc.W & 0x1100)) ? 0x03 : 0x04;
        }
        return 0x02;
        
    // BCS i8
    case 0xB0:
        if (this->getFlagC ()){
            adress = this->cpuReg.pc.W;
            this->cpuReg.pc.W = this->adrREL ();
            return ((adress & 0x1100) == (this->cpuReg.pc.W & 0x1100)) ? 0x03 : 0x04;
        }
        return 0x02;
        
    // BEQ i8
    case 0xF0:
        if (this->getFlagZ ()){
            adress = this->cpuReg.pc.W;
            this->cpuReg.pc.W = this->adrREL ();
            return ((adress & 0x1100) == (this->cpuReg.pc.W & 0x1100)) ? 0x03 : 0x04;
        }
        return 0x02;
 
//----------------------------------------------------------------------------------------------BIT//
        
    // BIT a8
    case 0x24:
        adress = this->adrZP ();
        this->comBIT (this->memory->readMemory (adress));
        return 0x03;
        
    // BIT a16
    case 0x2C:
        adress = this->adrABS ();
        this->comBIT (this->memory->readMemory (adress));
        return 0x04;
    
//----------------------------------------------------------------------------------------------BMI//
        
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------команды//
// команда ADC (коды 69, 65, 75, 6D, 7D, 79, 61, 71)
void DendyCPU::comADC (unsigned char operand){   
    short result = this->cpuReg.a;
    
    unsigned char sign = this->cpuReg.a & 0x80; // для фиксирования переноса из 6 разряда в 7
    
    if (this->getFlagC ()){
        result++;
    }
    
    result += operand;
    
    this->setFlagZ ((result & 0x00FF) == 0); //установка флага, если результат равен 0
    this->setFlagC ((result & 0x0100) != 0); // установка флага, если есть перенос
    this->setFlagV (((result & 0x0100) != 0) || (sign != (result & 0x0080)));
    this->setFlagN ((result & 0x0080) != 0);
    
    this->cpuReg.a = (unsigned char)(result & 0x00FF);
}

// команда AND (коды 29, 25, 35, 2D, 3D, 39, 21, 31)
void DendyCPU::comAND (unsigned char operand){
    this->cpuReg.a &= operand;
    
    // установка флага Z, если результат равен 0
    this->setFlagZ (this->cpuReg.a == 0x00);
    
    // установка флага N в значение бита знака результата
    this->setFlagN ((this->cpuReg.a & 0x80) != 0);
}

// команда ASL (коды 0A, 06, 16, 0E, 1E)
unsigned char DendyCPU::comASL (unsigned char operand){
    unsigned short result = operand;
    result = result<<1;
    
    // установка флага, если результат равен 0
    this->setFlagZ ((result & 0x00FF) == 0); 
    
    // установка флага знака
    this->setFlagN ((result & 0x0080) != 0);
    
    // седьмой бит сдвигается в флаг C
    this->setFlagC ((result & 0x0100) != 0);
    
    return (unsigned char)(result & 0x00FF);
}

// команда BIT (коды 24, 2C)
void DendyCPU::comBIT (unsigned char operand){
    operand &= this->cpuReg.a;
    
    this->setFlagZ (operand == 0x00);
    this->setFlagN ((operand & 0x80) > 0);
    this->setFlagV ((operand & 0x40) > 0);
}

//-------------------------------------------------------------------------------------методы адресации//
// адресация нулевой страницы
unsigned short DendyCPU::adrZP (){
    return 0x0000 + this->memory->readMemory (this->cpuReg.pc.W++);
}

// индексированная по X адресация нулевой страницы
unsigned short DendyCPU::adrZPX (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W++) + this->cpuReg.x;        
    if (adress > 0x00FF){
        adress = 0x0000;
    }
    return adress;
}

// индексированная по Y адресация нулевой страницы
unsigned short DendyCPU::adrZPY (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W++) + this->cpuReg.y;        
    if (adress > 0x00FF){
        adress = 0x0000;
    }
    return adress;
}

// прямая адресация
unsigned short DendyCPU::adrABS (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W + 1);
    adress = adress<<2;
    adress = this->memory->readMemory (this->cpuReg.pc.W);
    this->cpuReg.pc.W += 2;
    return adress;
}

// индексно-косвенная адресация
unsigned short DendyCPU::adrINDX (){
    unsigned short adress;
    unsigned short highByte = this->memory->readMemory (this->cpuReg.pc.W++);
    highByte += this->cpuReg.x;
    adress = this->memory->readMemory ((highByte + 1) & 0x00FF);
    adress = adress<<2;
    adress += this->memory->readMemory (highByte & 0x00FF);
    return adress;
}

// косвенно-индексная адресация
unsigned short DendyCPU::adrINDY (){
    unsigned short highByte = this->memory->readMemory (this->cpuReg.pc.W++);
    unsigned short adress = this->memory->readMemory ((highByte + 1) & 0x00FF);
    adress = adress<<2;
    adress += this->memory->readMemory (highByte);
    return adress;
}

// относительная адресация
unsigned short DendyCPU::adrREL (){
    short temp = 0x0000;
    temp += (signed char)this->memory->readMemory (this->cpuReg.pc.W++);
    temp += this->cpuReg.pc.W;
    return (unsigned short)temp;
}

void DendyCPU::pushStack (unsigned char value){
    this->memory->writeMemory (0x0100 + this->cpuReg.s, value);
    if (this->cpuReg.s){
        this->cpuReg.s--;
    }
}

unsigned char DendyCPU::popStack (){
    if (this->cpuReg.s != 0xFF){
        this->cpuReg.s++;
    }
    return this->memory->readMemory (0xFF + this->cpuReg.s);
}
//----------------------------------------------------------------------------------------------стек//

unsigned char DendyCPU::getRegA (){
    return this->cpuReg.a;
}

unsigned char DendyCPU::getRegP (){
    return this->cpuReg.p;
}

short DendyCPU::getRegPC (){
    return this->cpuReg.pc.W;
}

unsigned char DendyCPU::getRegPCh(){
    return this->cpuReg.pc.B.h;
}

unsigned char DendyCPU::getRegPCl(){
    return this->cpuReg.pc.B.l;
}

unsigned char DendyCPU::getRegS (){
    return this->cpuReg.s;
}

unsigned char DendyCPU::getRegX (){
    return this->cpuReg.x;
}

unsigned char DendyCPU::getRegY (){
    return this->cpuReg.y;
}

bool DendyCPU::getFlagB (){
    return ((this->cpuReg.p & 0x10) > 0);
}

bool DendyCPU::getFlagC (){
    return ((this->cpuReg.p & 0x01) > 0);
}

bool DendyCPU::getFlagD (){
    return ((this->cpuReg.p & 0x08) > 0);
}

bool DendyCPU::getFlagI (){
    return ((this->cpuReg.p & 0x04) > 0);
}

bool DendyCPU::getFlagN (){
    return ((this->cpuReg.p & 0x80) > 0);
}

bool DendyCPU::getFlagV (){
    return ((this->cpuReg.p & 0x40) > 0);
}

bool DendyCPU::getFlagZ (){
    return ((this->cpuReg.p & 0x02) > 0);
}

void DendyCPU::setFlagB (bool state){
    if (state){
        this->cpuReg.p |= 0x10;
    } else {
        this->cpuReg.p &= 0xEF;
    }
}

void DendyCPU::setFlagC (bool state){
    if (state){
        this->cpuReg.p |= 0x01;
    } else {
        this->cpuReg.p &= 0xFE;
    }
}

void DendyCPU::setFlagD (bool state){
    if (state){
        this->cpuReg.p |= 0x08;
    } else {
        this->cpuReg.p &= 0xF7;
    }
}

void DendyCPU::setFlagI (bool state){
    if (state){
        this->cpuReg.p |= 0x04;
    } else {
        this->cpuReg.p &= 0xFB;
    }
}

void DendyCPU::setFlagN (bool state){
    if (state){
        this->cpuReg.p |= 0x80;
    } else {
        this->cpuReg.p &= 0x7F;
    }
}

void DendyCPU::setFlagV (bool state){
    if (state){
        this->cpuReg.p |= 0x40;
    } else {
        this->cpuReg.p &= 0xBF;
    }
}

void DendyCPU::setFlagZ (bool state){
    if (state){
        this->cpuReg.p |= 0x02;
    } else {
        this->cpuReg.p &= 0xFD;
    }
}
