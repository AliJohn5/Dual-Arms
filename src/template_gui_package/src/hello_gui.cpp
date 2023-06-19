#include "hello_gui.h"
#include "ui_hello_gui.h"
//#include "rrtstar.h"
#include "mainwindow2.h"
#include "mainwindow3.h"
#include "mainwindow4.h"
#include <QMessageBox>
#include <QApplication>
#include<QScreen>
#include<QWidget>
static QString qstring_msg;
//using namespace cv;



//using namespace ali;

bool isSerialRunning = false;

bool is_Kinect_running = false;
const char * Kinect = "rosrun template_gui_package Kinect &";
const char * killKinect = "rosnode kill /Kinect1 &";

bool IsNodeRunning(const std::string& node_name)
{
    ros::NodeHandle nh;
    std::vector<std::string> nodes;
    if (ros::master::getNodes(nodes))
    {
        for (const auto& node : nodes)
        {
            if (node.find(node_name) != std::string::npos)
            {
                return true;
            }
        }
    }
    return false;
}


helloGui::helloGui(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::helloGui)
{
  ui->setupUi(this);
  second = new MainWindow2(this);
  win3 = new MainWindow3(this);
  win4 = new MainWindow4(this);
  setWindowTitle("RCArms");
  QIcon icon(":/new/prefix1/img/bac3.png");
  setWindowIcon(icon);
  QObject::connect(second, &MainWindow2::dataToSend, this, &helloGui::receiveData);
  QObject::connect(second, &MainWindow2::dataopen, this, &helloGui::not_hide);
  QObject::connect(win3, &MainWindow3::dataopen, this, &helloGui::not_hide);
  QObject::connect(win4, &MainWindow4::dataopen, this, &helloGui::not_hide);
  serialPtr.reset(new ros::NodeHandle("~"));
  serial = serialPtr->advertise<std_msgs::String>("/SERIAL",1);
  ros_timer = new QTimer(this);
  connect(ros_timer,SIGNAL(timeout()),this,SLOT(spinOnce()));
  ros_timer->start(100);
}

helloGui::~helloGui()
{
  delete ui;
}

void helloGui::spinOnce()
{
  if (ros::ok())
  {
    ros::spinOnce();
  } else {
    QApplication::quit();
}
}


void helloGui::spin()
{
  if (ros::ok())
  {
    ros::spin();
  } else {
    QApplication::quit();
  }
}

void helloGui::openSecondWindow() {
  hide();

  QScreen *screen = QGuiApplication::primaryScreen();

  // Calculate the center point of the screen
  QPoint center = screen->geometry().center();
  // Set the widget's position to the center of the screen
  second->move(center - second->rect().center());
  second->show();
}

void helloGui::openwin3()
{
  hide();
  QScreen *screen = QGuiApplication::primaryScreen();

  // Calculate the center point of the screen
  QPoint center = screen->geometry().center();
  // Set the widget's position to the center of the screen
  win3->move(center - win3->rect().center());
  win3->show();
}
void helloGui::openwin4()
{
  hide();
  QScreen *screen = QGuiApplication::primaryScreen();

  // Calculate the center point of the screen
  QPoint center = screen->geometry().center();
  // Set the widget's position to the center of the screen
  win4->move(center - win4->rect().center());

  win4->show();
}


void helloGui::closeEvent(QCloseEvent *event)
{
  closeNodes();
  QApplication::quit();
}

void closeNodes()
{
  //system("rosnode kill -a");
 // system("rosnode kill /DUAL &");
  system("rosnode kill /Kinect1 &");
}

void helloGui::on_pushButton_7_clicked()
{
  openSecondWindow();
}

void helloGui::on_pushButton_8_clicked()
{
    openwin3();
}

void helloGui::on_pushButton_9_clicked()
{
    openwin4();
}

void helloGui::on_pushButton_clicked()
{
  bool is_error = false;
  if (IsNodeRunning("Kinect1"))
  {
   int result = QMessageBox::question(this,"Running Kinect","Kinect is already runnig, Do you want to Kill it?", QMessageBox::Yes | QMessageBox::No);
   if(result == QMessageBox::Yes) system(killKinect);
  }
  else {
    is_error = system(Kinect);
  }

  if(is_error)
  {
    system(killKinect);
    QMessageBox::warning(this,"Runnin Error","I can't run Kinect, try to connect camera.");
  }

}

void helloGui::on_pushButton_2_pressed()
{
    std_msgs::String msg;
    if(!isSerialRunning)
    msg.data = "rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=115200 &";
    else
    msg.data = "rosnode kill /serial_node &";

    serial.publish(msg);
    isSerialRunning = !isSerialRunning;
}
