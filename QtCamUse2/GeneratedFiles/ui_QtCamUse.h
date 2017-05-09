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
#include <QtWidgets/QCheckBox>
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
    QRadioButton *exposure_mode_auto;
    QRadioButton *exposure_mode_manual;
    QFrame *exposure_manual;
    QGroupBox *groupBox_3;
    QSlider *horizontalSlider_gain;
    QLabel *label_2;
    QSpinBox *spinBox_gain;
    QLabel *label_3;
    QSlider *horizontalSlider_exposure_time;
    QLineEdit *lineEdit_exposure_time;
    QLabel *label;
    QFrame *wb_frame;
    QPushButton *pushButton_AWB_once;
    QLabel *label_4;
    QFrame *isp_frame;
    QGroupBox *groupBox_4;
    QCheckBox *checkBox_isp_h;
    QCheckBox *checkBox_isp_v;
    QLabel *label_5;
    QFrame *para_frame;
    QGroupBox *groupBox_5;
    QRadioButton *radioButton_para_A;
    QRadioButton *radioButton_para_B;
    QRadioButton *radioButton_para_C;
    QRadioButton *radioButton_para_D;
    QPushButton *pushButton_para_save;
    QPushButton *pushButton_para_default;
    QPushButton *pushButton_para_load;
    QLabel *label_6;
    QPushButton *pushButton_next_move;
    QPushButton *pushButton_back;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtCamUseClass)
    {
        if (QtCamUseClass->objectName().isEmpty())
            QtCamUseClass->setObjectName(QStringLiteral("QtCamUseClass"));
        QtCamUseClass->resize(1120, 647);
        centralWidget = new QWidget(QtCamUseClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gvMain = new QGraphicsView(centralWidget);
        gvMain->setObjectName(QStringLiteral("gvMain"));
        gvMain->setGeometry(QRect(10, 0, 800, 600));
        res_frame = new QFrame(centralWidget);
        res_frame->setObjectName(QStringLiteral("res_frame"));
        res_frame->setGeometry(QRect(820, 140, 161, 45));
        res_frame->setFrameShape(QFrame::StyledPanel);
        res_frame->setFrameShadow(QFrame::Raised);
        groupBox_6 = new QGroupBox(res_frame);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 0, 161, 45));
        res_combobox = new QComboBox(groupBox_6);
        res_combobox->setObjectName(QStringLiteral("res_combobox"));
        res_combobox->setGeometry(QRect(5, 7, 151, 31));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(830, 130, 54, 12));
        trigger_fram = new QFrame(centralWidget);
        trigger_fram->setObjectName(QStringLiteral("trigger_fram"));
        trigger_fram->setGeometry(QRect(990, 10, 121, 111));
        trigger_fram->setFrameShape(QFrame::StyledPanel);
        trigger_fram->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(trigger_fram);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 121, 111));
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
        exp_frame->setGeometry(QRect(820, 220, 241, 141));
        exp_frame->setFrameShape(QFrame::StyledPanel);
        exp_frame->setFrameShadow(QFrame::Raised);
        groupBox_2 = new QGroupBox(exp_frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 10, 131, 41));
        exposure_mode_auto = new QRadioButton(groupBox_2);
        exposure_mode_auto->setObjectName(QStringLiteral("exposure_mode_auto"));
        exposure_mode_auto->setGeometry(QRect(10, 10, 89, 16));
        exposure_mode_manual = new QRadioButton(groupBox_2);
        exposure_mode_manual->setObjectName(QStringLiteral("exposure_mode_manual"));
        exposure_mode_manual->setGeometry(QRect(60, 10, 61, 16));
        exposure_manual = new QFrame(exp_frame);
        exposure_manual->setObjectName(QStringLiteral("exposure_manual"));
        exposure_manual->setGeometry(QRect(0, 60, 241, 71));
        exposure_manual->setFrameShape(QFrame::StyledPanel);
        exposure_manual->setFrameShadow(QFrame::Raised);
        groupBox_3 = new QGroupBox(exposure_manual);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 241, 81));
        horizontalSlider_gain = new QSlider(groupBox_3);
        horizontalSlider_gain->setObjectName(QStringLiteral("horizontalSlider_gain"));
        horizontalSlider_gain->setGeometry(QRect(60, 10, 121, 19));
        horizontalSlider_gain->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(9, 13, 54, 12));
        spinBox_gain = new QSpinBox(groupBox_3);
        spinBox_gain->setObjectName(QStringLiteral("spinBox_gain"));
        spinBox_gain->setGeometry(QRect(190, 10, 42, 22));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(8, 43, 54, 12));
        horizontalSlider_exposure_time = new QSlider(groupBox_3);
        horizontalSlider_exposure_time->setObjectName(QStringLiteral("horizontalSlider_exposure_time"));
        horizontalSlider_exposure_time->setGeometry(QRect(60, 40, 121, 19));
        horizontalSlider_exposure_time->setOrientation(Qt::Horizontal);
        lineEdit_exposure_time = new QLineEdit(groupBox_3);
        lineEdit_exposure_time->setObjectName(QStringLiteral("lineEdit_exposure_time"));
        lineEdit_exposure_time->setGeometry(QRect(190, 40, 41, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(830, 210, 54, 12));
        wb_frame = new QFrame(centralWidget);
        wb_frame->setObjectName(QStringLiteral("wb_frame"));
        wb_frame->setGeometry(QRect(820, 20, 161, 35));
        wb_frame->setFrameShape(QFrame::StyledPanel);
        wb_frame->setFrameShadow(QFrame::Raised);
        pushButton_AWB_once = new QPushButton(wb_frame);
        pushButton_AWB_once->setObjectName(QStringLiteral("pushButton_AWB_once"));
        pushButton_AWB_once->setGeometry(QRect(5, 7, 151, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(830, 10, 71, 16));
        isp_frame = new QFrame(centralWidget);
        isp_frame->setObjectName(QStringLiteral("isp_frame"));
        isp_frame->setGeometry(QRect(820, 80, 161, 35));
        isp_frame->setFrameShape(QFrame::StyledPanel);
        isp_frame->setFrameShadow(QFrame::Raised);
        groupBox_4 = new QGroupBox(isp_frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 161, 35));
        checkBox_isp_h = new QCheckBox(groupBox_4);
        checkBox_isp_h->setObjectName(QStringLiteral("checkBox_isp_h"));
        checkBox_isp_h->setGeometry(QRect(10, 10, 71, 16));
        checkBox_isp_v = new QCheckBox(groupBox_4);
        checkBox_isp_v->setObjectName(QStringLiteral("checkBox_isp_v"));
        checkBox_isp_v->setGeometry(QRect(90, 10, 71, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(830, 70, 71, 16));
        para_frame = new QFrame(centralWidget);
        para_frame->setObjectName(QStringLiteral("para_frame"));
        para_frame->setGeometry(QRect(820, 380, 241, 91));
        para_frame->setFrameShape(QFrame::StyledPanel);
        para_frame->setFrameShadow(QFrame::Raised);
        groupBox_5 = new QGroupBox(para_frame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 10, 241, 71));
        radioButton_para_A = new QRadioButton(groupBox_5);
        radioButton_para_A->setObjectName(QStringLiteral("radioButton_para_A"));
        radioButton_para_A->setGeometry(QRect(10, 14, 31, 16));
        radioButton_para_B = new QRadioButton(groupBox_5);
        radioButton_para_B->setObjectName(QStringLiteral("radioButton_para_B"));
        radioButton_para_B->setGeometry(QRect(50, 14, 31, 16));
        radioButton_para_C = new QRadioButton(groupBox_5);
        radioButton_para_C->setObjectName(QStringLiteral("radioButton_para_C"));
        radioButton_para_C->setGeometry(QRect(10, 42, 31, 16));
        radioButton_para_D = new QRadioButton(groupBox_5);
        radioButton_para_D->setObjectName(QStringLiteral("radioButton_para_D"));
        radioButton_para_D->setGeometry(QRect(50, 40, 31, 20));
        pushButton_para_save = new QPushButton(groupBox_5);
        pushButton_para_save->setObjectName(QStringLiteral("pushButton_para_save"));
        pushButton_para_save->setGeometry(QRect(90, 10, 61, 23));
        pushButton_para_default = new QPushButton(groupBox_5);
        pushButton_para_default->setObjectName(QStringLiteral("pushButton_para_default"));
        pushButton_para_default->setGeometry(QRect(160, 10, 61, 23));
        pushButton_para_load = new QPushButton(groupBox_5);
        pushButton_para_load->setObjectName(QStringLiteral("pushButton_para_load"));
        pushButton_para_load->setGeometry(QRect(90, 40, 131, 23));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(830, 370, 54, 12));
        pushButton_next_move = new QPushButton(centralWidget);
        pushButton_next_move->setObjectName(QStringLiteral("pushButton_next_move"));
        pushButton_next_move->setGeometry(QRect(960, 520, 75, 23));
        pushButton_back = new QPushButton(centralWidget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setEnabled(false);
        pushButton_back->setGeometry(QRect(870, 520, 75, 23));
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
        exposure_mode_auto->setText(QApplication::translate("QtCamUseClass", "\350\207\252\345\212\250", Q_NULLPTR));
        exposure_mode_manual->setText(QApplication::translate("QtCamUseClass", "\346\211\213\345\212\250", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label_2->setText(QApplication::translate("QtCamUseClass", "\345\242\236\347\233\212", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtCamUseClass", "\346\233\235\345\205\211\346\227\266\351\227\264", Q_NULLPTR));
        label->setText(QApplication::translate("QtCamUseClass", "\346\233\235\345\205\211\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_AWB_once->setText(QApplication::translate("QtCamUseClass", "\344\270\200\351\224\256\347\231\275\345\271\263\350\241\241", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtCamUseClass", "ISP\351\242\234\350\211\262\345\244\204\347\220\206", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        checkBox_isp_h->setText(QApplication::translate("QtCamUseClass", "\346\260\264\345\271\263\351\225\234\345\203\217", Q_NULLPTR));
        checkBox_isp_v->setText(QApplication::translate("QtCamUseClass", "\345\236\202\347\233\264\351\225\234\345\203\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("QtCamUseClass", "ISP\345\233\276\345\203\217\345\244\204\347\220\206", Q_NULLPTR));
        groupBox_5->setTitle(QString());
        radioButton_para_A->setText(QApplication::translate("QtCamUseClass", "A", Q_NULLPTR));
        radioButton_para_B->setText(QApplication::translate("QtCamUseClass", "B", Q_NULLPTR));
        radioButton_para_C->setText(QApplication::translate("QtCamUseClass", "C", Q_NULLPTR));
        radioButton_para_D->setText(QApplication::translate("QtCamUseClass", "D", Q_NULLPTR));
        pushButton_para_save->setText(QApplication::translate("QtCamUseClass", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_para_default->setText(QApplication::translate("QtCamUseClass", "\351\273\230\350\256\244", Q_NULLPTR));
        pushButton_para_load->setText(QApplication::translate("QtCamUseClass", "\344\273\216\346\226\207\344\273\266\344\270\255\345\212\240\350\275\275", Q_NULLPTR));
        label_6->setText(QApplication::translate("QtCamUseClass", "\345\217\202\346\225\260\347\273\204", Q_NULLPTR));
        pushButton_next_move->setText(QApplication::translate("QtCamUseClass", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
        pushButton_back->setText(QApplication::translate("QtCamUseClass", "\344\270\212\344\270\200\346\255\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtCamUseClass: public Ui_QtCamUseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCAMUSE_H
