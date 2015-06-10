#ifndef DENDYPPU_H
#define DENDYPPU_H

#include "dendyvram.h"
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <iostream>

class DendyPPU {
private:    
    // видеопамять
    DendyVRAM *vRAM;
    
    // символ в знакогенераторе
    struct SGSymbol {
        uchar color[8][8];
    };
    
    // массив символов экранных страниц
    SGSymbol screenPage[30][32];
    uchar symbolNumbers[30][32];
    
    // painter
    QPainter* painter;
    
    
/////////////////////////////////////////////////////

    SGSymbol* getSymbol (uchar offsetX, uchar offsetY); // расшифровка символа
    void getSPNumbers();
    void getScreenPageInPixels();
    void addAttrToSymbol(SGSymbol* symbol, uchar attribute);
    
    SGSymbol *getSpriteView(uchar number, uchar attributes);
    
    // получение спрайтов, выводимых в строке
    DendyVRAM::Sprite *getSecondaryOAM(uchar lrange, uchar hrange);
    
public:
    DendyPPU(DendyVRAM* vRAM);
    ~DendyPPU();
    
    void drawFrame(QGraphicsPixmapItem* pixmapItem);
    
    bool isNMIAllowed();
};

#endif // DENDYPPU_H
