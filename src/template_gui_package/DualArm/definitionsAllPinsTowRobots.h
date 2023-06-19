#ifndef DEFINITIONSALLPINSTOWROBOTS_H_INCLUDED
#define DEFINITIONSALLPINSTOWROBOTS_H_INCLUDED

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Stepper.h>
#include <Servo.h>
#include <math.h>

#define allStepperMotors_R2_stops !(R2base.distanceToGo()||R2shoulder.distanceToGo()||R2elbow.distanceToGo())
//#define allStepperMotors_R1_stops !(R1base.isRunning()||R1shoulder.isRunning()||R1elbow.isRunning())
#define allStepperMotors_R1_stops !(R1base.distanceToGo()||R1shoulder.distanceToGo()||R1elbow.distanceToGo()||R1wrist.distanceToGo())
//#define allStepperMotors_R1_stops !(R1base.isRunning()||R1shoulder.isRunning()||R1elbow.isRunning())

#define R1baseDir 47            //------base motor direction pin
#define R1baseStep 46          //------base motor step pin
#define R1shoulderDir 49       //------shoulder motor direction pin
#define R1shoulderStep 48       //------shoulder motor direction pin
#define R1elbowDir 51              //------arm motor direction pin
#define R1elbowStep 50           //------arm motor step pin
#define R1wristDir 53             //------arm motor direction pin
#define R1wristStep 52           //------arm motor step pin
#define R1EndEffIN1BYJ 39
#define R1EndEffIN2BYJ 38
#define R1EndEffIN3BYJ 37
#define R1EndEffIN4BYJ 36
#define R1EndEffPin 2

#define R1BYJstepsPerRevolution 2038

#define R2baseDir 41       //------base motor direction pin
#define R2baseStep 40      //------base motor step pin
#define R2shoulderDir 43   //------shoulder motor direction pin
#define R2shoulderStep 42  //------shoulder motor direction pin
#define R2elbowDir 45      //------arm motor direction pin
#define R2elbowStep 44     //------arm motor step pin
#define R2WristPin 3
#define R2EndEffPin 9
#define R2baseLimit 23     // Normaly Closed (true)
#define R2shoulderLimit 22 // Normaly Closed (true)
#define R2elbowLimit 25    // Normaly Open (false)

#define R1baseLimit 0
#define R1shoulderLimit 8   // Normaly Open (false)
#define R1elbowLimit 24  // Normaly Open (false)

#define motorInterfaceType 1

/* zero angles */
#define R1theta1 90
#define R1theta2 125
#define R1theta3 -97
#define R1theta4 -78

#define R2theta1 166 //167
#define R2theta2 53
#define R2theta3 -7
#define R2theta4 130
/* Transmition Values*/
#define R1BaseTr 3.3
#define R1ShoulderTr 5.0
#define R1ElbowTr 3.5
#define R1WristTr 2.3

#define R2BaseTr 1
#define R2ShoulderTr 4.5
#define R2ElbowTr 4.5

#define R1_openGripperAngle 180
#define R1_closeGripperAngle 0

#define R2_openGripperAngle 38
#define R2_closeGripperAngle 160
float timeAngle;
float timeAngleadjust;
float moveAngle;
int oldposition;
float servocon;
float sfactor;

float action[11] = {0};

const int R1[2][4] = { // first row : all Dir _|_ Second row : all step
  {R1baseDir, R1shoulderDir, R1elbowDir, R1wristDir},
  {R1baseStep, R1shoulderStep, R1elbowStep, R1wristStep}
};
const int R2[2][3] = {
  {R2baseDir, R2shoulderDir, R2elbowDir},
  {R2baseStep, R2shoulderStep, R2elbowStep}
};
const float R2ZeroSteps[] {
  R2theta1 * 6400.0 / 360.0 * R2BaseTr ,
  R2theta2 * 6400.0 / 360.0 * R2ShoulderTr,
  R2theta3 * 6400.0 / 360.0 * R2ElbowTr,
  R2theta4
};
const float R1ZeroSteps[] {
  R1theta1 * 6400.0 / 360.0 * R1BaseTr,
  R1theta2 * 6400.0 / 360.0 * R1ShoulderTr,
  R1theta3 * 6400.0 / 360.0 * R1ElbowTr,
  R1theta4 * 6400.0 / 360.0 * R1WristTr
};
AccelStepper R1base = AccelStepper(motorInterfaceType, R1[1][0], R1[0][0]);
AccelStepper R1shoulder = AccelStepper(motorInterfaceType,  R1[1][1], R1[0][1]);
AccelStepper R1elbow = AccelStepper(motorInterfaceType,  R1[1][2], R1[0][2]);
AccelStepper R1wrist = AccelStepper(motorInterfaceType,  R1[1][3], R1[0][3]);
AccelStepper  R1EndEffector(4, 39, 38, 37, 36);

AccelStepper R2base = AccelStepper(motorInterfaceType, R2[1][0], R2[0][0]);
AccelStepper R2shoulder = AccelStepper(motorInterfaceType, R2[1][1], R2[0][1]);
AccelStepper R2elbow = AccelStepper(motorInterfaceType, R2[1][2], R2[0][2]);

MultiStepper tow_arms_steppers;
Servo R2wrist;
Servo R2EndEff;// Open angle = 180 & Close angle = 0
Servo R1EndEff; // Open angle = 150 & Close angle = 0

void initial() {
  pinMode(R1EndEffIN1BYJ, OUTPUT);
  pinMode(R1EndEffIN2BYJ, OUTPUT);
  pinMode(R1EndEffIN3BYJ, OUTPUT);
  pinMode(R1EndEffIN4BYJ, OUTPUT);

  R1base.setMaxSpeed(20000);
  R1base.setAcceleration(10000);
  R1shoulder.setMaxSpeed(20000);
  R1shoulder.setAcceleration(10000);
  R1elbow.setMaxSpeed(20000);
  R1elbow.setAcceleration(70000);
  R1wrist.setMaxSpeed(20000);
  R1wrist.setAcceleration(70000);
  R1EndEffector.setMaxSpeed(100);
  R1EndEffector.setAcceleration(20);
  R1EndEff.attach(2);

  R2base.setMaxSpeed(10000); // Speed unit : [step/s] steps per seconds.
  R2base.setAcceleration(5000);
  R2shoulder.setMaxSpeed( 20000);
  R2shoulder.setAcceleration(10000);
  R2elbow.setMaxSpeed( 20000);
  R2elbow.setAcceleration(10000);
  R2wrist.attach(R2WristPin);
  R2EndEff.attach(R2EndEffPin);

  pinMode(R2baseLimit, INPUT);
  pinMode(R2shoulderLimit, INPUT);
  pinMode(R2elbowLimit, INPUT);
  pinMode(R1elbowLimit, INPUT);
  pinMode(R1shoulderLimit, INPUT);
  Serial.begin(115200);
  /*tow_arms_steppers.addStepper(R1base);
  tow_arms_steppers.addStepper(R1shoulder);
  tow_arms_steppers.addStepper(R1elbow);
  tow_arms_steppers.addStepper(R1wrist);
  tow_arms_steppers.addStepper(R1EndEffector);*/
  tow_arms_steppers.addStepper(R2base);
  tow_arms_steppers.addStepper(R2shoulder);
  tow_arms_steppers.addStepper(R2elbow);
}




void zero() {
  bool R1 = false, R2 = false;
  while (true) {
    bool x = digitalRead(R2baseLimit);
    bool s = digitalRead(R2baseLimit);
    if (x == 0 && s == 0) {
      delay (5);
      if (x == 0 && s == 0)
        break;
    }
    R2base.setSpeed(1500);
    R2base.runSpeed();
  }
  R2base.stop();
  R1base.setCurrentPosition(R1ZeroSteps[0]);
  R2base.setCurrentPosition(R2ZeroSteps[0]);
  R1 = false; R2 = false;
  while (true) {
    bool x1 = digitalRead(R1shoulderLimit);
    bool x2 = digitalRead(R2shoulderLimit);
    if (x2 && !R2) {
      R2shoulder.setSpeed(-1500);
      R2shoulder.runSpeed();
      delay(1);
    }
    else {
      R2shoulder.stop();
      R2 = !R2;
    }
    if (!x1 && !R1) {
      R1shoulder.setSpeed(2000);
      R1shoulder.runSpeed();
    }
    else {
      R1shoulder.stop();
      R1 = !R1;
    }
    if (R1 && R2)
      break;
  }
  R1 = !R1;
  R1= true;
  R2 = !R2;
  R1shoulder.setCurrentPosition(R1ZeroSteps[1]);
  R2shoulder.setCurrentPosition(R2ZeroSteps[1]);
  while (true) {
    bool x1 = digitalRead(R1elbowLimit);
    bool x2 = digitalRead(R2elbowLimit);
    if (x2 && !R2) {
      R2elbow.setSpeed(-1000);
      R2elbow.runSpeed();
      delay(1);
    }
    else {
      R2elbow.stop();
      R2 = !R2;
    }
    if (!x1 && !R1) {
      R1elbow.setSpeed(-2000);
      R1elbow.runSpeed();
    }
    else {
      R1elbow.stop();
      R1 = !R1;
    }
    if (R1 && R2)
      break;
  }

  R1elbow.setCurrentPosition(R1ZeroSteps[2]);
  R2elbow.setCurrentPosition(R2ZeroSteps[2]);
  R1 = !R1;
  R2 = !R2;
  R2wrist.write(R2theta4);
  R1EndEffector.setCurrentPosition(0);
  R1EndEff.write(R1_openGripperAngle);
  R2EndEff.write(R2_openGripperAngle );
}
#endif // DEFINITIONSALLPINSTOWROBOTS_H_INCLUDED
