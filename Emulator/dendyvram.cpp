#include "dendyvram.h"

DendyVRAM::DendyVRAM(QByteArray **signGeneratorData, short numberOfPages) {
    this->signGeneratorData = signGeneratorData;
    this->numberOfPages = numberOfPages;
}

DendyVRAM::~DendyVRAM() {
    for (short i = 0; i < this->numberOfPages; i++) {
        delete *(this->signGeneratorData + i);
    }
    
    delete[] this->signGeneratorData;
}
