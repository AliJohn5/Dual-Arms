#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H


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


namespace Ui {
class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow3(QWidget *parent = nullptr);
  ~MainWindow3();

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

private:
  Ui::MainWindow3 *ui;
};

#endif // MAINWINDOW3_H
