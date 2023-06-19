#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#ifndef all_lib
#define all_lib
#include <QMainWindow>
#include <QtGui>
#include <ros/ros.h>
#include <QTimer>
#include <std_msgs/String.h>
#include <opencv4/opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include<QMouseEvent>
#include<QPixmap>
#include<QImage>
#include<QDebug>
#include <QCloseEvent>
#include<event.h>
#include <vector>
#include<math.h>
#include<QLabel>
//#include "namespaceali.h"
#endif

#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow2(QWidget *parent = nullptr);
  ~MainWindow2();

  void closeEvent(QCloseEvent *event);
signals:
    void dataToSend(int data);
    void dataopen(bool f);

public slots:
    void sendData() {
        int data = 42;
        emit dataToSend(data);
    }
    void not_hide()
    {
      bool f =true;
      emit dataopen(f);
    }

private slots:
   // void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    ros::NodeHandlePtr fwPtr;
    ros::Publisher fw;
    std_msgs::Float32MultiArray Action_msg;
    void init_msg();
  Ui::MainWindow2 *ui;
};

#endif // MAINWINDOW2_H
