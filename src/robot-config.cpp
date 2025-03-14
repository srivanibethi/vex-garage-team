#include "vex.h"
#include "robot-config.hpp"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;
controller Controller;

motor FL = motor(PORT4, ratio6_1, true);
motor ML = motor(PORT1, ratio6_1, true);
motor BL = motor(PORT8, ratio6_1, false);
motor_group LeftDrive = motor_group(FL, ML, BL);
motor FR = motor(PORT3, ratio6_1, false);
motor MR = motor(PORT7, ratio6_1, false);
motor BR = motor(PORT9, ratio6_1, true);
motor_group RightDrive = motor_group(FR, MR, BR);

digital_out D = digital_out(Brain.ThreeWirePort.E);
digital_out P = digital_out(Brain.ThreeWirePort.G);

motor Intake1 = motor(PORT5, ratio6_1, true);
motor Intake2 = motor(PORT2, ratio6_1, false);
motor_group Intake = motor_group(Intake1,Intake2);

motor LadyBrown = motor(PORT11, ratio6_1, false);

inertial Inertial = inertial(PORT6);

void vexcodeInit(void) {
  // Initialize motors and sensors
  // Set brake modes for drive motors
  LeftDrive.setStopping(brake);
  RightDrive.setStopping(brake);
  
  // Set default velocities
  LeftDrive.setVelocity(100, pct);
  RightDrive.setVelocity(100, pct);
  Intake.setVelocity(100, pct);
  LadyBrown.setVelocity(100, pct);
}
