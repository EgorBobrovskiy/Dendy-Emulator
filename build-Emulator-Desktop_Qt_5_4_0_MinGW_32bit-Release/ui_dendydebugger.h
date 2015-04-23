/********************************************************************************
** Form generated from reading UI file 'dendydebugger.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DENDYDEBUGGER_H
#define UI_DENDYDEBUGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DendyDebugger
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout;
    QGroupBox *registers;
    QWidget *pc;
    QLabel *pcName;
    QLineEdit *pcValue;
    QGroupBox *flags;
    QWidget *gridLayoutWidget;
    QGridLayout *values;
    QCheckBox *N;
    QCheckBox *checkBox_3;
    QCheckBox *V;
    QCheckBox *B;
    QCheckBox *D;
    QCheckBox *I;
    QCheckBox *Z;
    QCheckBox *C;
    QLabel *flagN;
    QLabel *flagV;
    QLabel *flagD;
    QLabel *flagI;
    QLabel *flagZ;
    QLabel *flagC;
    QLabel *flagB;
    QWidget *s;
    QLabel *sName;
    QLineEdit *sValue;
    QWidget *p;
    QLabel *pName;
    QLineEdit *pValue;
    QWidget *a;
    QLabel *aName;
    QLineEdit *aValue;
    QWidget *x;
    QLabel *xName;
    QLineEdit *xValue;
    QWidget *y;
    QLabel *yName;
    QLineEdit *yValue;
    QGroupBox *memory;
    QListWidget *memoryView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *resetCPU;
    QPushButton *stepCPU;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DendyDebugger)
    {
        if (DendyDebugger->objectName().isEmpty())
            DendyDebugger->setObjectName(QStringLiteral("DendyDebugger"));
        DendyDebugger->resize(480, 480);
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(10);
        DendyDebugger->setFont(font);
        DendyDebugger->setContextMenuPolicy(Qt::DefaultContextMenu);
        DendyDebugger->setWindowOpacity(1);
        DendyDebugger->setSizeGripEnabled(false);
        DendyDebugger->setModal(false);
        verticalLayoutWidget = new QWidget(DendyDebugger);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 462, 431));
        layout = new QVBoxLayout(verticalLayoutWidget);
        layout->setObjectName(QStringLiteral("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        registers = new QGroupBox(verticalLayoutWidget);
        registers->setObjectName(QStringLiteral("registers"));
        registers->setMinimumSize(QSize(460, 150));
        registers->setMaximumSize(QSize(460, 150));
        QFont font1;
        font1.setPointSize(15);
        registers->setFont(font1);
        registers->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        registers->setFlat(true);
        registers->setCheckable(false);
        pc = new QWidget(registers);
        pc->setObjectName(QStringLiteral("pc"));
        pc->setGeometry(QRect(0, 30, 120, 40));
        pc->setMinimumSize(QSize(120, 40));
        pc->setMaximumSize(QSize(120, 40));
        pc->setAutoFillBackground(false);
        pcName = new QLabel(pc);
        pcName->setObjectName(QStringLiteral("pcName"));
        pcName->setGeometry(QRect(0, 0, 60, 40));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        pcName->setFont(font2);
        pcName->setAlignment(Qt::AlignCenter);
        pcValue = new QLineEdit(pc);
        pcValue->setObjectName(QStringLiteral("pcValue"));
        pcValue->setGeometry(QRect(60, 0, 60, 40));
        QFont font3;
        font3.setPointSize(12);
        pcValue->setFont(font3);
        pcValue->setMaxLength(5);
        pcValue->setFrame(true);
        pcValue->setAlignment(Qt::AlignCenter);
        pcValue->setReadOnly(true);
        flags = new QGroupBox(registers);
        flags->setObjectName(QStringLiteral("flags"));
        flags->setGeometry(QRect(120, 30, 220, 120));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(flags->sizePolicy().hasHeightForWidth());
        flags->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setPointSize(14);
        flags->setFont(font4);
        flags->setAlignment(Qt::AlignCenter);
        flags->setFlat(true);
        gridLayoutWidget = new QWidget(flags);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 25, 201, 91));
        values = new QGridLayout(gridLayoutWidget);
        values->setObjectName(QStringLiteral("values"));
        values->setContentsMargins(0, 0, 0, 0);
        N = new QCheckBox(gridLayoutWidget);
        N->setObjectName(QStringLiteral("N"));
        N->setMaximumSize(QSize(15, 15));

        values->addWidget(N, 1, 0, 1, 1);

        checkBox_3 = new QCheckBox(gridLayoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setEnabled(false);
        checkBox_3->setMaximumSize(QSize(15, 15));
        checkBox_3->setCheckable(true);
        checkBox_3->setChecked(true);

        values->addWidget(checkBox_3, 1, 2, 1, 1);

        V = new QCheckBox(gridLayoutWidget);
        V->setObjectName(QStringLiteral("V"));
        V->setMaximumSize(QSize(15, 15));

        values->addWidget(V, 1, 1, 1, 1);

        B = new QCheckBox(gridLayoutWidget);
        B->setObjectName(QStringLiteral("B"));
        B->setEnabled(true);
        B->setMaximumSize(QSize(15, 15));
        B->setCheckable(false);

        values->addWidget(B, 1, 3, 1, 1);

        D = new QCheckBox(gridLayoutWidget);
        D->setObjectName(QStringLiteral("D"));
        D->setMaximumSize(QSize(15, 15));

        values->addWidget(D, 1, 4, 1, 1);

        I = new QCheckBox(gridLayoutWidget);
        I->setObjectName(QStringLiteral("I"));
        I->setMaximumSize(QSize(15, 15));

        values->addWidget(I, 1, 5, 1, 1);

        Z = new QCheckBox(gridLayoutWidget);
        Z->setObjectName(QStringLiteral("Z"));
        Z->setMaximumSize(QSize(15, 15));

        values->addWidget(Z, 1, 6, 1, 1);

        C = new QCheckBox(gridLayoutWidget);
        C->setObjectName(QStringLiteral("C"));
        C->setMaximumSize(QSize(15, 15));

        values->addWidget(C, 1, 7, 1, 1);

        flagN = new QLabel(gridLayoutWidget);
        flagN->setObjectName(QStringLiteral("flagN"));
        flagN->setMaximumSize(QSize(15, 30));
        flagN->setAlignment(Qt::AlignCenter);

        values->addWidget(flagN, 0, 0, 1, 1);

        flagV = new QLabel(gridLayoutWidget);
        flagV->setObjectName(QStringLiteral("flagV"));
        flagV->setMaximumSize(QSize(15, 30));
        flagV->setAlignment(Qt::AlignCenter);

        values->addWidget(flagV, 0, 1, 1, 1);

        flagD = new QLabel(gridLayoutWidget);
        flagD->setObjectName(QStringLiteral("flagD"));
        flagD->setMaximumSize(QSize(15, 30));
        flagD->setAlignment(Qt::AlignCenter);

        values->addWidget(flagD, 0, 4, 1, 1);

        flagI = new QLabel(gridLayoutWidget);
        flagI->setObjectName(QStringLiteral("flagI"));
        flagI->setMaximumSize(QSize(15, 30));
        flagI->setAlignment(Qt::AlignCenter);

        values->addWidget(flagI, 0, 5, 1, 1);

        flagZ = new QLabel(gridLayoutWidget);
        flagZ->setObjectName(QStringLiteral("flagZ"));
        flagZ->setMaximumSize(QSize(15, 30));
        flagZ->setAlignment(Qt::AlignCenter);

        values->addWidget(flagZ, 0, 6, 1, 1);

        flagC = new QLabel(gridLayoutWidget);
        flagC->setObjectName(QStringLiteral("flagC"));
        flagC->setMaximumSize(QSize(15, 30));
        flagC->setAlignment(Qt::AlignCenter);

        values->addWidget(flagC, 0, 7, 1, 1);

        flagB = new QLabel(gridLayoutWidget);
        flagB->setObjectName(QStringLiteral("flagB"));
        flagB->setMaximumSize(QSize(15, 30));
        flagB->setAlignment(Qt::AlignCenter);

        values->addWidget(flagB, 0, 3, 1, 1);

        s = new QWidget(registers);
        s->setObjectName(QStringLiteral("s"));
        s->setGeometry(QRect(0, 70, 120, 40));
        s->setMinimumSize(QSize(120, 40));
        s->setMaximumSize(QSize(120, 40));
        s->setAutoFillBackground(false);
        sName = new QLabel(s);
        sName->setObjectName(QStringLiteral("sName"));
        sName->setGeometry(QRect(0, 0, 60, 40));
        sName->setFont(font2);
        sName->setAlignment(Qt::AlignCenter);
        sValue = new QLineEdit(s);
        sValue->setObjectName(QStringLiteral("sValue"));
        sValue->setGeometry(QRect(60, 0, 30, 40));
        sValue->setFont(font3);
        sValue->setMaxLength(2);
        sValue->setFrame(true);
        sValue->setCursorPosition(2);
        sValue->setAlignment(Qt::AlignCenter);
        sValue->setReadOnly(true);
        p = new QWidget(registers);
        p->setObjectName(QStringLiteral("p"));
        p->setGeometry(QRect(0, 110, 120, 40));
        p->setMinimumSize(QSize(120, 40));
        p->setMaximumSize(QSize(120, 40));
        p->setAutoFillBackground(false);
        pName = new QLabel(p);
        pName->setObjectName(QStringLiteral("pName"));
        pName->setGeometry(QRect(0, 0, 60, 40));
        pName->setFont(font2);
        pName->setAlignment(Qt::AlignCenter);
        pValue = new QLineEdit(p);
        pValue->setObjectName(QStringLiteral("pValue"));
        pValue->setGeometry(QRect(60, 0, 30, 40));
        pValue->setFont(font3);
        pValue->setMaxLength(2);
        pValue->setFrame(true);
        pValue->setCursorPosition(2);
        pValue->setAlignment(Qt::AlignCenter);
        pValue->setReadOnly(true);
        a = new QWidget(registers);
        a->setObjectName(QStringLiteral("a"));
        a->setGeometry(QRect(340, 30, 120, 40));
        a->setMinimumSize(QSize(120, 40));
        a->setMaximumSize(QSize(120, 40));
        a->setAutoFillBackground(false);
        aName = new QLabel(a);
        aName->setObjectName(QStringLiteral("aName"));
        aName->setGeometry(QRect(0, 0, 60, 40));
        aName->setFont(font2);
        aName->setAlignment(Qt::AlignCenter);
        aValue = new QLineEdit(a);
        aValue->setObjectName(QStringLiteral("aValue"));
        aValue->setGeometry(QRect(60, 0, 30, 40));
        aValue->setFont(font3);
        aValue->setMaxLength(2);
        aValue->setFrame(true);
        aValue->setCursorPosition(2);
        aValue->setAlignment(Qt::AlignCenter);
        aValue->setReadOnly(true);
        x = new QWidget(registers);
        x->setObjectName(QStringLiteral("x"));
        x->setGeometry(QRect(340, 70, 120, 40));
        x->setMinimumSize(QSize(120, 40));
        x->setMaximumSize(QSize(120, 40));
        x->setAutoFillBackground(false);
        xName = new QLabel(x);
        xName->setObjectName(QStringLiteral("xName"));
        xName->setGeometry(QRect(0, 0, 60, 40));
        xName->setFont(font2);
        xName->setAlignment(Qt::AlignCenter);
        xValue = new QLineEdit(x);
        xValue->setObjectName(QStringLiteral("xValue"));
        xValue->setGeometry(QRect(60, 0, 30, 40));
        xValue->setFont(font3);
        xValue->setMaxLength(2);
        xValue->setFrame(true);
        xValue->setCursorPosition(2);
        xValue->setAlignment(Qt::AlignCenter);
        xValue->setReadOnly(true);
        y = new QWidget(registers);
        y->setObjectName(QStringLiteral("y"));
        y->setGeometry(QRect(340, 110, 120, 40));
        y->setMinimumSize(QSize(120, 40));
        y->setMaximumSize(QSize(120, 40));
        y->setAutoFillBackground(false);
        yName = new QLabel(y);
        yName->setObjectName(QStringLiteral("yName"));
        yName->setGeometry(QRect(0, 0, 60, 40));
        yName->setFont(font2);
        yName->setAlignment(Qt::AlignCenter);
        yValue = new QLineEdit(y);
        yValue->setObjectName(QStringLiteral("yValue"));
        yValue->setGeometry(QRect(60, 0, 30, 40));
        yValue->setFont(font3);
        yValue->setMaxLength(2);
        yValue->setFrame(true);
        yValue->setCursorPosition(2);
        yValue->setAlignment(Qt::AlignCenter);
        yValue->setReadOnly(true);

        layout->addWidget(registers);

        memory = new QGroupBox(verticalLayoutWidget);
        memory->setObjectName(QStringLiteral("memory"));
        memory->setFont(font1);
        memory->setFlat(true);
        memory->setCheckable(false);
        memoryView = new QListWidget(memory);
        memoryView->setObjectName(QStringLiteral("memoryView"));
        memoryView->setGeometry(QRect(0, 21, 461, 251));
        QFont font5;
        font5.setBold(true);
        font5.setWeight(75);
        memoryView->setFont(font5);
        memoryView->setAlternatingRowColors(true);
        memoryView->setTextElideMode(Qt::ElideRight);

        layout->addWidget(memory);

        horizontalLayoutWidget = new QWidget(DendyDebugger);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 440, 461, 36));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        resetCPU = new QPushButton(horizontalLayoutWidget);
        resetCPU->setObjectName(QStringLiteral("resetCPU"));

        horizontalLayout->addWidget(resetCPU);

        stepCPU = new QPushButton(horizontalLayoutWidget);
        stepCPU->setObjectName(QStringLiteral("stepCPU"));

        horizontalLayout->addWidget(stepCPU);

        buttonBox = new QDialogButtonBox(horizontalLayoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(false);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(DendyDebugger);
        QObject::connect(buttonBox, SIGNAL(accepted()), DendyDebugger, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DendyDebugger, SLOT(reject()));

        QMetaObject::connectSlotsByName(DendyDebugger);
    } // setupUi

    void retranslateUi(QDialog *DendyDebugger)
    {
        DendyDebugger->setWindowTitle(QApplication::translate("DendyDebugger", "Dendy debugger", 0));
        registers->setTitle(QApplication::translate("DendyDebugger", "Registers", 0));
        pcName->setText(QApplication::translate("DendyDebugger", "PC:", 0));
        pcValue->setText(QApplication::translate("DendyDebugger", "00:00", 0));
        flags->setTitle(QApplication::translate("DendyDebugger", "Flags:", 0));
        N->setText(QString());
        checkBox_3->setText(QString());
        V->setText(QString());
        B->setText(QString());
        D->setText(QString());
        I->setText(QString());
        Z->setText(QString());
        C->setText(QString());
        flagN->setText(QApplication::translate("DendyDebugger", "N", 0));
        flagV->setText(QApplication::translate("DendyDebugger", "V", 0));
        flagD->setText(QApplication::translate("DendyDebugger", "D", 0));
        flagI->setText(QApplication::translate("DendyDebugger", "I", 0));
        flagZ->setText(QApplication::translate("DendyDebugger", "Z", 0));
        flagC->setText(QApplication::translate("DendyDebugger", "C", 0));
        flagB->setText(QApplication::translate("DendyDebugger", "B", 0));
        sName->setText(QApplication::translate("DendyDebugger", "S:", 0));
        sValue->setText(QApplication::translate("DendyDebugger", "5B", 0));
        pName->setText(QApplication::translate("DendyDebugger", "P:", 0));
        pValue->setText(QApplication::translate("DendyDebugger", "06", 0));
        aName->setText(QApplication::translate("DendyDebugger", "A:", 0));
        aValue->setText(QApplication::translate("DendyDebugger", "07", 0));
        xName->setText(QApplication::translate("DendyDebugger", "X:", 0));
        xValue->setText(QApplication::translate("DendyDebugger", "00", 0));
        yName->setText(QApplication::translate("DendyDebugger", "Y:", 0));
        yValue->setText(QApplication::translate("DendyDebugger", "00", 0));
        memory->setTitle(QApplication::translate("DendyDebugger", "Memory", 0));
        resetCPU->setText(QApplication::translate("DendyDebugger", "\320\241\320\261\321\200\320\276\321\201", 0));
        stepCPU->setText(QApplication::translate("DendyDebugger", "\320\250\320\260\320\263", 0));
    } // retranslateUi

};

namespace Ui {
    class DendyDebugger: public Ui_DendyDebugger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DENDYDEBUGGER_H
