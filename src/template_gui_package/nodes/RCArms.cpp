#include<QApplication>
#include<QPushButton>
#include "hello_gui.h"
#include <QScreen>
#include<QWidget>

void runNodes()
{
  //system("rosrun template_gui_package talker &");
}



int main(int argc, char **argv)
{
  ros::init(argc,argv,"hello_gui_node");
  QApplication a(argc,argv);
  helloGui w;
  runNodes();
  QScreen *screen = QGuiApplication::primaryScreen();

      // Calculate the center point of the screen
  QPoint center = screen->geometry().center();

      // Set the widget's position to the center of the screen
  w.move(center - w.rect().center());
  w.show();
  return a.exec();
}
