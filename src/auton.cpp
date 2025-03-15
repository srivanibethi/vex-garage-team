// Include required headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"
#include "auton.h" // Include auton.h first to get the AutonMode definition

using namespace vex;

// Define the current autonomous mode used by all parts of the program
// Change this value when uploading to different brain slots
const AutonMode CURRENT_AUTON_MODE = AUTON_MODE_SKILLS;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.cpp                                                 */
/*    Description:  Autonomous routines for VEX robot                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auton.h"
#include <thread>   // For threads
#include <future>  // For async tasks 
#include <iostream>
#include <string.h>
#include "robot-config.hpp" // Include robot configuration

// Use references to existing motor groups for autonomous functions
// This avoids duplicate definitions 

// Function to move the robot forward (time-based)
void goForward(double time, int speed) {
  LeftDrive.spin(forward, speed, pct);
  RightDrive.spin(forward, speed, pct);
  wait(time, sec); 
  LeftDrive.stop();
  RightDrive.stop(); 
}

void goBackward(double time, int speed) {
  LeftDrive.spin(reverse, speed, pct);
  RightDrive.spin(reverse, speed, pct);
  wait(time, sec); 
  LeftDrive.stop();
  RightDrive.stop(); 
}

// Function to turn the robot (time-based)
void turnLeft(double time, int speed) {
  LeftDrive.spin(forward, speed, pct);
  RightDrive.spin(reverse, speed, pct);
  wait(time, sec); 
  LeftDrive.stop();
  RightDrive.stop();
}

// Function to turn the robot (time-based)
void turnRight(double time, int speed) {
  LeftDrive.spin(reverse, speed, pct);
  RightDrive.spin(forward, speed, pct);
  wait(time, sec); 
  LeftDrive.stop();
  RightDrive.stop();
}

// Function to run the intake
void runIntake(int speed) {
  Intake.spin(forward, speed, pct); 
}

void stopIntake() {
  Intake.stop();
}

// Function to score rings
void scoreRings() {
  goForward(-1, 100); 

  LadyBrown.spin(forward, 100, pct); 
  wait(1, sec); 
  LadyBrown.stop(); 
}

void redPositiveAutonomous() {
  turnRight(0.2, 50);
  goBackward(1.6, 20);
  turnLeft(0.3, 50);
  goBackward(0.8, 40);
  P.set(true); // Use P from robot-config.hpp instead of ClawPiston
  wait(1, sec); 
  runIntake(70);
  stopIntake();
  turnRight(0.56, 50);
  wait(1, sec); 
  auto driveForwardWrapper = []() { goForward(1, 40); };
  thread driveThread(driveForwardWrapper);
  driveThread.detach();
  auto runIntakeWrapper = []() { runIntake(50); };
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(1, sec);
  turnRight(0.1, 50);
  wait(1, sec);
  goBackward(1.5, 40);
  wait(5, sec);
  stopIntake(); 
}

void bluePositiveAutonomous() {
    turnLeft(0.2, 50);
    goBackward(1.1, 20);
    turnRight(0.25, 50);
    goBackward(0.9, 40);
    P.set(true);  // Use P from robot-config.hpp
    wait(1, sec); 
    runIntake(70);
    stopIntake();
    turnLeft(0.43, 50); 
    auto driveForwardWrapper = []() { goForward(0.8, 50); };
    thread driveThread(driveForwardWrapper);
    driveThread.detach();
    auto runIntakeWrapper = []() { runIntake(50); };
    thread intakeThread(runIntakeWrapper);
    intakeThread.detach();
    wait(1, sec); 
    turnRight(0.25, 50);
    wait(5, sec);
    goBackward(1.5, 50);
    wait(3, sec);
    stopIntake(); 
}

void RedNegativeAutonomous() {
  goBackward(1.03, 25);
  turnLeft(0.16, 50);
  goBackward(0.43, 30);
  P.set(true);  // Use P from robot-config.hpp
  wait(1, sec); 
  runIntake(70);
  wait(1, sec);
  stopIntake();
  turnLeft(0.28, 50); 
  auto driveForwardWrapper = []() { goForward(1.13, 40); };
  thread driveThread(driveForwardWrapper);
  driveThread.detach();
  auto runIntakeWrapper = []() { runIntake(70); };
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(1, sec); 
  goBackward(.53, 25);
  turnLeft(0.46, 50); 
  auto driveForwardWrapper2 = []() { goForward(0.75, 40); };
  thread driveThread2(driveForwardWrapper2);
  driveThread2.detach();
  auto runIntakeWrapper2 = []() { runIntake(70); };
  thread intakeThread2(runIntakeWrapper2);
  intakeThread2.detach();
  wait(1, sec); 
  goForward(.53, 25);
  turnLeft(0.56, 50); 
  goBackward(1.53, 25);
  /*wait(1, sec); 
  stopIntake(); */
}

// Skills autonomous routine
void skillsAutonomous() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Running Skills Autonomous");
  
  // Make sure clamp is released at the start
  P.set(false);
  
  // Start by running the intake
  runIntake(60);
  wait(1, sec); 
  
  // Execute movement pattern
  goForward(0.48, 50);
  turnLeft(0.34, 50);
  goBackward(0.55, 50);

  // Stop the intake before finishing
  stopIntake();
  
  // Final message
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Skills Autonomous Complete");
}

void SimpleAutonomous(const char* position) {
  // For backwards compatibility with existing code
  if (strcmp(position, "0") == 0) {
    redPositiveAutonomous();
  } else if (strcmp(position, "1") == 0) {
    bluePositiveAutonomous();
  } else if (strcmp(position, "2") == 0) {
    RedNegativeAutonomous();
  } else if (strcmp(position, "3") == 0 || strcmp(position, "skills") == 0) {
    skillsAutonomous();
  }
}

// Define descriptive names for each autonomous mode
const char* const AUTON_MODE_NAMES[AUTON_MODE_COUNT] = {
    "Red Alliance Positive",
    "Blue Alliance Positive",
    "Red Alliance Negative",
    "Skills Challenge"
};

void autonomousRunner(const char* input) {
    if (input && input[0]) {
        int modeValue = input[0] - '0';
        if (modeValue >= 0 && modeValue < AUTON_MODE_COUNT) {
            AutonMode mode = static_cast<AutonMode>(modeValue);
            
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1,1);
            Brain.Screen.print("Running: %s", AUTON_MODE_NAMES[mode]);
            
            switch (mode) { 
                case AUTON_MODE_RED_POSITIVE:
                    redPositiveAutonomous(); 
                    break;
                case AUTON_MODE_BLUE_POSITIVE:
                    bluePositiveAutonomous();
                    break;
                case AUTON_MODE_RED_NEGATIVE:
                    RedNegativeAutonomous();
                    break;
                case AUTON_MODE_SKILLS:
                    skillsAutonomous();
                    break;
                default:
                    // Should never reach here
                    Brain.Screen.clearScreen();
                    Brain.Screen.setCursor(1,1);
                    Brain.Screen.print("Invalid autonomous mode");
                    break;
            }
        }
    }
}
