#ifndef DENDY_H
#define DENDY_H

#include "dendycpu.h"
#include "dendyppu.h"
#include <QGraphicsPixmapItem>
#include <QObject>

///
/// \brief The Dendy class -- управляет составляющими консоли
///

class Dendy : public QObject{
private:
    Q_OBJECT
    
    DendyCPU* cpu;
    DendyMemory* memory;
    DendyPPU* ppu;
    
    int period;
    
public:
    explicit Dendy(QFile *nesFile, QObject* parent = 0);
    ~Dendy();
    
    DendyCPU* getCPU();
    DendyMemory* getMemory();
    
    void setKeyState(uchar number, bool state);
    
public slots:
    void getFrame(QGraphicsPixmapItem* pixmap);
};

#endif // DENDY_H
