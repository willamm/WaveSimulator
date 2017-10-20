/********************************************************************************
** Form generated from reading UI file 'WaveSim.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaveSimClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *WaveSimClass)
    {
        if (WaveSimClass->objectName().isEmpty())
            WaveSimClass->setObjectName(QStringLiteral("WaveSimClass"));
        WaveSimClass->resize(1600, 800);
        actionNew = new QAction(WaveSimClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(WaveSimClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(WaveSimClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(WaveSimClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(WaveSimClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WaveSimClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WaveSimClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        WaveSimClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(WaveSimClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WaveSimClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(WaveSimClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WaveSimClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);

        retranslateUi(WaveSimClass);
        QObject::connect(actionExit, SIGNAL(triggered()), WaveSimClass, SLOT(close()));

        QMetaObject::connectSlotsByName(WaveSimClass);
    } // setupUi

    void retranslateUi(QMainWindow *WaveSimClass)
    {
        WaveSimClass->setWindowTitle(QApplication::translate("WaveSimClass", "WaveSim", Q_NULLPTR));
        actionNew->setText(QApplication::translate("WaveSimClass", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("WaveSimClass", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("WaveSimClass", "Save", Q_NULLPTR));
        actionExit->setText(QApplication::translate("WaveSimClass", "Exit", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("WaveSimClass", "File", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("WaveSimClass", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaveSimClass: public Ui_WaveSimClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVESIM_H
