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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
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
    QFrame *trigger_fram;
    QGroupBox *groupBox;
    QRadioButton *radioButton_collect;
    QRadioButton *radioButton_software_trigger;
    QPushButton *software_trigger_once_button;
    QRadioButton *radioButton_hardware_trigger;
    QFrame *exp_frame;
    QGroupBox *groupBox_2;
    QRadioButton *exposure_mod_auto;
    QRadioButton *exposure_mode_manual;
    QGroupBox *groupBox_3;
    QSlider *horizontalSlider_gain;
    QLabel *label_2;
    QSpinBox *AE_spinBox;
    QLabel *label_3;
    QSlider *horizontalSlider_exposure_time;
    QLineEdit *lineEdit_exposure_time;
    QLabel *label;
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
        res_frame->setGeometry(QRect(830, 20, 161, 45));
        res_frame->setFrameShape(QFrame::StyledPanel);
        res_frame->setFrameShadow(QFrame::Raised);
        groupBox_6 = new QGroupBox(res_frame);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 0, 161, 45));
        res_combobox = new QComboBox(groupBox_6);
        res_combobox->setObjectName(QStringLiteral("res_combobox"));
        res_combobox->setGeometry(QRect(5, 7, 151, 30));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(840, 10, 54, 12));
        trigger_fram = new QFrame(centralWidget);
        trigger_fram->setObjectName(QStringLiteral("trigger_fram"));
        trigger_fram->setGeometry(QRect(1000, 10, 141, 111));
        trigger_fram->setFrameShape(QFrame::StyledPanel);
        trigger_fram->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(trigger_fram);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 141, 111));
        radioButton_collect = new QRadioButton(groupBox);
        radioButton_collect->setObjectName(QStringLiteral("radioButton_collect"));
        radioButton_collect->setGeometry(QRect(10, 20, 89, 16));
        radioButton_software_trigger = new QRadioButton(groupBox);
        radioButton_software_trigger->setObjectName(QStringLiteral("radioButton_software_trigger"));
        radioButton_software_trigger->setGeometry(QRect(10, 40, 89, 16));
        software_trigger_once_button = new QPushButton(groupBox);
        software_trigger_once_button->setObjectName(QStringLiteral("software_trigger_once_button"));
        software_trigger_once_button->setGeometry(QRect(10, 80, 101, 23));
        radioButton_hardware_trigger = new QRadioButton(groupBox);
        radioButton_hardware_trigger->setObjectName(QStringLiteral("radioButton_hardware_trigger"));
        radioButton_hardware_trigger->setGeometry(QRect(10, 60, 89, 16));
        exp_frame = new QFrame(centralWidget);
        exp_frame->setObjectName(QStringLiteral("exp_frame"));
        exp_frame->setGeometry(QRect(830, 130, 291, 151));
        exp_frame->setFrameShape(QFrame::StyledPanel);
        exp_frame->setFrameShadow(QFrame::Raised);
        groupBox_2 = new QGroupBox(exp_frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 271, 41));
        exposure_mod_auto = new QRadioButton(groupBox_2);
        exposure_mod_auto->setObjectName(QStringLiteral("exposure_mod_auto"));
        exposure_mod_auto->setGeometry(QRect(10, 10, 89, 16));
        exposure_mode_manual = new QRadioButton(groupBox_2);
        exposure_mode_manual->setObjectName(QStringLiteral("exposure_mode_manual"));
        exposure_mode_manual->setGeometry(QRect(90, 10, 89, 16));
        groupBox_3 = new QGroupBox(exp_frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 60, 271, 81));
        horizontalSlider_gain = new QSlider(groupBox_3);
        horizontalSlider_gain->setObjectName(QStringLiteral("horizontalSlider_gain"));
        horizontalSlider_gain->setGeometry(QRect(60, 10, 151, 19));
        horizontalSlider_gain->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(9, 13, 54, 12));
        AE_spinBox = new QSpinBox(groupBox_3);
        AE_spinBox->setObjectName(QStringLiteral("AE_spinBox"));
        AE_spinBox->setGeometry(QRect(220, 10, 42, 22));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(8, 43, 54, 12));
        horizontalSlider_exposure_time = new QSlider(groupBox_3);
        horizontalSlider_exposure_time->setObjectName(QStringLiteral("horizontalSlider_exposure_time"));
        horizontalSlider_exposure_time->setGeometry(QRect(60, 40, 151, 19));
        horizontalSlider_exposure_time->setOrientation(Qt::Horizontal);
        lineEdit_exposure_time = new QLineEdit(groupBox_3);
        lineEdit_exposure_time->setObjectName(QStringLiteral("lineEdit_exposure_time"));
        lineEdit_exposure_time->setGeometry(QRect(220, 40, 41, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(840, 120, 54, 12));
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
        groupBox->setTitle(QApplication::translate("QtCamUseClass", "\350\247\246\345\217\221\346\250\241\345\274\217", Q_NULLPTR));
        radioButton_collect->setText(QApplication::translate("QtCamUseClass", "\350\277\236\347\273\255\351\207\207\351\233\206", Q_NULLPTR));
        radioButton_software_trigger->setText(QApplication::translate("QtCamUseClass", "\350\275\257\350\247\246\345\217\221", Q_NULLPTR));
        software_trigger_once_button->setText(QApplication::translate("QtCamUseClass", "\350\275\257\344\273\266\350\247\246\345\217\221\344\270\200\346\254\241", Q_NULLPTR));
        radioButton_hardware_trigger->setText(QApplication::translate("QtCamUseClass", "\347\241\254\344\273\266\345\207\272\345\217\221", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        exposure_mod_auto->setText(QApplication::translate("QtCamUseClass", "\350\207\252\345\212\250", Q_NULLPTR));
        exposure_mode_manual->setText(QApplication::translate("QtCamUseClass", "\346\211\213\345\212\250", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label_2->setText(QApplication::translate("QtCamUseClass", "\345\242\236\347\233\212", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtCamUseClass", "\346\233\235\345\205\211\346\227\266\351\227\264", Q_NULLPTR));
        label->setText(QApplication::translate("QtCamUseClass", "\346\233\235\345\205\211\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUseClass: public Ui_QtCamUseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_H
