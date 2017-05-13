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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QFrame *frame_template;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_get_template_save;
    QPushButton *pushButton_get_template_load;
    QLabel *label_4;
    QLineEdit *lineEdit_get_template_path;
    QLabel *label;
    QPushButton *pushButton_back_to_mainwindow;
    QLabel *label_2;
    QFrame *frame_back;
    QGroupBox *groupBox;
    QPushButton *pushButton_get_back_save;
    QLabel *label_3;
    QLineEdit *lineEdit_get_back_path;
    QPushButton *pushButton_get_back_load;
    QFrame *frame;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_image_process;
    QLabel *label_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtCamUse_moveClass)
    {
        if (QtCamUse_moveClass->objectName().isEmpty())
            QtCamUse_moveClass->setObjectName(QStringLiteral("QtCamUse_moveClass"));
        QtCamUse_moveClass->resize(1120, 647);
        QtCamUse_moveClass->setAcceptDrops(false);
        centralwidget = new QWidget(QtCamUse_moveClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gvMain = new QGraphicsView(centralwidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));
        gvMain->setGeometry(QRect(10, 0, 800, 600));
        frame_template = new QFrame(centralwidget);
        frame_template->setObjectName(QStringLiteral("frame_template"));
        frame_template->setGeometry(QRect(820, 150, 281, 81));
        frame_template->setFrameShape(QFrame::StyledPanel);
        frame_template->setFrameShadow(QFrame::Raised);
        groupBox_2 = new QGroupBox(frame_template);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 281, 81));
        pushButton_get_template_save = new QPushButton(groupBox_2);
        pushButton_get_template_save->setObjectName(QStringLiteral("pushButton_get_template_save"));
        pushButton_get_template_save->setGeometry(QRect(50, 10, 75, 23));
        pushButton_get_template_load = new QPushButton(groupBox_2);
        pushButton_get_template_load->setObjectName(QStringLiteral("pushButton_get_template_load"));
        pushButton_get_template_load->setGeometry(QRect(160, 10, 75, 23));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 54, 54, 12));
        lineEdit_get_template_path = new QLineEdit(groupBox_2);
        lineEdit_get_template_path->setObjectName(QStringLiteral("lineEdit_get_template_path"));
        lineEdit_get_template_path->setEnabled(true);
        lineEdit_get_template_path->setGeometry(QRect(80, 50, 181, 20));
        lineEdit_get_template_path->setAcceptDrops(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(820, 130, 121, 21));
        pushButton_back_to_mainwindow = new QPushButton(centralwidget);
        pushButton_back_to_mainwindow->setObjectName(QStringLiteral("pushButton_back_to_mainwindow"));
        pushButton_back_to_mainwindow->setGeometry(QRect(850, 410, 61, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(820, 10, 121, 16));
        frame_back = new QFrame(centralwidget);
        frame_back->setObjectName(QStringLiteral("frame_back"));
        frame_back->setGeometry(QRect(820, 30, 281, 81));
        frame_back->setFrameShape(QFrame::StyledPanel);
        frame_back->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(frame_back);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 281, 81));
        pushButton_get_back_save = new QPushButton(groupBox);
        pushButton_get_back_save->setObjectName(QStringLiteral("pushButton_get_back_save"));
        pushButton_get_back_save->setGeometry(QRect(50, 10, 75, 23));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 53, 54, 12));
        lineEdit_get_back_path = new QLineEdit(groupBox);
        lineEdit_get_back_path->setObjectName(QStringLiteral("lineEdit_get_back_path"));
        lineEdit_get_back_path->setEnabled(true);
        lineEdit_get_back_path->setGeometry(QRect(80, 50, 181, 20));
        lineEdit_get_back_path->setAcceptDrops(true);
        pushButton_get_back_load = new QPushButton(groupBox);
        pushButton_get_back_load->setObjectName(QStringLiteral("pushButton_get_back_load"));
        pushButton_get_back_load->setGeometry(QRect(160, 10, 75, 23));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(820, 260, 281, 81));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 281, 81));
        pushButton_image_process = new QPushButton(groupBox_3);
        pushButton_image_process->setObjectName(QStringLiteral("pushButton_image_process"));
        pushButton_image_process->setGeometry(QRect(50, 30, 75, 23));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(830, 250, 121, 16));
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
        groupBox_2->setTitle(QString());
        pushButton_get_template_save->setText(QApplication::translate("QtCamUse_moveClass", "\350\216\267\345\217\226\345\271\266\345\212\240\350\275\275", Q_NULLPTR));
        pushButton_get_template_load->setText(QApplication::translate("QtCamUse_moveClass", "\345\212\240\350\275\275", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtCamUse_moveClass", "\345\233\276\347\211\207\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("QtCamUse_moveClass", "\347\254\254\344\272\214\351\203\250\357\274\232\350\216\267\345\217\226\346\250\241\346\235\277\345\233\276\345\203\217", Q_NULLPTR));
        pushButton_back_to_mainwindow->setText(QApplication::translate("QtCamUse_moveClass", "\350\277\224\345\233\236", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtCamUse_moveClass", "\347\254\254\344\270\200\346\255\245\357\274\232\350\216\267\345\217\226\350\203\214\346\231\257\345\233\276\345\203\217", Q_NULLPTR));
        groupBox->setTitle(QString());
        pushButton_get_back_save->setText(QApplication::translate("QtCamUse_moveClass", "\350\216\267\345\217\226\345\271\266\344\277\235\345\255\230", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtCamUse_moveClass", "\345\233\276\347\211\207\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton_get_back_load->setText(QApplication::translate("QtCamUse_moveClass", "\345\212\240\350\275\275", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        pushButton_image_process->setText(QApplication::translate("QtCamUse_moveClass", "\345\274\200\345\247\213\345\244\204\347\220\206", Q_NULLPTR));
        label_5->setText(QApplication::translate("QtCamUse_moveClass", "\347\254\254\344\270\211\346\255\245\357\274\232\346\250\241\346\235\277\345\233\276\345\203\217\346\223\215\344\275\234", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUse_moveClass: public Ui_QtCamUse_moveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_MOVE_H
