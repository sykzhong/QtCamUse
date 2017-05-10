/********************************************************************************
** Form generated from reading UI file 'QtCamUse_move.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCAMUSE_MOVE_H
#define UI_QTCAMUSE_MOVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCamUse_moveClass
{
public:
    QWidget *centralwidget;
    QGraphicsView *gvMain;
    QFrame *frame;
    QPushButton *pushButton_n;
    QPushButton *pushButton_back_to_mainwindow;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtCamUse_moveClass)
    {
        if (QtCamUse_moveClass->objectName().isEmpty())
            QtCamUse_moveClass->setObjectName(QStringLiteral("QtCamUse_moveClass"));
        QtCamUse_moveClass->resize(1120, 647);
        centralwidget = new QWidget(QtCamUse_moveClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gvMain = new QGraphicsView(centralwidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));
        gvMain->setGeometry(QRect(10, 0, 800, 600));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(850, 70, 191, 91));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_n = new QPushButton(frame);
        pushButton_n->setObjectName(QStringLiteral("pushButton_n"));
        pushButton_n->setGeometry(QRect(100, 30, 75, 23));
        pushButton_back_to_mainwindow = new QPushButton(frame);
        pushButton_back_to_mainwindow->setObjectName(QStringLiteral("pushButton_back_to_mainwindow"));
        pushButton_back_to_mainwindow->setGeometry(QRect(10, 30, 75, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(850, 50, 81, 21));
        QtCamUse_moveClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(QtCamUse_moveClass);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        QtCamUse_moveClass->setStatusBar(statusbar);

        retranslateUi(QtCamUse_moveClass);

        QMetaObject::connectSlotsByName(QtCamUse_moveClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtCamUse_moveClass)
    {
        QtCamUse_moveClass->setWindowTitle(QApplication::translate("QtCamUse_moveClass", "MainWindow", Q_NULLPTR));
        pushButton_n->setText(QApplication::translate("QtCamUse_moveClass", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
        pushButton_back_to_mainwindow->setText(QApplication::translate("QtCamUse_moveClass", "\344\270\212\344\270\200\346\255\245", Q_NULLPTR));
        label->setText(QApplication::translate("QtCamUse_moveClass", "\350\216\267\345\217\226\346\250\241\346\235\277\345\233\276\345\203\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUse_moveClass: public Ui_QtCamUse_moveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_MOVE_H
