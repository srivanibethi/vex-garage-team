#include "vex.h"
#include <iostream>
#include <cstdlib>
using namespace vex;
#include "robot-config.hpp"

static void MoveDrivetrain() {
    double TempSpeed = 1;
    double DriveSpeed = (Controller.Axis3.position()) * 0.99 * TempSpeed;
    double TurnSpeed = (Controller.Axis1.position()) * 0.99 * TempSpeed;
    LeftDrive.setVelocity((DriveSpeed + TurnSpeed), pct);
    RightDrive.setVelocity((DriveSpeed - TurnSpeed), pct);

    if (((FL.temperature(temperatureUnits::fahrenheit)) >= 131) || ((ML.temperature(temperatureUnits::fahrenheit)) >= 131) || 
    ((BL.temperature(temperatureUnits::fahrenheit)) >= 131) || ((FR.temperature(temperatureUnits::fahrenheit)) >= 131) || 
    ((MR.temperature(temperatureUnits::fahrenheit)) >= 131) || ((BR.temperature(temperatureUnits::fahrenheit)) >= 131)) {
      TempSpeed = 0.13;
    }
    else if (((FL.temperature(temperatureUnits::fahrenheit)) > 90) || ((ML.temperature(temperatureUnits::fahrenheit)) > 90) || 
    ((BL.temperature(temperatureUnits::fahrenheit)) > 90) || ((FR.temperature(temperatureUnits::fahrenheit)) > 90) || 
    ((MR.temperature(temperatureUnits::fahrenheit)) > 90) || ((BR.temperature(temperatureUnits::fahrenheit)) > 90)) {
      TempSpeed = 0.66;
    }
    else {
      TempSpeed = 1;
    }

    LeftDrive.spin(forward);
    RightDrive.spin(forward);

}

static void MoveIntake() {
    // Set intake velocity to maximum speed (100%)
    Intake.setVelocity(100, pct);
    
    // Press and hold L1 to spin intake forward at max speed
    if(Controller.ButtonL1.pressing()) {
        Intake.spin(forward);
    }
    // Press and hold L2 to spin intake in reverse at max speed
    else if(Controller.ButtonL2.pressing()) {
        Intake.spin(reverse);
    }
    // Stop the intake when neither button is pressed
    else {
        Intake.stop();
    }
}


int arm = 0;
static void MoveDoinker(){
  if(Controller.ButtonX.pressing()) {
    arm += 1;
    if(arm%2 == 1) {
        D.set(true);
    }

    if(arm%2 == 0) {
        D.set(false);
    }
    wait(150, msec);
  }
}

int mogo = 0;
static void MoveMogo() {
    if(Controller.ButtonR2.pressing()) {
        mogo += 1;
        if(mogo%2 == 1) {
            P.set(true);
            wait(150, msec);
        }

        if(mogo%2 == 0) {
            P.set(false);
            wait(150, msec);
        }
    }
}

int armPosition = 0;
static void MoveArm() {
    // Implement arm movement functionality
    // This is a placeholder implementation
    if(Controller.ButtonR1.pressing()) {
        armPosition += 1;
        // Add actual arm control code here
        wait(150, msec);
    }
}

int clampState = 0;
static void MoveClamp() {
    // Implement clamp movement functionality
    // This is a placeholder implementation
    if(Controller.ButtonY.pressing()) {
        clampState += 1;
        // Add actual clamp control code here
        wait(150, msec);
    }
}

static void MoveLadyBrown() {
    // Set LadyBrown velocity for operation
    LadyBrown.setVelocity(100, pct);
    
    // Button A - Move lady brown forward
    if(Controller.ButtonA.pressing()) {
        LadyBrown.spin(forward);
    }
    // Button B - Move lady brown backward
    else if(Controller.ButtonB.pressing()) {
        LadyBrown.spin(reverse);
    }
    // Stop lady brown when no button is pressed
    else {
        LadyBrown.stop();
    }
}


void drivercontrol() {
    // Removed duplicate velocity setting - now handled in MoveIntake function
    while(true){
      MoveDrivetrain();
      MoveIntake();
      MoveDoinker();
      MoveMogo();
      MoveArm();
      MoveClamp();
      MoveLadyBrown();

      wait(20, msec);
    }
}

// vexcodeInit() is defined in main.cpp
