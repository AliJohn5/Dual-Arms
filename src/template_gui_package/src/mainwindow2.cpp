#include "mainwindow2.h"
#include "ui_mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow2)
{
  ui->setupUi(this);
  setWindowTitle("forward");
  fwPtr.reset(new ros::NodeHandle("~"));
  fw = fwPtr->advertise<std_msgs::Float32MultiArray>("/MISSION",1);
  init_msg();
}

MainWindow2::~MainWindow2()
{
  delete ui;
}


//void MainWindow2::on_pushButton_clicked()
//{
//    sendData();
//    qDebug()<<"mainwindow2 send :";
//}

void MainWindow2::closeEvent(QCloseEvent *event)
{
  not_hide();
}

void MainWindow2::on_pushButton_pressed()
{
  Action_msg.data.clear(); // clear data of last angles smg.
  Action_msg.data.push_back(1);
  Action_msg.data.push_back(ui->theta_1_1->text().toInt());
  Action_msg.data.push_back(ui->theta_1_2->text().toInt());
  Action_msg.data.push_back(ui->theta_1_3->text().toInt());
  Action_msg.data.push_back(ui->theta_1_4->text().toInt());
  Action_msg.data.push_back(ui->theta_1_5->text().toInt());
  Action_msg.data.push_back(ui->theta_2_1->text().toInt());
  Action_msg.data.push_back(ui->theta_2_2->text().toInt());
  Action_msg.data.push_back(ui->theta_2_3->text().toInt());
  Action_msg.data.push_back(ui->theta_2_4->text().toInt());
  fw.publish(Action_msg);
}

void MainWindow2::init_msg()
{
  std_msgs::MultiArrayDimension msg_dim;
  msg_dim.label = "mission";
  msg_dim.size = 11; // size is [11] 'cause we have 11 angles of tow arms.
  msg_dim.stride = 11;
  Action_msg.layout.dim.clear(); // clean layout.
  Action_msg.layout.dim.push_back(msg_dim);
}
