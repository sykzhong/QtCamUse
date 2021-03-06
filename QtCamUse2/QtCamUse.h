#ifndef QTCAMUSE_H
#define QTCAMUSE_H

#include <QMainWindow>
#include <QtGui>
#include "capturethread.h"

#include <qlabel.h>
#include <qgraphicslinearlayout.h>
#include <QRadioButton>

#include <windows.h>
#include "CameraApi.h"

#include "QtCamUse_move.h"

class QtCamUse_move;

typedef struct _WIDTH_HEIGHT{
    int     display_width;
    int     display_height;
    int     xOffsetFOV;
    int     yOffsetFOV;
    int     sensor_width;
    int     sensor_height;
    int     buffer_size;
}Width_Height;

namespace Ui {
    class QtCamUseClass;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *);
    int status;

protected:
    //void changeEvent(QEvent *e);

private:
    Ui::QtCamUseClass *ui;
    int init_SDK();
    int  GUI_init_parameter(int hCamera,tSdkCameraCapbility * pCameraInfo);
    int  GUI_init_Resolution(int hCamera,tSdkCameraCapbility * pCameraInfo);
    int  GUI_set_Resolution(int hCamera,tSdkCameraCapbility * pCameraInfo);
    int  GUI_init_exposure(int hCamera,tSdkCameraCapbility * pCameraInfo);
	int  GUI_init_isp(int hCamera, tSdkCameraCapbility * pCameraInfo);
	int  GUI_init_Trigger(int hCamera, tSdkCameraCapbility * pCameraInfo);
    int  GUI_init_WB(int hCamera,tSdkCameraCapbility * pCameraInfo);
//    int  GUI_init_mmap(int hCamera,tSdkCameraCapbility * pCameraInfo);
//    int  GUI_init_speed(int hCamera,tSdkCameraCapbility * pCameraInfo);
//    int  GUI_set_speed(int hCamera,tSdkCameraCapbility * pCameraInfo);
	

private slots:
	void Image_process(QImage img);
	void camera_statues();
	void slot_res_combobox_activated(int index);
	void slot_radioButton_collect_clicked(bool checked);
	void slot_radioButton_software_trigger_clicked(bool);
	void slot_radioButton_hardware_trigger_clicked(bool);
	void slot_software_trigger_once_button_clicked();
	void slot_exposure_mode_auto_clicked(bool);
	void slot_exposure_mode_manual_clicked(bool);
	void slot_horizontalSlider_gain_valueChanged(int);
	void slot_horizontalSlider_exposure_time_valueChanged(int);
	void on_pushButton_AWB_once_clicked();
	void on_checkBox_isp_h_clicked(bool checked);
	void on_checkBox_isp_v_clicked(bool checked);
	void on_radioButton_para_A_clicked(bool);
	void on_radioButton_para_B_clicked(bool);
	void on_radioButton_para_C_clicked(bool);
	void on_radioButton_para_D_clicked(bool);
	void on_pushButton_para_load_clicked();
	void on_pushButton_para_save_clicked();
	void on_pushButton_para_default_clicked();
	void on_pushButton_next_move_clicked();

	void slot_recover();
//    void on_radioButton_trigger_hardware_clicked(bool checked);
//    void on_radioButton_software_trigger_clicked(bool checked);
//    void on_radioButton_collect_clicked(bool checked);
//    void on_flashlight_l_clicked(bool checked);
//    void on_flashlight_h_clicked(bool checked);
//    void on_flashlight_manual_clicked(bool checked);
//    void on_flashlight_auto_clicked(bool checked);
//    void on_lineEdit_exposure_time_returnPressed();
//    void on_radioButton_raw_clicked();
//    void on_radioButton_bmp_clicked();
//    void on_pushButton_snap_catch_released();
//    void on_pushButton_snap_path_released();
//    void on_pushButton_para_load_released();
//    void on_pushButton_para_save_released();
//    void on_pushButton_para_acquiesce_released();
//    void on_radioButton_D_clicked(bool checked);
//    void on_radioButton_C_clicked(bool checked);
//    void on_radioButton_B_clicked(bool checked);
//    void on_horizontalSlider_isp_acutance_valueChanged(int value);
//    void on_checkBox_isp_v_clicked(bool checked);
//    void on_checkBox_isp_h_clicked(bool checked);
//    void on_contrast_horizontalSlider_valueChanged(int value);
//    void on_gamma_horizontalSlider_valueChanged(int value);
//    void on_horizontalSlider_saturation_valueChanged(int value);
//    void on_horizontalSlider_gain_b_valueChanged(int value);
//    void on_horizontalSlider_gain_g_valueChanged(int value);
//    void on_horizontalSlider_gain_r_valueChanged(int value);
//    void on_horizontalSlider_exposure_time_valueChanged(int value);
//    void on_horizontalSlider_gain_valueChanged(int value);
//    void on_AWB_once_button_released();
//    void on_res_combobox_activated(int index);

//    void on_radioButton_A_clicked(bool checked);
//    void on_exposure_mode_manual_clicked(bool checked);
//    void on_exposure_mode_auto_clicked(bool checked);
//    void on_radioButton_60HZ_clicked(bool checked);
//    void on_radioButton_50HZ_clicked(bool checked);
//    void on_software_trigger_once_button_clicked();
//    void on_flicker_checkBox_clicked(bool checked);
//    void on_AE_horizontalSlider_valueChanged(int value);
//
//    void radioChange();

private:
	QtCamUse_move *m_QtCamUse_move_window;
	bool b_child_window;		//判断是否有子窗口

	bool b_pause;				//暂停窗口运作进入下一操作环节的标识

    QTimer *m_timer;
    QLabel *m_camera_statuesFps;
    bool   exposure_time_lineedit_status;

    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_image_item;
    QRadioButton *radioButton_speed[3];

    CaptureThread *m_thread;
	
};

#endif // MAINWINDOW_H
