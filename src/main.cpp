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


// vexcodeInit function is now defined in robot-config.cpp

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  inauton = true;
  
  // Display which autonomous is running
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Competition Skills Mode");
  
  // Run skills autonomous directly
  skillsAutonomous();
  
  inauton = false;
}

int main() {
  // Print a message to the brain's screen
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("VEX Robot Starting...");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Press X+Y for Skills Mode");
  
  // For normal competition use
  Competition.drivercontrol(drivercontrol);
  Competition.autonomous(autonomous);

  // Run pre-autonomous function
  pre_auton();
  
  // If in competition mode, we'll let the competition switch control things
  if(Competition.isCompetitionSwitch()) {
    while(true) {
      wait(100, msec);
    }
  }
  
  // If not in competition mode, start driver control immediately
  drivercontrol();
  
  // This should never be reached, but just in case
  while(true) {
    wait(100, msec);
  }
}
