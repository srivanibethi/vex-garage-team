#include <iostream>
#include <cstdlib>
#include "vex.h"
#include "driver-contro.hpp"
#include "robot-config.hpp"
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

}

int main() {
  Competition.drivercontrol(drivercontrol);
  Competition.autonomous(autonomous);

  pre_auton();
  
  while(true) {
    wait(20, msec);
  }
}
