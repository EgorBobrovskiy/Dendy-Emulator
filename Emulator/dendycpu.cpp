#include "dendycpu.h"
#define RUN 1

DendyCPU::DendyCPU(DendyMemory *memory)
{
    this->memory = memory;
    
    /* init accumulator and index registers */
    this->cpuReg.a = this->cpuReg.x = this->cpuReg.y = 0;
    
    /* init flag register:
    * D5 = 1 (always)
    * Z(D1) = 1 (coz cpuReg.a = 0)
    */
    this->cpuReg.p = 0x22;

    /* init stack ptr */
    this->cpuReg.s = 0xFF;

    this->resetCPU ();
}

DendyCPU::~DendyCPU(){
}

void DendyCPU::resetCPU (){
    
    /* init command counter.
    * after RESET writing adress from
    * memory FFFDh:FFFCh
    */
    this->cpuReg.pc.B.l = this->memory->readMemory ((unsigned short)0xFFFC);
    this->cpuReg.pc.B.h = this->memory->readMemory ((unsigned short)0xFFFD);
}

char DendyCPU::nmiCPU (){
    // ���������� �������� ��������� � ����
    this->pushStack (this->cpuReg.pc.B.h);
    this->pushStack (this->cpuReg.pc.B.l);
    this->pushStack (this->cpuReg.p);
    
    /* ������� � ����������� ����������, ����� �������� 
    *  ������� �� ������ 0xFFFA
    */
    this->cpuReg.pc.B.l = this->memory->readMemory (0xFFFA);
    this->cpuReg.pc.B.h = this->memory->readMemory (0xFFFB);
    
    // ������� � ����������� �������� 7 ������
    return 0x07;
}


//void DendyCPU::runCPU (){
//    // ����� ��������� ����������
//    this->resetCPU ();
    
//    while (RUN){
//        // ���������� �������� ������
//        this->iPeriod -= this->stepCPU ();
        
//        if (this->iPeriod <= 0){
//            this->iPeriod += FRAME_PERIOD;
            
//            // ��� �������� �����
            
//            // ��������� �������
            
//            // ����������� ������������� ����������
//            this->nmiCPU ();
//        }
        
//    }
//}

char DendyCPU::stepCPU (){
    unsigned char opCode = this->memory->readMemory (this->cpuReg.pc.W++);
    unsigned short adress = 0;
    unsigned short highByte = 0;
    
    switch(opCode){
//----------------------------------------------------------------------------------------------ADC//
    
    // ADC #d8
    case 0x69:    
        this->comADC (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // ADC a8
    case 0x65:
        adress = this->adrZP ();       
        this->comADC (this->memory->readMemory (adress));
        return 0x03; // 3 �����
        
    // ADC a8, X
    case 0x75:
        adress = this->adrZPX ();
        this->comADC (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // ADC a16    
    case 0x6D:
        adress = this->adrABS ();
        this->comADC (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // ADC a16, X    
    case 0x7D:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comADC (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // ADC o16, Y
    case 0x79:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comADC (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // ADC (a8, X)
    case 0x61:
        adress = this->adrINDX ();
        this->comADC (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // ADC (a8), Y
    case 0x71:
        adress = this->adrINDY ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comADC (this->memory->readMemory (adress));
        // 5 ������ + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x05 : 0x06;
        
//----------------------------------------------------------------------------------------------AND//
        
    // AND #d8
    case 0x29:
        this->comAND (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // AND a8
    case 0x25:
        adress = this->adrZP ();       
        this->comAND (this->memory->readMemory (adress));
        return 0x03; // 3 �����
            
    // AND a8, X
    case 0x35:
        adress = this->adrZPX ();
        this->comAND (this->memory->readMemory (adress));
        return 0x04; // 4 �����
            
    // AND a16    
    case 0x2D:    
        adress = this->adrABS ();
        this->comAND (this->memory->readMemory (adress));
        return 0x04; // 4 �����
            
    // AND o16, X    
    case 0x3D:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comAND (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
            
    // AND o16, Y
    case 0x39:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comAND (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
            
    // AND (a8, x)
    case 0x21:
        adress = this->adrINDX ();
        this->comAND (this->memory->readMemory (adress));
        return 0x06; // 6 ������
            
    // AND (a8), Y
    case 0x31:
        adress = this->adrINDY ();
        adress += this->cpuReg.y;
        this->comAND (this->memory->readMemory (adress));
        return 0x05; // 5 ������
        
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
        
//--------------------------------------------------------------------------------------BCC-BCS-BEQ//
        
    // BCC i8
    case 0x90:
        return this->comBranch (!this->getFlagC ());
        
    // BCS i8
    case 0xB0:
        return this->comBranch (this->getFlagC ());
        
    // BEQ i8
    case 0xF0:
        return this->comBranch (this->getFlagZ ());
 
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
    
//--------------------------------------------------------------------------------------BMI-BNE-BPL//
        
    // BMI i8
    case 0x30:
        return this->comBranch (this->getFlagN ());
        
    // BNE i8
    case 0xD0:
        return this->comBranch (!this->getFlagZ ());
        
    // BPL i8
    case 0x10:
        return this->comBranch (!this->getFlagN ());
        
//--------------------------------------------------------------------------------------BRK-BVC-BVS//
        
    // BRK
    case 0x00:
        return this->comBRK ();
        
    // BVC i8
    case 0x50:
        return this->comBranch (!this->getFlagV ());
        
    // BVS i8
    case 0x70:
        return this->comBranch (this->getFlagV ());

//----------------------------------------------------------------------------------CLC-CLD-CLI-CLV//        
        
    // CLC
    case 0x18:
        this->setFlagC (false);
        return 0x02;
        
    // CLD
    case 0xD8:
        this->setFlagD (false);
        return 0x02;
        
    // CLI
    case 0x58:
        this->setFlagI (false);
        return 0x02;
        
    // CLV
    case 0xB8:
        this->setFlagV (false);
        return 0x02;
        
//----------------------------------------------------------------------------------------------CMP//
    // CMP #d8
    case 0xC9:
        this->comCMP (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02;
        
    // CMP a8
    case 0xC5:
        this->comCMP (this->memory->readMemory (this->adrZP ()));
        return 0x03;
        
    // CMP a8, X
    case 0xD5:
        this->comCMP (this->memory->readMemory (this->adrZPX ()));
        return 0x04;
        
    // CMP a16
    case 0xCD:
        this->comCMP (this->memory->readMemory (this->adrABS ()));
        return 0x04;
        
    // CMP a16, X
    case 0xDD:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comCMP (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // CMP a16, Y
    case 0xD9:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comCMP (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // CMP (a8, X)
    case 0xC1:
        adress = this->adrINDX ();
        this->comADC (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // CMP (a8), Y
    case 0xD1:
        adress = this->adrINDY ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comCMP (this->memory->readMemory (adress));
        // 5 ������ + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x05 : 0x06;
        
//----------------------------------------------------------------------------------------------CPX//
        
    // CPX #d8
    case 0xE0:
        this->comCPX (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02;
        
    // CPX a8
    case 0xE4:
        this->comCPX (this->memory->readMemory (this->adrZP ()));
        return 0x03;
        
    // CPX a16
    case 0xEC:
        this->comCPX (this->memory->readMemory (this->adrABS ()));
        return 0x04;
        
//----------------------------------------------------------------------------------------------CPY//
        
    // CPY #d8
    case 0xC0:
        this->comCPY (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02;
        
    // CPY a8
    case 0xC4:
        this->comCPY (this->memory->readMemory (this->adrZP ()));
        return 0x03;
        
    // CPY a16
    case 0xCC:
        this->comCPY (this->memory->readMemory (this->adrABS ()));
        return 0x04;
        
//----------------------------------------------------------------------------------------------DEC//
        
    // DEC a8
    case 0xC6:
        this->comDEC (this->adrZP ());
        return 0x05;
        
    // DEC a8, X
    case 0xD6:
        this->comDEC (this->adrZPX ());
        return 0x06;
        
    // DEC a16
    case 0xCE:
        this->comDEC (this->adrABS ());
        return 0x06;
        
    // DEC a16, X
    case 0xDE:
        this->comDEC (this->adrABS () + this->cpuReg.x);
        return 0x07;
        
//------------------------------------------------------------------------------------------DEX-DEY//
    
    // DEX
    case 0xCA:
        this->cpuReg.x--;
        this->setFlagZ (this->cpuReg.x == 0);
        this->setFlagN ((this->cpuReg.x & 0x80) != 0x00);
        return 0x02;
        
    // DEY
    case 0x88:
        this->cpuReg.y--;
        this->setFlagZ (this->cpuReg.y == 0);
        this->setFlagN ((this->cpuReg.y & 0x80) != 0x00);
        return 0x02;
        
//----------------------------------------------------------------------------------------------EOR//  
        
    // EOR #d8
    case 0x49:    
        this->comEOR (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // EOR a8
    case 0x45:
        adress = this->adrZP ();       
        this->comEOR (this->memory->readMemory (adress));
        return 0x03; // 3 �����
        
    // EOR a8, X
    case 0x55:
        adress = this->adrZPX ();
        this->comEOR (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // EOR a16    
    case 0x4D:
        adress = this->adrABS ();
        this->comEOR (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // EOR a16, X    
    case 0x5D:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comEOR (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // EOR o16, Y
    case 0x59:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comEOR (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // EOR (a8, X)
    case 0x41:
        adress = this->adrINDX ();
        this->comEOR (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // EOR (a8), Y
    case 0x51:
        adress = this->adrINDY ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comEOR (this->memory->readMemory (adress));
        // 5 ������ + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x05 : 0x06;
        
//----------------------------------------------------------------------------------------------INC//
        
    // INC a8
    case 0xE6:
        this->comINC (this->adrZP ());
        return 0x05;
        
    // INC a8, X
    case 0xF6:
        this->comINC (this->adrZPX ());
        return 0x06;
        
    // INC a16
    case 0xEE:
        this->comINC (this->adrABS ());
        return 0x06;
        
    // INC a16, X
    case 0xFE:
        this->comINC (this->adrABS () + this->cpuReg.x);
        return 0x07;
        
//------------------------------------------------------------------------------------------INX-INY//
            
    // INX
    case 0xE8:
        this->cpuReg.x++;
        this->setFlagZ (this->cpuReg.x == 0);
        this->setFlagN ((this->cpuReg.x & 0x80) != 0x00);
        return 0x02;
        
    // INY
    case 0xC8:
        this->cpuReg.y++;
        this->setFlagZ (this->cpuReg.y == 0);
        this->setFlagN ((this->cpuReg.y & 0x80) != 0x00);
        return 0x02;
        
//------------------------------------------------------------------------------------------JMP-JSR//
        
    // JMP a16
    case 0x4C:
        this->cpuReg.pc.W = this->adrABS ();
        return 0x03;
        
    // JMP (a16)
    case 0x6C:
        adress = this->cpuReg.pc.W;
        this->cpuReg.pc.B.l = this->memory->readMemory (++adress);
        adress = ((adress & 0x00FF) == 0x00FF) ? (adress & 0xFF00) : (adress + 1);
        this->cpuReg.pc.B.h = this->memory->readMemory (adress + 2);
        return 0x05;
        
    // JSR a16
    case 0x20:
        return this->comJSR ();
        
//----------------------------------------------------------------------------------------------LDA//
        
    // LDA #d8
    case 0xA9:    
        this->comLDA (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // LDA a8
    case 0xA5:
        adress = this->adrZP ();       
        this->comLDA (this->memory->readMemory (adress));
        return 0x03; // 3 �����
        
    // LDA a8, X
    case 0xB5:
        adress = this->adrZPX ();
        this->comLDA (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // LDA a16    
    case 0xAD:
        adress = this->adrABS ();
        this->comLDA (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // LDA a16, X    
    case 0xBD:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comLDA (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // LDA a16, Y
    case 0xB9:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comLDA (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // LDA (a8, X)
    case 0xA1:
        adress = this->adrINDX ();
        this->comLDA (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // LDA (a8), Y
    case 0xB1:
        adress = this->adrINDY ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comLDA (this->memory->readMemory (adress));
        // 5 ������ + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x05 : 0x06;
        
//----------------------------------------------------------------------------------------------LDX//
        
    // LDX #d8
    case 0xA2:    
        this->comLDX (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // LDX a8
    case 0xA6:
        this->comLDX (this->adrZP ());
        return 0x03;
        
    // LDX a8, Y
    case 0xB6:
        this->comLDX (this->adrZPY ());
        return 0x04;
        
    // LDX a16
    case 0xAE:
        this->comLDX (this->adrABS ());
        return 0x04;
        
    // LDX a16, Y
    case 0xBE:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comLDX (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
//----------------------------------------------------------------------------------------------LDY//
        
    // LDY #d8
    case 0xA0:    
        this->comLDY (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // LDY a8
    case 0xA4:
        this->comLDY (this->adrZP ());
        return 0x03;
        
    // LDY a8, X
    case 0xB4:
        this->comLDY (this->adrZPX ());
        return 0x04;
        
    // LDY a16
    case 0xAC:
        this->comLDY (this->adrABS ());
        return 0x04;
        
    // LDY a16, X
    case 0xBC:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comLDY (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
//----------------------------------------------------------------------------------------------LSR//
        
    // LSR A
    case 0x4A:
        this->cpuReg.a = this->comLSR (this->cpuReg.a);
        return 0x02;
        
    // LSR a8    
    case 0x46:
        adress = this->adrZP ();
        this->memory->writeMemory (adress, this->comLSR (this->memory->readMemory (adress)));
        return 0x05;
        
    // LSR a8, X
    case 0x56:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->comLSR (this->memory->readMemory (adress)));
        return 0x06;
        
    // LSR a16
    case 0x4E:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->comLSR (this->memory->readMemory (adress)));
        return 0x06;
        
    // LSR o16, X
    case 0x5E:
        adress = this->adrABS ();
        adress += this->cpuReg.x;
        this->memory->writeMemory (adress, this->comLSR (this->memory->readMemory (adress)));
        return 0x07;
        
//----------------------------------------------------------------------------------------------NOP//
        
    // NOP (no operation)
    case 0xEA:
        return 0x02;
        
//----------------------------------------------------------------------------------------------ORA//
        
    // ORA #d8
    case 0x09:
        this->comORA (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // ORA a8
    case 0x05:
        adress = this->adrZP ();       
        this->comAND (this->memory->readMemory (adress));
        return 0x03; // 3 �����
        
    // ORA a8, X
    case 0x15:
        adress = this->adrZPX ();
        this->comORA (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // ORA a16    
    case 0x0D:    
        adress = this->adrABS ();
        this->comAND (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // ORA o16, X    
    case 0x1D:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comORA (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // ORA o16, Y
    case 0x19:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comORA (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // ORA (a8, x)
    case 0x01:
        adress = this->adrINDX ();
        this->comORA (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // ORA (a8), Y
    case 0x11:
        adress = this->adrINDY ();
        adress += this->cpuReg.y;
        this->comORA (this->memory->readMemory (adress));
        return 0x05; // 5 ������
        
//----------------------------------------------------------------------------------PHA-PHP-PLA-PLP//
        
    // PHA
    case 0x48:
        this->pushStack (this->cpuReg.a);
        return 0x03;
        
    // PHP
    case 0x08:
        this->pushStack (this->cpuReg.p);
        return 0x03;
        
    // PLA
    case 0x68:
        this->cpuReg.a = this->popStack ();
        this->setFlagZ (this->cpuReg.a == 0);
        this->setFlagN ((this->cpuReg.a & 0x80) != 0x00);
        return 0x04;
        
    // PLP
    case 0x28:
        this->cpuReg.p = this->popStack ();
        return 0x04;
        
//----------------------------------------------------------------------------------------------ROL//
                
    // ROL A
    case 0x2A:
        this->cpuReg.a = this->comROL (this->cpuReg.a);
        return 0x02;
        
    // ROL a8    
    case 0x26:
        adress = this->adrZP ();
        this->memory->writeMemory (adress, this->comROL (this->memory->readMemory (adress)));
        return 0x05;
        
    // ROL a8, X
    case 0x36:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->comROL (this->memory->readMemory (adress)));
        return 0x06;
        
    // ROL a16
    case 0x2E:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->comROL (this->memory->readMemory (adress)));
        return 0x06;
        
    // ROL a16, X
    case 0x3E:
        adress = this->adrABS ();
        adress += this->cpuReg.x;
        this->memory->writeMemory (adress, this->comROL (this->memory->readMemory (adress)));
        return 0x07;
        
//----------------------------------------------------------------------------------------------ROR//
        
    // ROR A
    case 0x6A:
        this->cpuReg.a = this->comROR (this->cpuReg.a);
        return 0x02;
        
    // ROR a8    
    case 0x66:
        adress = this->adrZP ();
        this->memory->writeMemory (adress, this->comROR (this->memory->readMemory (adress)));
        return 0x05;
        
    // ROR a8, X
    case 0x76:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->comROR (this->memory->readMemory (adress)));
        return 0x06;
        
    // ROR a16
    case 0x6E:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->comROR (this->memory->readMemory (adress)));
        return 0x06;
        
    // ROR a16, X
    case 0x7E:
        adress = this->adrABS ();
        adress += this->cpuReg.x;
        this->memory->writeMemory (adress, this->comROR (this->memory->readMemory (adress)));
        return 0x07;
        
//------------------------------------------------------------------------------------------RTI-RTS//
        
    // RTI (������� �� ����������)
    case 0x40:
        return this->comRTI ();
        
    // RTS (������� �� ������������)
    case 0x60:
        return this->comRTS ();
        
//----------------------------------------------------------------------------------------------SBC//
        
    // SBC #d8
    case 0xE9:    
        this->comSBC (this->memory->readMemory (this->cpuReg.pc.W++));
        return 0x02; // 2 �����
        
    // SBC a8
    case 0xE5:
        adress = this->adrZP ();       
        this->comSBC (this->memory->readMemory (adress));
        return 0x03; // 3 �����
        
    // SBC a8, X
    case 0xF5:
        adress = this->adrZPX ();
        this->comSBC (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // SBC a16    
    case 0xED:
        adress = this->adrABS ();
        this->comSBC (this->memory->readMemory (adress));
        return 0x04; // 4 �����
        
    // SBC a16, X    
    case 0xFD:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.x;
        this->comSBC (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // SBC o16, Y
    case 0xF9:
        adress = this->adrABS ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comSBC (this->memory->readMemory (adress));
        // 4 ����� + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x04 : 0x05;
        
    // SBC (a8, X)
    case 0xE1:
        adress = this->adrINDX ();
        this->comSBC (this->memory->readMemory (adress));
        return 0x06; // 6 ������
        
    // SBC (a8), Y
    case 0xF1:
        adress = this->adrINDY ();
        highByte = adress & 0x0300;
        adress += this->cpuReg.y;
        this->comSBC (this->memory->readMemory (adress));
        // 5 ������ + 1, ���� ���� ����������� ��������
        return ((adress & 0x0300) == highByte) ? 0x05 : 0x06;
        
//--------------------------------------------------------------------------------------SEC-SED-SEI//
        
    // SEC
    case 0x38:
        this->setFlagC (true);
        return 0x02;
        
    // SED
    case 0xF8:
        this->setFlagD (true);
        return 0x02;
        
    // SEI
    case 0x78:
        this->setFlagI (true);
        return 0x02;
        
//----------------------------------------------------------------------------------------------STA//
        
    // STA a8
    case 0x85:
        adress = this->adrZP ();       
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x03; // 3 �����
        
    // STA a8, X
    case 0x95:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x04; // 4 �����
        
    // STA a16    
    case 0x8D:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x04; // 4 �����
        
    // STA a16, X    
    case 0x9D:
        adress = this->adrABS ();
        adress += this->cpuReg.x;
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x05;
        
    // STA a16, Y
    case 0x99:
        adress = this->adrABS ();
        adress += this->cpuReg.y;
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x05;
        
    // STA (a8, X)
    case 0x81:
        adress = this->adrINDX ();
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x06; // 6 ������
        
    // STA (a8), Y
    case 0x91:
        adress = this->adrINDY ();
        adress += this->cpuReg.y;
        this->memory->writeMemory (adress, this->cpuReg.a);
        return 0x06;
        
//----------------------------------------------------------------------------------------------STX//
        
    // STX a8
    case 0x86:
        adress = this->adrZP ();       
        this->memory->writeMemory (adress, this->cpuReg.x);
        return 0x03; // 3 �����
        
    // STX a8, Y
    case 0x96:
        adress = this->adrZPY ();
        this->memory->writeMemory (adress, this->cpuReg.x);
        return 0x04; // 4 �����
        
    // STX a16    
    case 0x8E:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->cpuReg.x);
        return 0x04; // 4 �����
        
//----------------------------------------------------------------------------------------------STY//
        
    // STY a8
    case 0x84:
        adress = this->adrZP ();       
        this->memory->writeMemory (adress, this->cpuReg.y);
        return 0x03; // 3 �����
        
    // STY a8, X
    case 0x94:
        adress = this->adrZPX ();
        this->memory->writeMemory (adress, this->cpuReg.y);
        return 0x04; // 4 �����
        
    // STY a16    
    case 0x8C:
        adress = this->adrABS ();
        this->memory->writeMemory (adress, this->cpuReg.y);
        return 0x04; // 4 �����
        
//--------------------------------------------------------------------------------------TAX-TAY-TSX//
        
    // TAX
    case 0xAA:
        this->cpuReg.x = this->cpuReg.a;
        this->setFlagZ (this->cpuReg.x == 0x00); 
        this->setFlagN ((this->cpuReg.x & 0x80) != 0);
        return 0x02;
        
    // TAY
    case 0xA8:
        this->cpuReg.y = this->cpuReg.a;
        this->setFlagZ (this->cpuReg.y == 0x00); 
        this->setFlagN ((this->cpuReg.y & 0x80) != 0);
        return 0x02;
        
    // TSX
    case 0xBA:
        this->cpuReg.x = this->cpuReg.s;
        this->setFlagZ (this->cpuReg.x == 0x00); 
        this->setFlagN ((this->cpuReg.x & 0x80) != 0);
        return 0x02;
        
//--------------------------------------------------------------------------------------TXA-TYA-TXS//
    
    // TXA
    case 0x8A:
        this->cpuReg.a = this->cpuReg.x;
        this->setFlagZ (this->cpuReg.a == 0x00); 
        this->setFlagN ((this->cpuReg.a & 0x80) != 0);
        return 0x02;
        
    // TYA
    case 0x98:
        this->cpuReg.a = this->cpuReg.y;
        this->setFlagZ (this->cpuReg.a == 0x00); 
        this->setFlagN ((this->cpuReg.a & 0x80) != 0);
        return 0x02;
        
    // TSX
    case 0x9A:
        this->cpuReg.s = this->cpuReg.x;
        return 0x02;        
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------�������//
// ������� ADC (���� 69, 65, 75, 6D, 7D, 79, 61, 71)
void DendyCPU::comADC (unsigned char operand){   
    short result = this->cpuReg.a;
    
    if (this->getFlagC ()){
        result++;
    }
    
    result += operand;
    
    this->setFlagZ ((result & 0x00FF) == 0); //��������� �����, ���� ��������� ����� 0
    this->setFlagC ((result & 0x0100) != 0); // ��������� �����, ���� ���� �������
    this->setFlagV ((this->cpuReg.a ^ result) & (operand ^ result) & 0x80);
    this->setFlagN ((result & 0x0080) != 0);
    
    this->cpuReg.a = (unsigned char)(result); // ��� ���� ������ �������� ������� 8 ���
//    this->cpuReg.a = (unsigned char)(result & 0x00FF);
}

// ������� AND (���� 29, 25, 35, 2D, 3D, 39, 21, 31)
void DendyCPU::comAND (unsigned char operand){
    this->cpuReg.a &= operand;
    
    // ��������� ����� Z, ���� ��������� ����� 0
    this->setFlagZ (this->cpuReg.a == 0x00);
    
    // ��������� ����� N � �������� ���� ����� ����������
    this->setFlagN ((this->cpuReg.a & 0x80) != 0);
}

// ������� ASL (���� 0A, 06, 16, 0E, 1E)
unsigned char DendyCPU::comASL (unsigned char operand){
    // ������� ��� ���������� � ���� C
    this->setFlagC ((operand & 0x80) != 0);
    
    operand = operand<<1;
    
    // ��������� �����, ���� ��������� ����� 0
    this->setFlagZ (operand == 0x00); 
    
    // ��������� ����� �����
    this->setFlagN ((operand & 0x80) != 0);
    
    return operand;
}

// ������� BIT (���� 24, 2C)
void DendyCPU::comBIT (unsigned char operand){
    operand &= this->cpuReg.a;
    
    this->setFlagZ (operand == 0x00);
    this->setFlagN ((operand & 0x80) > 0);
    this->setFlagV ((operand & 0x40) > 0);
}

// �������� ������� (branch on ...)
char DendyCPU::comBranch (bool condition){
    if (condition){
        unsigned short adress = this->cpuReg.pc.W;
        this->cpuReg.pc.W = this->adrREL ();
        return ((adress & 0x1100) == (this->cpuReg.pc.W & 0x1100)) ? 0x03 : 0x04;
    }
    return 0x02;
}

// ����������� ����������
char DendyCPU::comBRK (){
    this->pushStack (this->cpuReg.pc.B.h);
    this->pushStack (this->cpuReg.pc.B.l);
    this->pushStack (this->cpuReg.p);
        
    this->cpuReg.pc.B.l = this->memory->readMemory (0xFFFE);
    this->cpuReg.pc.B.h = this->memory->readMemory (0xFFFF);
        
    this->setFlagB (true);
    this->setFlagI (true);
        
    return 0x07;
}

// ������� CMP (���� C9, C5, D5, CD, DD, D9, C1, D1)
void DendyCPU::comCMP (unsigned char operand){
    unsigned short result = 0x0100; 
    result += this->cpuReg.a;
    result -= operand;
    
    this->setFlagZ (result == 0x0000);
    this->setFlagC ((result & 0x0100) == 0x0000);
    this->setFlagN ((result & 0x0080) != 0x0000);
}

// ������� CPX (���� E0, E4, EC)
void DendyCPU::comCPX (unsigned char operand){
    unsigned short result = 0x0100; 
    result += this->cpuReg.x;
    result -= operand;
    
    this->setFlagZ (result == 0x0000);
    this->setFlagC ((result & 0x0100) == 0x0000);
    this->setFlagN ((result & 0x0080) != 0x0000);
}

// ������� CPY (���� C0, C4, CC)
void DendyCPU::comCPY (unsigned char operand){
    unsigned short result = 0x0100; 
    result += this->cpuReg.y;
    result -= operand;
    
    this->setFlagZ (result == 0x0000);
    this->setFlagC ((result & 0x0100) == 0x0000);
    this->setFlagN ((result & 0x0080) != 0x0000);
}

// ������� DEC (���� C6, D6, CE, DE)
void DendyCPU::comDEC (unsigned short adress){
    unsigned char operand = this->memory->readMemory (adress);
    operand--;
    
    this->setFlagZ (operand == 0);
    this->setFlagN ((operand & 0x80) != 0x00);
    
    this->memory->writeMemory (adress, operand);
}

// ������� EOR (���� 49, 45, 55, 4D, 5D, 59, 41, 51)
void DendyCPU::comEOR (unsigned char operand){
    this->cpuReg.a ^= operand;
    
    this->setFlagZ (this->cpuReg.a == 0x00);
    this->setFlagN ((operand & 0x80) != 0x00);
    
}

// ������� INC (���� E6, F6, EE, FE)
void DendyCPU::comINC (unsigned short adress){
    unsigned char operand = this->memory->readMemory (adress);
    operand++;
    
    this->setFlagZ (operand == 0);
    this->setFlagN ((operand & 0x80) != 0x00);
    
    this->memory->writeMemory (adress, operand);
}

// ������� � ���������� ������������ (��� 20)
char DendyCPU::comJSR (){
    unsigned short newAdress = this->adrABS ();
    
    // ���������� ������ ��������
    this->pushStack (this->cpuReg.pc.B.h);
    this->pushStack (this->cpuReg.pc.B.l);
    
    this->cpuReg.pc.W = newAdress;
    return 0x06;
}

// ������� LDA (���� A9, A5, B5, AD, BD, B9, A1, B1)
void DendyCPU::comLDA (unsigned char operand){
    this->cpuReg.a = operand;
    
    this->setFlagZ (operand == 0);
    this->setFlagN ((operand & 0x80) != 0x00);
}

// ������� LDX (���� A2, A6, B6, AE, BE)
void DendyCPU::comLDX (unsigned char operand){
    this->cpuReg.x = operand;
    
    this->setFlagZ (operand == 0);
    this->setFlagN ((operand & 0x80) != 0x00);
}

// ������� LDY (���� A0, A4, B4, AC, BC)
void DendyCPU::comLDY (unsigned char operand){
    this->cpuReg.y = operand;
    
    this->setFlagZ (operand == 0);
    this->setFlagN ((operand & 0x80) != 0x00);
}

// ������� LSR (���� 4A, 46, 56, 4E, 5E)
unsigned char DendyCPU::comLSR (unsigned char operand){
    // ������� ��� ���������� � ���� C
    this->setFlagC ((operand & 0x01) != 0);
    
    operand = operand>>1;
    
    // ��������� �����, ���� ��������� ����� 0
    this->setFlagZ (operand == 0x00); 
    
    // ��������� ����� �����
    this->setFlagN (false);
    
    return operand;
}

// ������� ORA (���� 09, 05, 15, 0D, 1D, 19, 01, 11)
void DendyCPU::comORA (unsigned char operand){
    this->cpuReg.a |= operand;
    
    // ��������� ����� Z, ���� ��������� ����� 0
    this->setFlagZ (this->cpuReg.a == 0x00);
    
    // ��������� � ���� N �������� ���� ����� ����������
    this->setFlagN ((this->cpuReg.a & 0x80) != 0);
}

// ������� ROL (���� 2A, 26, 36, 2E, 3E)
unsigned char DendyCPU::comROL (unsigned char operand){
    // ������� ��� ������������ � ���� C
    this->setFlagC ((operand & 0x80) != 0);
    
    operand = operand<<1;
    
    if (this->getFlagC ()){
        operand |= 0x01;
    }
    
    // ��������� �����, ���� ��������� ����� 0
    this->setFlagZ (operand == 0x00); 
    
    // ��������� ����� �����
    this->setFlagN ((operand & 0x80) != 0);
    
    return operand;
}

// ������� ROR (���� 6A, 66, 76, 6E, 7E)
unsigned char DendyCPU::comROR (unsigned char operand){
    // ������� ��� ������������ � ���� C
    this->setFlagC ((operand & 0x01) != 0);
    
    operand = operand>>1;
    
    if (this->getFlagC ()){
        operand |= 0x80;
    }
    
    // ��������� �����, ���� ��������� ����� 0
    this->setFlagZ (operand == 0x00); 
    
    // ��������� ����� �����
    this->setFlagN ((operand & 0x80) != 0);
    
    return operand;
}

// ������� �� ����������
char DendyCPU::comRTI(){
    this->cpuReg.p = this->popStack ();
    this->cpuReg.pc.B.l = this->popStack ();
    this->cpuReg.pc.B.h = this->popStack ();
    
    return 0x06;
}

// ������� �� ������������
char DendyCPU::comRTS (){
    this->cpuReg.pc.B.l = this->popStack ();
    this->cpuReg.pc.B.h = this->popStack ();
    
    return 0x06;
}

// ������� SBC (���� E9, E5, F5, ED, FD, F9, E1, F1)
void DendyCPU::comSBC (unsigned char operand){
    short result = this->cpuReg.a;
    
    if (this->getFlagC ()){
        result--;
    }
    
    result -= operand;
    
    this->setFlagZ ((result & 0x00FF) == 0); //��������� �����, ���� ��������� ����� 0
    this->setFlagC ((result & 0x8000) != 0); // ��������� �����, ���� ��������� < 0
    // ���� V ������������, ���� ����� ������������ ��� ��������� ��� ��� ������ �������� ��� ����������
    this->setFlagV ((this->cpuReg.a ^ result) & (operand ^ result) & 0x80);
    
    this->setFlagN ((result & 0x0080) != 0);
    
    this->cpuReg.a = (unsigned char)(result & 0x00FF);
}

//-------------------------------------------------------------------------------------������ ���������//
// ��������� ������� ��������
unsigned short DendyCPU::adrZP (){
    return 0x0000 + this->memory->readMemory (this->cpuReg.pc.W++);
}

// ��������������� �� X ��������� ������� ��������
unsigned short DendyCPU::adrZPX (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W++) + this->cpuReg.x;        
    if (adress > 0x00FF){
        adress = 0x0000;
    }
    return adress;
}

// ��������������� �� Y ��������� ������� ��������
unsigned short DendyCPU::adrZPY (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W++) + this->cpuReg.y;        
    if (adress > 0x00FF){
        adress = 0x0000;
    }
    return adress;
}

// ������ ���������
unsigned short DendyCPU::adrABS (){
    unsigned short adress = this->memory->readMemory (this->cpuReg.pc.W + 1);
    adress = adress<<2;
    adress = this->memory->readMemory (this->cpuReg.pc.W);
    this->cpuReg.pc.W += 2;
    return adress;
}

// ��������-��������� ���������
unsigned short DendyCPU::adrINDX (){
    unsigned short adress;
    unsigned short highByte = this->memory->readMemory (this->cpuReg.pc.W++);
    highByte += this->cpuReg.x;
    adress = this->memory->readMemory ((highByte + 1) & 0x00FF);
    adress = adress<<2;
    adress += this->memory->readMemory (highByte & 0x00FF);
    return adress;
}

// ��������-��������� ���������
unsigned short DendyCPU::adrINDY (){
    unsigned short highByte = this->memory->readMemory (this->cpuReg.pc.W++);
    unsigned short adress = this->memory->readMemory ((highByte + 1) & 0x00FF);
    adress = adress<<2;
    adress += this->memory->readMemory (highByte);
    return adress;
}

// ������������� ���������
unsigned short DendyCPU::adrREL (){
    short temp = this->cpuReg.pc.W + 1;
    temp += (signed char)this->memory->readMemory (this->cpuReg.pc.W++);
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
//----------------------------------------------------------------------------------------------����//

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
