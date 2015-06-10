#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TIMER_STEP 20

#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <iostream>
#include <QGraphicsScene>
#include <QTimer>
#include "dendydebugger.h"
#include "dendy.h"

namespace Ui {
class MainWindow;
}

///
/// \brief The MainWindow class -- главное окно приложения
///

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DendyDebugger *dDebugger = NULL;
    QFile* nesFile = NULL; // .nes file
    Dendy* dendy = NULL;   // dendy console
    QGraphicsScene* dendyGraphics;
    QGraphicsPixmapItem* pixmap;
    QTimer* timer;
    
    void dendyRun();
    void keyPressEvent (QKeyEvent* keyEvent);
    void keyReleaseEvent (QKeyEvent* keyEvent);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dendyDebuggerButton_clicked();

    void on_openFileNes_clicked();
    
    void dendyUpdate();
    
signals:
    void synchSignal(QGraphicsPixmapItem *pixmap);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
