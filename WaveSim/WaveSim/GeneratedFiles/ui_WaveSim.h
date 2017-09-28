/********************************************************************************
** Form generated from reading UI file 'WaveSim.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
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
    QPushButton *pushButton;
    QTreeView *treeView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *WaveSimClass)
    {
        if (WaveSimClass->objectName().isEmpty())
            WaveSimClass->setObjectName(QStringLiteral("WaveSimClass"));
        WaveSimClass->resize(894, 716);
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
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 290, 75, 23));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 80, 256, 551));
        WaveSimClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WaveSimClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 894, 31));
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
        WaveSimClass->setWindowTitle(QApplication::translate("WaveSimClass", "WaveSim", 0));
        actionNew->setText(QApplication::translate("WaveSimClass", "New", 0));
        actionOpen->setText(QApplication::translate("WaveSimClass", "Open", 0));
        actionSave->setText(QApplication::translate("WaveSimClass", "Save", 0));
        actionExit->setText(QApplication::translate("WaveSimClass", "Exit", 0));
        pushButton->setText(QApplication::translate("WaveSimClass", "Close", 0));
        menuFile->setTitle(QApplication::translate("WaveSimClass", "File", 0));
        menuAbout->setTitle(QApplication::translate("WaveSimClass", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class WaveSimClass: public Ui_WaveSimClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVESIM_H
