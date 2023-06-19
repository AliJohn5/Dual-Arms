#include "definitionsAllPinsTowRobots.h"

#include "ros.h"
#include <std_msgs/Float32MultiArray.h>

float state = 10;

void ROS_properities();

void IK_FK();
void Jacobian();

void grabItOrNot();

ros::NodeHandle  nh;

/* these comming matrix hold the both arm's data.
   it can be angles to do IK or FK, or it can hold
   speeds in case of we want to do path planning.
*/
bool flag1 = false;
byte n = 0;
void ActionCb(const std_msgs::Float32MultiArray& s) {
  state = s.data[0]; /* the first value is what should th arms do, it can be:
                      (0)or(1): it means do the IK or FK.
                      (2): run at cirtain speeds (Jacobian).
                      (3): that means go to Zero.
                      (5): open/close grippersu
*/
  for (byte i = 1; i < 12; i++)
    action[i - 1] = s.data[i];

  if (state == 3 && n == 0)
    flag1 = true;
  else
    n = 0;

}
ros::Subscriber<std_msgs::Float32MultiArray> ACTION("dual_arm", ActionCb );

void setup() {
  initial();
 

  //servocon = 0.05; // servo factor, the higher the faster
  zero();
  R1base.setCurrentPosition(R1ZeroSteps[0]);
  R2base.setCurrentPosition(R2ZeroSteps[0]);
  R1shoulder.setCurrentPosition(R1ZeroSteps[1]);
  R2shoulder.setCurrentPosition(R2ZeroSteps[1]);
  R1elbow.setCurrentPosition(R1ZeroSteps[2]);
  R2elbow.setCurrentPosition(R2ZeroSteps[2]);
  R1wrist.setCurrentPosition(R1ZeroSteps[3]);
  ROS_properities();
}
void loop() {
  if (state == 2)
    Jacobian();
  else if (state == 0 || state == 1 || state == 4)
    IK_FK();
  else if (state == 5)
    grabItOrNot();
  else if (state == 3 && flag1) {
    zero();
    n++;
    flag1 = false;
  }

  grabItOrNot();

  nh.spinOnce();
}
void ROS_properities() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(ACTION);
}
void IK_FK() {
  /** Go to comming angles **/
  //R1
//long x[] = {action[0],action[1],action[2],action[3],action[4]};
  //R2
 //long x[] = {action[0],action[1],action[2],action[3],action[4],action[5],action[6],action[7]};
 long x[] = {action[5], action[6], action[7]};
  tow_arms_steppers.moveTo(x);
  tow_arms_steppers.run();

    R2wrist.write(action[8]);

}
void Jacobian() {
  /*R1base.setSpeed(action[0]);
    R1base.runSpeed();
    R1shoulder.setSpeed(action[1]);
    R1shoulder.runSpeed();
    R1elbow.setSpeed(action[2]);
    R1elbow.runSpeed();
    R1wrist.setSpeed(action[3]);
    R1wrist.runSpeed();
    R1EndEffector.setSpeed(action[4]);
    R1EndEffector.runSpeed();
  */

  R2base.setMaxSpeed(action[5]);
  R2base.run();
  R2shoulder.setMaxSpeed(action[6]);
  R2shoulder.run();
  R2elbow.setMaxSpeed(action[7]);
}
void grabItOrNot() {
  if(action[0] > 0)
  R1EndEff.write(R1_closeGripperAngle);
  else
  R1EndEff.write(R1_openGripperAngle);
  if(action[1] > 0)
  R2EndEff.write(R2_closeGripperAngle);
  else
  R2EndEff.write(R2_openGripperAngle);
}
