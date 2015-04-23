/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QToolBox *console;
    QWidget *dendyTab;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *dendyLayout;
    QSpacerItem *dHSpacerL;
    QOpenGLWidget *dendyVideoOutput;
    QSpacerItem *dHSpacerC;
    QFrame *dVLineL;
    QVBoxLayout *dendyTools;
    QSpacerItem *verticalSpacer;
    QPushButton *openFileNes;
    QPushButton *dendyDebuggerButton;
    QSpacerItem *verticalSpacer_2;
    QFrame *dVLineR;
    QWidget *segaTab;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *segaLayout;
    QSpacerItem *sHSpacerL;
    QOpenGLWidget *segaVideoOutput;
    QFrame *sVLineL;
    QVBoxLayout *segaTools;
    QSpacerItem *verticalSpacer_4;
    QPushButton *segaExampleButton;
    QSpacerItem *verticalSpacer_3;
    QFrame *sVLineR;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        console = new QToolBox(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(0, 0, 783, 580));
        console->setMinimumSize(QSize(680, 580));
        console->setMaximumSize(QSize(783, 580));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        console->setFont(font);
        console->setAutoFillBackground(true);
        console->setFrameShape(QFrame::StyledPanel);
        console->setFrameShadow(QFrame::Raised);
        dendyTab = new QWidget();
        dendyTab->setObjectName(QStringLiteral("dendyTab"));
        dendyTab->setGeometry(QRect(0, 0, 781, 520));
        horizontalLayoutWidget = new QWidget(dendyTab);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 781, 516));
        dendyLayout = new QHBoxLayout(horizontalLayoutWidget);
        dendyLayout->setSpacing(6);
        dendyLayout->setContentsMargins(11, 11, 11, 11);
        dendyLayout->setObjectName(QStringLiteral("dendyLayout"));
        dendyLayout->setContentsMargins(0, 0, 0, 0);
        dHSpacerL = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        dendyLayout->addItem(dHSpacerL);

        dendyVideoOutput = new QOpenGLWidget(horizontalLayoutWidget);
        dendyVideoOutput->setObjectName(QStringLiteral("dendyVideoOutput"));
        sizePolicy.setHeightForWidth(dendyVideoOutput->sizePolicy().hasHeightForWidth());
        dendyVideoOutput->setSizePolicy(sizePolicy);
        dendyVideoOutput->setMinimumSize(QSize(512, 480));
        dendyVideoOutput->setMaximumSize(QSize(512, 480));

        dendyLayout->addWidget(dendyVideoOutput);

        dHSpacerC = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        dendyLayout->addItem(dHSpacerC);

        dVLineL = new QFrame(horizontalLayoutWidget);
        dVLineL->setObjectName(QStringLiteral("dVLineL"));
        dVLineL->setFrameShadow(QFrame::Raised);
        dVLineL->setFrameShape(QFrame::VLine);

        dendyLayout->addWidget(dVLineL);

        dendyTools = new QVBoxLayout();
        dendyTools->setSpacing(6);
        dendyTools->setObjectName(QStringLiteral("dendyTools"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        dendyTools->addItem(verticalSpacer);

        openFileNes = new QPushButton(horizontalLayoutWidget);
        openFileNes->setObjectName(QStringLiteral("openFileNes"));

        dendyTools->addWidget(openFileNes);

        dendyDebuggerButton = new QPushButton(horizontalLayoutWidget);
        dendyDebuggerButton->setObjectName(QStringLiteral("dendyDebuggerButton"));
        dendyDebuggerButton->setEnabled(true);
        dendyDebuggerButton->setCheckable(false);
        dendyDebuggerButton->setChecked(false);
        dendyDebuggerButton->setAutoDefault(false);
        dendyDebuggerButton->setDefault(false);

        dendyTools->addWidget(dendyDebuggerButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        dendyTools->addItem(verticalSpacer_2);


        dendyLayout->addLayout(dendyTools);

        dVLineR = new QFrame(horizontalLayoutWidget);
        dVLineR->setObjectName(QStringLiteral("dVLineR"));
        dVLineR->setFrameShadow(QFrame::Raised);
        dVLineR->setFrameShape(QFrame::VLine);

        dendyLayout->addWidget(dVLineR);

        console->addItem(dendyTab, QStringLiteral("DENDY"));
        segaTab = new QWidget();
        segaTab->setObjectName(QStringLiteral("segaTab"));
        segaTab->setGeometry(QRect(0, 0, 781, 520));
        horizontalLayoutWidget_2 = new QWidget(segaTab);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 781, 521));
        segaLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        segaLayout->setSpacing(6);
        segaLayout->setContentsMargins(11, 11, 11, 11);
        segaLayout->setObjectName(QStringLiteral("segaLayout"));
        segaLayout->setContentsMargins(0, 0, 0, 0);
        sHSpacerL = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        segaLayout->addItem(sHSpacerL);

        segaVideoOutput = new QOpenGLWidget(horizontalLayoutWidget_2);
        segaVideoOutput->setObjectName(QStringLiteral("segaVideoOutput"));
        sizePolicy.setHeightForWidth(segaVideoOutput->sizePolicy().hasHeightForWidth());
        segaVideoOutput->setSizePolicy(sizePolicy);
        segaVideoOutput->setMinimumSize(QSize(640, 448));
        segaVideoOutput->setMaximumSize(QSize(640, 448));

        segaLayout->addWidget(segaVideoOutput);

        sVLineL = new QFrame(horizontalLayoutWidget_2);
        sVLineL->setObjectName(QStringLiteral("sVLineL"));
        sVLineL->setFrameShadow(QFrame::Raised);
        sVLineL->setFrameShape(QFrame::VLine);

        segaLayout->addWidget(sVLineL);

        segaTools = new QVBoxLayout();
        segaTools->setSpacing(6);
        segaTools->setObjectName(QStringLiteral("segaTools"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        segaTools->addItem(verticalSpacer_4);

        segaExampleButton = new QPushButton(horizontalLayoutWidget_2);
        segaExampleButton->setObjectName(QStringLiteral("segaExampleButton"));

        segaTools->addWidget(segaExampleButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        segaTools->addItem(verticalSpacer_3);


        segaLayout->addLayout(segaTools);

        sVLineR = new QFrame(horizontalLayoutWidget_2);
        sVLineR->setObjectName(QStringLiteral("sVLineR"));
        sVLineR->setFrameShadow(QFrame::Raised);
        sVLineR->setFrameShape(QFrame::VLine);

        segaLayout->addWidget(sVLineR);

        console->addItem(segaTab, QStringLiteral("SEGA"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(false);
        statusBar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        console->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Emulator", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        openFileNes->setText(QApplication::translate("MainWindow", "Open", 0));
        dendyDebuggerButton->setText(QApplication::translate("MainWindow", "Debugger", 0));
        console->setItemText(console->indexOf(dendyTab), QApplication::translate("MainWindow", "DENDY", 0));
        segaExampleButton->setText(QApplication::translate("MainWindow", "Sega button", 0));
        console->setItemText(console->indexOf(segaTab), QApplication::translate("MainWindow", "SEGA", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
