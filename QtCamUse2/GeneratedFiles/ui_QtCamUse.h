/********************************************************************************
** Form generated from reading UI file 'QtCamUse.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCAMUSE_H
#define UI_QTCAMUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCamUseClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *gvMain;
    QFrame *res_frame;
    QGroupBox *groupBox_6;
    QComboBox *res_combobox;
    QLabel *label_25;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtCamUseClass)
    {
        if (QtCamUseClass->objectName().isEmpty())
            QtCamUseClass->setObjectName(QStringLiteral("QtCamUseClass"));
        QtCamUseClass->resize(1247, 688);
        centralWidget = new QWidget(QtCamUseClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gvMain = new QGraphicsView(centralWidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));
        gvMain->setGeometry(QRect(10, 0, 800, 600));
        res_frame = new QFrame(centralWidget);
        res_frame->setObjectName(QStringLiteral("res_frame"));
        res_frame->setGeometry(QRect(830, 20, 250, 45));
        res_frame->setFrameShape(QFrame::StyledPanel);
        res_frame->setFrameShadow(QFrame::Raised);
        groupBox_6 = new QGroupBox(res_frame);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 0, 250, 45));
        res_combobox = new QComboBox(groupBox_6);
        res_combobox->setObjectName(QStringLiteral("res_combobox"));
        res_combobox->setGeometry(QRect(5, 7, 240, 30));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(840, 10, 54, 12));
        QtCamUseClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtCamUseClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtCamUseClass->setStatusBar(statusBar);

        retranslateUi(QtCamUseClass);

        QMetaObject::connectSlotsByName(QtCamUseClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtCamUseClass)
    {
        QtCamUseClass->setWindowTitle(QApplication::translate("QtCamUseClass", "QtCamUse", Q_NULLPTR));
        groupBox_6->setTitle(QString());
        label_25->setText(QApplication::translate("QtCamUseClass", "\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUseClass: public Ui_QtCamUseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_H
