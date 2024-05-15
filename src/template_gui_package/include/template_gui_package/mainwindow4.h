#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H



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


#include <stdio.h>
#include <stdlib.h>
#include "libfreenect/libfreenect.h"

#include <QTimer>
#include<QProcess>
#include <thread>

#define FREENECT_FRAME_H 480
#define FREENECT_FRAME_W 640


using std::vector;

//using namespace cv;
//using namespace std;

/*
namespace  ali{
static cv::Mat image;
static cv::Mat image2;

static int num_of_cols = 480;
static int num_of_raws = 640;

static int x_of_center = 160;
static int y_of_center = 320;

static QLabel* lab;
static QLabel* lab2;


const char * Kinect = "rosrun template_gui_package Kenict &";

}*/

namespace Ui {
class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow4(QWidget *parent = nullptr);
  ~MainWindow4();

  void RGBcallback(const sensor_msgs::Image::ConstPtr& msg);
  void DEPcallback(const sensor_msgs::Image::ConstPtr& msg);
  void closeEvent(QCloseEvent *event);

  class CustomLabel : public QLabel
  {
    //Q_OBJECT
  public:
      CustomLabel(QWidget *parent = nullptr);

      void mousePressEvent(QMouseEvent *event) override;
  };

signals:
    void dataToSend(int data);
    void dataopen(bool f);

public slots:
    void spinOnce();
    void spin();
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
    void on_pushButton_2_clicked();

    void on_take_first_clicked();

    void on_take_second_clicked();

    void on_pushButton_3_clicked();

    void on_time_for_all_editingFinished();


    void on_pushButton_4_pressed();



private:
  Ui::MainWindow4 *ui;
  QTimer *ros_timer;

  ros::NodeHandlePtr RGBptr;
  ros::NodeHandlePtr DEPptr;
  ros::NodeHandlePtr pub1ptr;
  ros::NodeHandlePtr missionPtr;
  ros::NodeHandlePtr endPubPtr;

  ros::Subscriber RGB;
  ros::Subscriber DEP;
  ros::Publisher pub1;
  ros::Publisher mission;
  ros::Publisher endPub;
  std_msgs::Float32MultiArray Action_msg;
  void init_msg();
  QTimer timer;
  QTimer yello;
  QTimer green;
  QTimer END;
  QTimer sendEND;
  void star1_func();
  void star2_func();
  std::thread *w1;
  std::thread *w2;


//  freenect_context *context;
};

#endif // MAINWINDOW4_H
