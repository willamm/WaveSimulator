/********************************************************************************
** Form generated from reading UI file 'WaveSim.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVESIM_H
#define UI_WAVESIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaveSimClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WaveSimClass)
    {
        if (WaveSimClass->objectName().isEmpty())
            WaveSimClass->setObjectName(QStringLiteral("WaveSimClass"));
        WaveSimClass->resize(483, 370);
        centralWidget = new QWidget(WaveSimClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WaveSimClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WaveSimClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 483, 21));
        WaveSimClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WaveSimClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WaveSimClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WaveSimClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WaveSimClass->setStatusBar(statusBar);

        retranslateUi(WaveSimClass);

        QMetaObject::connectSlotsByName(WaveSimClass);
    } // setupUi

    void retranslateUi(QMainWindow *WaveSimClass)
    {
        WaveSimClass->setWindowTitle(QApplication::translate("WaveSimClass", "WaveSim", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaveSimClass: public Ui_WaveSimClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVESIM_H
