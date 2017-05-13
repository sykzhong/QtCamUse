/********************************************************************************
** Form generated from reading UI file 'QtCamUse_process.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCAMUSE_PROCESS_H
#define UI_QTCAMUSE_PROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCamUse_processClass
{
public:
    QWidget *centralwidget;
    QGraphicsView *gvMain;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtCamUse_processClass)
    {
        if (QtCamUse_processClass->objectName().isEmpty())
            QtCamUse_processClass->setObjectName(QStringLiteral("QtCamUse_processClass"));
        QtCamUse_processClass->resize(1120, 647);
        centralwidget = new QWidget(QtCamUse_processClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gvMain = new QGraphicsView(centralwidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));
        gvMain->setGeometry(QRect(10, 0, 800, 600));
        QtCamUse_processClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QtCamUse_processClass);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1120, 23));
        QtCamUse_processClass->setMenuBar(menubar);
        statusbar = new QStatusBar(QtCamUse_processClass);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        QtCamUse_processClass->setStatusBar(statusbar);

        retranslateUi(QtCamUse_processClass);

        QMetaObject::connectSlotsByName(QtCamUse_processClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtCamUse_processClass)
    {
        QtCamUse_processClass->setWindowTitle(QApplication::translate("QtCamUse_processClass", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUse_processClass: public Ui_QtCamUse_processClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_PROCESS_H
