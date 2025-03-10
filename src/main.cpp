#include <iostream>
#include <cstdlib>
#include "vex.h"
#include "driver-control.hpp"
#include "robot-config.hpp"
#include "auton.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

competition Competition;
bool inauton = false;


void vexcodeInit() {

}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  inauton = true;
  
  // Choose which autonomous routine to run
  // AWPRed();    // Uncomment this line to run AWP Red autonomous
  // AWPBlue();   // Uncomment this line to run AWP Blue autonomous
  // Red();       // Uncomment this line to run Red autonomous
  // Blue();      // Uncomment this line to run Blue autonomous
  // AutonSkills(); // Uncomment this line to run Skills autonomous
  
  // Choose one of these autonomous functions:
  //   TestPID();    // PID-based autonomous (more accurate)
  // CustomAuton(); // Alternative time-based autonomous (simpler but less accurate)
  
  inauton = false;
}

int main() {
  Competition.drivercontrol(drivercontrol);
  Competition.autonomous(autonomous);

  pre_auton();
  
  while(true) {
    wait(20, msec);
  }
}
