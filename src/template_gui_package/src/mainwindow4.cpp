#include "mainwindow4.h"
#include "ui_mainwindow4.h"
#include "hello_gui.h"
#include<string.h>
#include <geometry_msgs/Twist.h>
#include "rrtstar.h"
#include<QMessageBox>
#include <QProcess>


//using namespace ali;

#ifndef INF
#define INF 10000000
#endif

#define increment 30 // unit in milli second [ms].


int hueRange = 4;
int saturationRange = 20;
int valueRange = 20;

using std::thread;

bool is_Kinect_running1 = false;
const char * Kinect1 = "rosrun template_gui_package Kinect &";
const char * killKinect1 = "rosnode kill /Kinect1 &";
using std::string;

bool f = false;
bool first_move = false;
static cv::Mat image;
static cv::Mat image2;

double num_of_cols = 640;
double num_of_raws = 480;
double ddd = -30;

double max_x1 = 400;
double max_y1 = +200;
double max_z1 = 260;

double min_x1 = -400;
double min_y1 = -200;
double min_z1 = 0;


double max_x2 = 400;
double max_y2 = 200;
double max_z2 = 260;

double min_x2 = -400;
double min_y2 = -200;
double min_z2 = 0;


static double x_of_center = 320;
static double y_of_center = 160;

double x_for_z ;
double y_for_z ;

static QLabel* lab;
//static QLabel* lab2;

QProcess process;

QString output;

double _x1=0;
double _y1=0;
double _z1=0;


double send_x2= x_of_center;
double send_y2= y_of_center;
double send_z2= 50;


double send_x1=x_of_center;
double send_y1=y_of_center;
double send_z1=50;



double e_send_x2=-239.32;
double e_send_y2=-372.33;
double e_send_z2= 17.85 ;

double e_send_x1=-241.78;
double e_send_y1=0;
double e_send_z1=202.59;

double  x_center = 0;
double  y_center = 0;
uint16_t * depth_data;

double x_yello;
double y_yello;
double z_yello;

int x_yello_img = -1;
int y_yello_img = -1;
int z_yello_img = -1;



double x_green;
double y_green;
double z_green;

int x_green_img = -1;
int y_green_img = -1;
int z_green_img = -1;


double x_end = -3;
double y_end = -3;
double z_end = -3;


int x_end_img = -3;
int y_end_img = -3;


QLabel *x_label;
QLabel *y_label;

int time_for_all = 50;

bool IsNodeRunning(const std::string& node_name);



cv::Mat detect_center_of_object(cv::Mat img, int x ,int y)
{
      vector<vector<cv::Point>> contours;
      vector<cv::Vec4i> hierarchy;
      findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
      // Find the contour that contains the point
      cv::Point point(x, y);
      int contourIdx = -1;
      for (size_t i = 0; i < contours.size(); i++)
      {
          double dist = pointPolygonTest(contours[i], point, true);
          if (dist >= 0)
          {
              contourIdx = static_cast<int>(i);
              break;
          }
      }

      // Find the center of the contwidthour
      if (contourIdx >= 0) {
      cv::Moments moment = moments(contours[static_cast<unsigned int>(contourIdx)]);
      // Calculate the center of the contour
      int cx = static_cast<int>(moment.m10 / moment.m00) ;
      int cy = static_cast<int>(moment.m01 / moment.m00) ;
      // Draw a circle at the center of the object
      circle(img, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);
      x_center = cx;
      y_center = cy;
      return img;
      }
      x_center = 0;
      y_center = 0;
      return img;
}



void getHSVRange(cv::Vec3b gbr, int& minH, int& maxH, int& minS, int& maxS, int& minV, int& maxV) {
    cv::Mat3b color(1,1,cv::Vec3b(gbr[0], gbr[1], gbr[2])); // convert RGB to BGR for OpenCV
    cv::Mat3b hsv;
    cvtColor(color, hsv, cv::COLOR_BGR2HSV);
    cv::Vec3b hsvColor = hsv(0,0);
    int hue = hsvColor[0];
    int saturation = hsvColor[1];
    int value = hsvColor[2];

    // Set range for hue, saturation, and value to create a mask for the color
    int hueRange = 10;
    int saturationRange = 50;
    int valueRange = 50;

    minH = (hue - hueRange < 0) ? 0 : hue - hueRange;
    maxH = (hue + hueRange > 179) ? 179 : hue + hueRange;
    minS = (saturation - saturationRange < 0) ? 0 : saturation - saturationRange;
    maxS = (saturation + saturationRange > 255) ? 255 : saturation + saturationRange;
    minV = (value - valueRange < 0) ? 0 : value - valueRange;
    maxV = (value + valueRange > 255) ? 255 : value + valueRange;
}



cv::Mat createMask(cv::Mat3b img, int minH, int maxH, int minS, int maxS, int minV, int maxV) {
    cv::Mat3b hsv;
    cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat1b mask;
    inRange(hsv, cv::Scalar(minH, minS, minV), cv::Scalar(maxH, maxS, maxV), mask);

    return std::move(mask);
}




QPixmap Mat_to_pixmap(cv::Mat src)
{
  QImage::Format format=QImage::Format_Grayscale8;
  int bpp = src.channels();
  if (bpp==3) format=QImage::Format_RGB888;
  QImage img(src.cols,src.rows,format);
  uchar *sptr,*dptr;
  size_t linesize = static_cast<size_t>(src.cols*bpp);
  for (int y=0;y<src.rows;y++) {
    sptr=src.ptr(y);
    dptr=img.scanLine(y);
    memcpy(dptr,sptr,linesize);
  }
  if (bpp==3)return  QPixmap::fromImage(img.rgbSwapped());
  return QPixmap::fromImage(img);
}


vector<Point3DForAmin*>path1;
vector<Point3DForAmin*>path2;
bool star1Isruning = false;
bool star2Isruning = false;



MainWindow4::MainWindow4(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow4)
{
  ui->setupUi(this);
  setWindowTitle("control");
  pub1ptr.reset(new ros::NodeHandle("~"));
  init_msg();
  RGBptr.reset(new ros::NodeHandle("~"));
  DEPptr.reset(new ros::NodeHandle("~"));
  missionPtr.reset(new ros::NodeHandle("~"));
  endPubPtr.reset(new ros::NodeHandle("~"));
  lab = ui->label_2;
  x_label = ui->label_6;
  y_label = ui->label_7;
  ros_timer = new QTimer(this);
  connect(ros_timer,SIGNAL(timeout()),this,SLOT(spinOnce()));
  ros_timer->start(100);

  pub1 = pub1ptr->advertise<geometry_msgs::Twist>("/point",10);
  RGB = RGBptr->subscribe<sensor_msgs::Image>("/rgb_image",1,&MainWindow4::RGBcallback,this);
  DEP = DEPptr->subscribe<sensor_msgs::Image>("/depth_image",1,&MainWindow4::DEPcallback,this);
  mission = missionPtr->advertise<std_msgs::Float32MultiArray>("/MISSION",1);
  endPub = pub1ptr->advertise<geometry_msgs::Twist>("/END",1);

  QObject::connect(ui->lineEdit,&QLineEdit::editingFinished,[&]()
  {
    QString command = ui->lineEdit->text();
    QString cl = "";
    for(int i=0 ;i< command.length();i++)
    {
      if(command[i]!=" ")
        cl += command[i];
    }
    if(cl == "clear")
    {
      ui->textEdit->clear();
      return;
    }

    process.setProgram("/bin/sh");
    process.setArguments({"-c",command});
    process.start();
    output = process.readAllStandardOutput();
  }
  );
  QObject::connect(&process,&QProcess::readyReadStandardOutput,[&]()
  {
    output = process.readAllStandardOutput();
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText(output);
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->show();
  });

  QObject::connect(&process,&QProcess::errorOccurred,[&](QProcess::ProcessError error)
  {
    QString errormsg = "Error occured: " + QString::number(error);
    QMessageBox::critical(this,"Error",errormsg);
  });


  QObject::connect(ui->pushButton, &QPushButton::pressed, [&]() {
     // qDebug() << "Button clicked!";
      timer.start(100);
  });

  QObject::connect(ui->pushButton, &QPushButton::released, [&]() {
    Action_msg.data.clear(); // clear data of last angles smg.
    Action_msg.data.push_back(-1);
    mission.publish(Action_msg);
      timer.stop();
  });

  QObject::connect(&timer, &QTimer::timeout, [&]() {
          Action_msg.data.clear(); // clear data of last angles smg.
          Action_msg.data.push_back(3);
          mission.publish(Action_msg);
      });

  QObject::connect(&sendEND, &QTimer::timeout, [&]() {
    geometry_msgs::Twist msg;
    msg.linear.x = x_end;
    msg.linear.y = y_end;
    msg.linear.z = z_end;
    endPub.publish(msg);
  });
  sendEND.start(100);

  QObject::connect(&green, &QTimer::timeout, [&]() {
    if(image.empty()) return;
    int minh,maxh,mins,maxs,minv,maxv;
   unsigned char blueValue = 200;
   unsigned char greenValue = 108;
   unsigned char redValue = 96;
    cv::Vec3b color(blueValue, greenValue, redValue);
    getHSVRange(color,minh,maxh,mins,maxs,minv,maxv);

    cv::Mat mask = createMask(image,minh,maxh,mins,maxs,minv,maxv);
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    for (int var = 0; var < 2; var++) {
      cv::Mat eroded_mask;
      erode(mask, eroded_mask, kernel);
      mask = eroded_mask;
    }

    for (int var = 0; var < 8; var++)
    {
    cv::Mat dilated_mask;
    dilate(mask, dilated_mask, kernel);
    mask = dilated_mask;
    }

    cv::Mat img = mask;
  //  cv::imshow("blue",img);
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // Find the contour that contains the point
    // Find the center of the contwidthou
    for(int i=0;i<contours.size();i++)
    {
      std::vector<cv::Point> point = contours[i];
      if( point[0].x < 540)
      {
        cv::Moments moment = moments(contours[static_cast<unsigned int>(i)]);
        // Calculate the center of the contour
        int cx = static_cast<int>(moment.m10 / moment.m00) ;
        int cy = static_cast<int>(moment.m01 / moment.m00) ;

     //  circle(img, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);

        double a1 =-(cx - x_of_center);
        double a2 = cy - y_of_center;
        x_green = a1/750.0;
        y_green = a2/750.0;

        x_green_img = cx;
        y_green_img = cy;
//        QPixmap m = Mat_to_pixmap(img);

//        int w = lab->width();
//        int h = lab->height();
//        lab->setPixmap( m.scaled(w,h) );
        return;
      }
    }

      x_green_img = -3;
      y_green_img = -3;

      });

 green.start(100);

  QObject::connect(&yello, &QTimer::timeout, [&]() {
    if(image.empty()) return;
    int minh,maxh,mins,maxs,minv,maxv;
   unsigned char blueValue = 60;
   unsigned char greenValue = 80;
   unsigned char redValue = 197;
    cv::Vec3b color(blueValue, greenValue, redValue);
    getHSVRange(color,minh,maxh,mins,maxs,minv,maxv);

    cv::Mat mask = createMask(image,minh,maxh,mins,maxs,minv,maxv);
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    for (int var = 0; var < 2; var++) {
      cv::Mat eroded_mask;
      erode(mask, eroded_mask, kernel);
      mask = eroded_mask;
    }

    for (int var = 0; var < 5; var++)
    {
    cv::Mat dilated_mask;
    dilate(mask, dilated_mask, kernel);
    mask = dilated_mask;
    }

    cv::Mat img = mask;
   // cv::imshow("orange",img);
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // Find the contour that contains the point
    // Find the center of the contwidthour
    if (contours.size()>0){
    cv::Moments moment = moments(contours[static_cast<unsigned int>(contours.size()-1)]);
    // Calculate the center of the contour
    int cx = static_cast<int>(moment.m10 / moment.m00) ;
    int cy = static_cast<int>(moment.m01 / moment.m00) ;

   //circle(image, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);

    double a1 =-(cx - x_of_center);
    double a2 = cy - y_of_center;
    x_yello = a1/750.0;
    y_yello = a2/750.0;

    x_yello_img = cx;
    y_yello_img = cy;
//    QPixmap m = Mat_to_pixmap(img);

//    int w = lab->width();
//    int h = lab->height();
//    lab->setPixmap( m.scaled(w,h) );

    }
    else
    {
      x_yello_img = -1;
      y_yello_img = -1;
    }

      });

  yello.start(100);

  QObject::connect(&END, &QTimer::timeout, [&]() {
    if(image.empty())return ;
    int minh,maxh,mins,maxs,minv,maxv;
   unsigned char blueValue = 73;
   unsigned char greenValue = 41;
   unsigned char redValue = 125;
    cv::Vec3b color(blueValue, greenValue, redValue);
    getHSVRange(color,minh,maxh,mins,maxs,minv,maxv);

    cv::Mat mask = createMask(image,minh,maxh,mins,maxs,minv,maxv);
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    for (int var = 0; var < 2; var++) {
      cv::Mat eroded_mask;
      erode(mask, eroded_mask, kernel);
      mask = eroded_mask;
    }

    for (int var = 0; var < 5; var++)
    {
    cv::Mat dilated_mask;
    dilate(mask, dilated_mask, kernel);
    mask = dilated_mask;
    }

    cv::Mat img = mask;
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // Find the contour that contains the point
    // Find the center of the contwidthour
    cv::imshow("end",img);
    if (contours.size()>0){
    cv::Moments moment = moments(contours[static_cast<unsigned int>(contours.size()-1)]);
    // Calculate the center of the contour
    int cx = static_cast<int>(moment.m10 / moment.m00) ;
    int cy = static_cast<int>(moment.m01 / moment.m00) ;

//   circle(img, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);

    double a1 =-(cx - x_of_center);
    double a2 = cy - y_of_center;
    x_end = a1/750.0;
    y_end = a2/750.0;

    x_end_img = cx;
    y_end_img = cy;
    //x_end =-(x_end_img - x_of_center)/750.0;
    //y_end = y_end_img - y_of_center/750.0;


//    QPixmap m = Mat_to_pixmap(img);

//    int w = lab->width();
//    int h = lab->height();
//    lab->setPixmap( m.scaled(w,h) );
    }

    else
    {
      x_end_img = -3;
      y_end_img = -3;
      x_end = -3;
      y_end = -3;
    }
      });
 END.start(100);


}

MainWindow4::~MainWindow4()
{
  delete ui;
}


void MainWindow4::spinOnce()
{
  if (ros::ok())
  {
    ros::spinOnce();
  } else {
    QApplication::quit();
}
}


void MainWindow4::spin()
{
  if (ros::ok())
  {
    ros::spin();
  } else {
    QApplication::quit();
  }
}


void MainWindow4::RGBcallback(const sensor_msgs::Image::ConstPtr &msg)
{
 // if (!camera_is_on_1) {ui->frame_2_label->clear(); return;}

  cv_bridge::CvImagePtr k = cv_bridge::toCvCopy(msg,"bgr8");
  image = k->image;
 // if (x_center && y_center)
 // circle(image, cv::Point(x_center, y_center), 5, cv::Scalar(0, 0, 255), -1);

 // if(x_yello_img!=-1)
 // circle(image, cv::Point(x_yello_img, y_yello_img), 5, cv::Scalar(0, 0, 255), -1);
 //
//  if(x_green_img!=-1)
//  circle(image, cv::Point(x_green_img, y_green_img), 5, cv::Scalar(0, 255, 0), -1);


  QPixmap m = Mat_to_pixmap(image);
  int w = ui->label->width();
  int h = ui->label->height();
  //if (w > this->width()/2) w = this->width()/2;
  //if (h > this->height()/3) w = this->height()/3;

  ui->label ->setPixmap( m.scaled(w,h) );
  //QVBoxLayout layout(this);
  //layout.addWidget(ui->label);
  // Set the size policy of the widget to QSizePolicy::Fixed or QSizePolicy::Minimum
}

void MainWindow4::DEPcallback(const sensor_msgs::Image::ConstPtr &msg)
{
  depth_data = (uint16_t*)&msg->data[0];

  //uint16_t pixel = msg->data.at<uint16_t>(y_for_z, x_for_z);
  _z1 = 740 - depth_data[((int)y_for_z - 30) * image.cols + (int)(x_for_z)];
/*  for (int i = -30;i<=30;i++) {
    for(int j = -30;j<=30;j++){
    int temp = _z1 = 740-depth_data[(y_for_z  + i) * (image.cols) + (x_for_z) + j];
   if (temp > 5 && temp < 280 && temp<_z1 ) _z1 = temp;
    }
  }
*/

  if(y_end_img!=-3){
  z_end = 740 - depth_data[ ((int) y_end_img -30) * image.cols + (int)(x_end_img)];

  if (z_end < 0) z_end = 0;
  if (z_end > 280) z_end = 280;

  z_end /= 100.00;

  }

  if(y_green_img!=-3){
  z_green = 740 - depth_data[ ((int) y_green_img -30) * image.cols + (int)(x_green_img)];

  if (z_green < 0) z_green = 0;
  if (z_green > 280) z_green = 280;

  z_green /= 100.00;

  }

  if(y_yello_img!=-1){
  z_yello = 740 - depth_data[ ((int) y_yello_img -30) * image.cols + (int)(x_yello_img)];

  if (z_yello < 0) z_yello = 0;
  if (z_yello > 280) z_yello = 280;

  z_yello /= 100.00;

  }

  if (_z1 < 0) _z1 = 0;
  if (_z1 > 280) _z1 = 280;

  send_z2 = _z1/20;
  ui->label_8->setNum(send_z2/100.00);
}


void MainWindow4::closeEvent(QCloseEvent *event)
{
  not_hide();
}



cv::Mat qPixmapToMat(const QPixmap& pixmap)
{
    // Convert the QPixmap to a QImage
    QImage qImage = pixmap.toImage();

    // Convert the QImage to a cv::Mat
    cv::Mat mat(qImage.height(), qImage.width(), CV_8UC4, (void*)qImage.bits(), qImage.bytesPerLine());

    // Convert the BGRA image to BGR
    cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);

    return mat;
}




MainWindow4::CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{
  this->setAlignment(Qt::AlignCenter);
}

void MainWindow4::CustomLabel::mousePressEvent(QMouseEvent *event)
{
  if (!this->pixmap()) return;
  if(image.empty()) return;
  QPoint position = event->pos();

  int x = position.x()*image.cols /this->width();
  int y = position.y()*image.rows /this->height();

  int minh,maxh,mins,maxs,minv,maxv;
  cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
  unsigned char blueValue = pixel[0];
  unsigned char greenValue = pixel[1];
  unsigned char redValue = pixel[2];
  qDebug()<<blueValue<<greenValue<<redValue;
  cv::Vec3b color(blueValue, greenValue, redValue);
  getHSVRange(color,minh,maxh,mins,maxs,minv,maxv);
  cv::Mat mask = createMask(image,minh,maxh,mins,maxs,minv,maxv);
  cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

  for (int var = 0; var < 1; var++) {
    cv::Mat eroded_mask;
    erode(mask, eroded_mask, kernel);
    mask = eroded_mask;
  }

  for (int var = 0; var < 1; var++)
  {
  cv::Mat dilated_mask;
  dilate(mask, dilated_mask, kernel);
  mask = dilated_mask;
  }

  mask = detect_center_of_object(mask,x,y);

  QPixmap m = Mat_to_pixmap(mask);

  int w = lab->width();
  int h = lab->height();
  lab->setPixmap( m.scaled(w,h) );


   x_for_z = x_center;
   y_for_z = y_center;

  _x1 =-(x_center - x_of_center);
  _y1 = y_center - y_of_center;
  double send_x2_l = _x1/750.0;
  double send_y2_l = _y1/750.0;
  x_label->setNum(send_x2_l);
  y_label->setNum(send_y2_l);
}



void MainWindow4::on_pushButton_2_clicked()
{

    Action_msg.data.clear(); // clear data of last angles smg.
    Action_msg.data.push_back(0);
    Action_msg.data.push_back(send_x1/1000.0);
    Action_msg.data.push_back(send_y1/1000.0);
    Action_msg.data.push_back(send_z1/100.0);
    Action_msg.data.push_back(send_x2/1000.0);
    Action_msg.data.push_back(send_y2/1000.0);
    Action_msg.data.push_back(send_z2/100.0);
    Action_msg.data.push_back(x_end);
    Action_msg.data.push_back(y_end);
    Action_msg.data.push_back(z_end);

    mission.publish(Action_msg);
    e_send_x1 = send_x1;
    e_send_y1 = send_y1;
    e_send_z1 = send_z1;
    e_send_x2 = send_x2;
    e_send_y2 = send_y2;
    e_send_z2 = send_z2;


//    Action_msg.data.clear(); // clear data of last angles smg.
//    Action_msg.data.push_back(-1);
//    mission.publish(Action_msg);


    return;
}



void MainWindow4::on_take_first_clicked()
{
   send_x1 = ui->label_6->text().toDouble()*1000;
   send_y1 = ui->label_7->text().toDouble()*1000;
   send_z1 = ui->label_8->text().toDouble()*100;
}

void MainWindow4::on_take_second_clicked()
{
  send_x2 = ui->label_6->text().toDouble()*1000;
  send_y2 = ui->label_7->text().toDouble()*1000;
  send_z2 = ui->label_8->text().toDouble()*100;
}


void MainWindow4::on_pushButton_3_clicked()
{
  bool is_error = false;
  if (IsNodeRunning("Kinect1"))
  {
   int result = QMessageBox::question(this,"Running Kinect","Kinect is already runnig, Do you want to Kill it?", QMessageBox::Yes | QMessageBox::No);
   if(result == QMessageBox::Yes)
   {
     system(killKinect1);
     ui->pushButton_3->setText("switch kinect on");
   }
  }
  else {
    is_error = system(Kinect1);
    ui->pushButton_3->setText("switch kinect off");
  }

  if(is_error)
  {
    system(killKinect1);
    ui->pushButton_3->setText("switch kinect on");
    QMessageBox::warning(this,"Runnin Error","I can't run Kinect, try to connect camera.");
  }
}


void MainWindow4::on_time_for_all_editingFinished()
{
    time_for_all = ui->time_for_all->text().toInt();
}



void MainWindow4::init_msg()
{
  std_msgs::MultiArrayDimension msg_dim;
  msg_dim.label = "mission";
  msg_dim.size = 11; // size is [11] 'cause we have 11 angles of tow arms.
  msg_dim.stride = 11;
  Action_msg.layout.dim.clear(); // clean layout.
  Action_msg.layout.dim.push_back(msg_dim);
}

void MainWindow4::star1_func()
{

    if (!star1Isruning) return;
    time_for_all = ui->time_for_all->text().toInt();
    if(time_for_all==0){
    QMessageBox::information(this,"ERROR","time_for_all i equal to zero");
    return;
    }

   // qDebug()<<1;
    RRTstar3D *ARM1 = new RRTstar3D(max_x1, max_y1, max_z1, min_x1, min_y1, min_z1,30, 10);
    ARM1->get_safety_dist(2);
   // qDebug()<<2;
    //ARM1->get_obstract_point(20, 20,20);
    Point3D sour(e_send_x1, e_send_y1, e_send_z1);
    Point3D fi(send_x1, send_y1, send_z1/2.0);
    //qDebug()<<send_z1;

    if (fi != sour){
   //   qDebug()<<3.1;
    ARM1->set_start_and_goal(sour, fi,time_for_all);
   qDebug()<<sour.x<<sour.y<<sour.z<<fi.x<<fi.y<<fi.z<<time_for_all;
    ARM1->go();
    }
    //qDebug()<<4;
    //ARM1->print_path_for_amin();
    //ARM1->rebootAll(reboot_obsract);
    path1 = ARM1->pathForAmin;
    delete ARM1;
    star1Isruning = false;
}

void MainWindow4::star2_func()
{
  if (!star2Isruning) return;
  time_for_all = ui->time_for_all->text().toInt();

  if(time_for_all==0){
  QMessageBox::information(this,"ERROR","time_for_all i equal to zero");
  return;
  }

  RRTstar3D *ARM2 = new RRTstar3D(max_x2, max_y2, max_z2, min_x2, min_y2, min_z2,40, 10);
  ARM2->get_safety_dist(2);
  //ARM1->get_obstract_point(20, 20,20);
//qDebug()<<6;
  Point3D sour2(e_send_x2, e_send_y2, e_send_z2);
  Point3D fi2(send_x2, send_y2, send_z2/2.0);
  qDebug()<<sour2.x<<sour2.y<<sour2.z<<fi2.x<<fi2.y<<fi2.z<<time_for_all;
  if (fi2 != sour2){
//  int time_for_all = 50;
  ARM2->set_start_and_goal(sour2, fi2,time_for_all);
  //qDebug()<<7;
  ARM2->go();
  }

  path2 = ARM2->pathForAmin;

  delete ARM2;
  star2Isruning = false;

}


void MainWindow4::on_pushButton_4_pressed()
{
  time_for_all = ui->time_for_all->text().toInt();
  if(time_for_all==0){
  QMessageBox::information(this,"ERROR","time_for_all i equal to zero");
  return;
  }
/*
 // qDebug()<<1;
  RRTstar3D *ARM1 = new RRTstar3D(max_x1, max_y1, max_z1, min_x1, min_y1, min_z1,20, 10);
  ARM1->get_safety_dist(2);
 // qDebug()<<2;
  //ARM1->get_obstract_point(20, 20,20);
  Point3D sour(e_send_x1, e_send_y1, e_send_z1);
  Point3D fi(send_x1, send_y1, send_z1/2.0);
  //qDebug()<<send_z1;

  if (fi != sour){
 //   qDebug()<<3.1;
  ARM1->set_start_and_goal(sour, fi,time_for_all);
  qDebug()<<sour.x<<sour.y<<sour.z<<fi.x<<fi.y<<fi.z<<time_for_all;
  ARM1->go();
  }
  //qDebug()<<4;
  //ARM1->print_path_for_amin();
  //ARM1->rebootAll(reboot_obsract);
  vector<Point3DForAmin*>path1 = ARM1->pathForAmin;
//qDebug()<<5;
  RRTstar3D *ARM2 = new RRTstar3D(max_x2, max_y2, max_z2, min_x2, min_y2, min_z2,20, 10);
  ARM2->get_safety_dist(2);
  //ARM1->get_obstract_point(20, 20,20);
//qDebug()<<6;
  Point3D sour2(e_send_x2, e_send_y2, e_send_z2);
  Point3D fi2(send_x2, send_y2, send_z2/2.0);
  qDebug()<<sour2.x<<sour2.y<<sour2.z<<fi2.x<<fi2.y<<fi2.z<<time_for_all;
  if (fi2 != sour2){
//  int time_for_all = 50;
  ARM2->set_start_and_goal(sour2, fi2,time_for_all);
  //qDebug()<<7;
  ARM2->go();
  }

  vector<Point3DForAmin*>path2 = ARM2->pathForAmin;*/
  star1Isruning = true;
  star2Isruning = true;

  std::thread myThread1([&](){
      star1_func();
  });
  std::thread myThread2([&](){
      star2_func();
  });

  qDebug()<<1;
 myThread1.join();
 myThread2.join();
  int i=1;
  int j=1;

  int counterTR1 = 0;
  int counterTR2 = 0;

//  qDebug() << path1.size() <<path2.size();
  ros::Rate rate(increment);
  double vx1,vy1,vz1,vx2,vy2,vz2;
  double dx1,dy1,dz1,dx2,dy2,dz2;
  double t1,t2;
  double r1,r2;
  double v1,v2;

  ROS_INFO("1 = %d  , 2 = %d",path1.size(),path2.size());
  while (i<path1.size() || j<path2.size())
  {
    if(i >= path1.size())
    {
      vx1 = 0;
      vy1 = 0;
      vz1 = 0;
    }
    else
    {
      r1 = sqrt( (path1[i-1]->x - path1[i]->x)*(path1[i-1]->x - path1[i]->x) + (path1[i-1]->y - path1[i]->y)*(path1[i-1]->y - path1[i]->y) + (path1[i-1]->z - path1[i]->z)*(path1[i-1]->z - path1[i]->z) );
      vx1 = path1[i-1]->vx;
      vy1 = path1[i-1]->vy;
      vz1 = path1[i-1]->vz;
      v1 = vx1 + vy1 + vz1;

      if(v1!=0)
      t1 = r1/(v1+0.0);
      if(counterTR1/(increment+0.0) >= t1)
      {
        i++;
        ROS_INFO("i = %d",i);
    //    qDebug()<<"1: " << i << j << path1.size()<<path2.size();
        counterTR1 = 0;
      }

    }

    if(j>= path2.size())
    {
      vx2 = 0;
      vy2 = 0;
      vz2 = 0;
    }

    else{
      dx2 = fabs(path2[j-1]->x - path2[j]->x);
      dy2 = fabs(path2[j-1]->y - path2[j]->y);
      dz2 = fabs(path2[j-1]->z - path2[j]->z);
      r2 = sqrt( dx2*dx2 + dy2*dy2 +dz2*dz2 );
      vx2 = path2[j-1]->vx;
      vy2 = path2[j-1]->vy;
      vz2 = path2[j-1]->vz;
      v2 = vx2 + vy2 + vz2;
      if(v2!=0)
      t2 = r2/(v2+0.0);

      if(counterTR2/(increment+0.0) >= t2)
      {
      j++;
//      qDebug()<<"1: " << i << j << path1.size()<<path2.size();
      ROS_INFO("j = %d",j);
      counterTR2 = 0;
      }
    }



    //qDebug() << vx1 << vy1 << vz1 << vx2<< vy2<<vz2 ;
    //JR.publish(twist_msg);
    Action_msg.data.clear(); // clear data of last angles smg.
    Action_msg.data.push_back(2);
    Action_msg.data.push_back(vx1/1000.0);
    Action_msg.data.push_back(vy1/1000.0);
    Action_msg.data.push_back(vz1/1000.0);
    Action_msg.data.push_back(vx2/1000.0);
    Action_msg.data.push_back(vy2/1000.0);
    Action_msg.data.push_back(vz2/1000.0);
    mission.publish(Action_msg);
    counterTR1++;
    counterTR2++;
    rate.sleep();
  }


  Action_msg.data.clear(); // clear data of last angles smg.
  Action_msg.data.push_back(2);
  Action_msg.data.push_back(0);
  Action_msg.data.push_back(0);
  Action_msg.data.push_back(0);
  Action_msg.data.push_back(0);
  Action_msg.data.push_back(0);
  Action_msg.data.push_back(0);
  mission.publish(Action_msg);
  rate.sleep();

  Action_msg.data.clear(); // clear data of last angles smg.
  Action_msg.data.push_back(-1);
  mission.publish(Action_msg);

  //qDebug()<<"ali";
  e_send_x1 = send_x1;
  e_send_y1 = send_y1;
  e_send_z1 = send_z1;

  e_send_x2 = send_x1;
  e_send_y2 = send_y2;
  e_send_z2 = send_z2;


}

