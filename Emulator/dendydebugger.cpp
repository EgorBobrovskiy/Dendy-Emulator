#include "dendydebugger.h"
#include "ui_dendydebugger.h"

DendyDebugger::DendyDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DendyDebugger)
{
    ui->setupUi(this);
}

DendyDebugger::~DendyDebugger()
{
    delete ui;
}
