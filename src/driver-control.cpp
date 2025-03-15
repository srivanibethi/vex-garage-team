#include "vex.h"
#include <iostream>
#include <cstdlib>
#include "auton.h"
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

int mogoState = 0;  // Renamed to avoid conflict with clampState
static bool R2Pressed = false;
static void MoveMogo() {
    // Check if R2 is currently being pressed
    if(Controller.ButtonR2.pressing()) {
        // Only take action if button wasn't pressed in the previous iteration
        if(!R2Pressed) {
            R2Pressed = true;
            // Toggle between hold and release
            mogoState = 1 - mogoState; // Toggle between 0 and 1
            
            if(mogoState == 1) {
                // Close/hold the clamp
                P.set(true);
                Brain.Screen.clearScreen();
                Brain.Screen.setCursor(1, 1);
                Brain.Screen.print("Clamp: HOLDING");
            } else {
                // Release the clamp
                P.set(false);
                Brain.Screen.clearScreen();
                Brain.Screen.setCursor(1, 1);
                Brain.Screen.print("Clamp: RELEASED");
            }
        }
    } else {
        // Reset the pressed state when the button is released
        R2Pressed = false;
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


// Add skills autonomous function declaration
extern void skillsAutonomous(void);
bool autonRunning = false;

// Function to check if a specific button combination is pressed to trigger skills autonomous
static void CheckAutonTrigger() {
    static bool buttonPressed = false;
    
    // Press X + Y buttons simultaneously to trigger skills autonomous
    if(Controller.ButtonX.pressing() && Controller.ButtonY.pressing()) {
        if (!buttonPressed && !autonRunning) {
            buttonPressed = true;
            
            // Display message on controller
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1, 1);
            Controller.Screen.print("Running Skills Mode");
            
            // Display message on brain
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("Starting Skills Autonomous");
            
            // Set flag to prevent multiple triggers
            autonRunning = true;
            
            // Run the skills autonomous routine directly
            skillsAutonomous();
            
            // Reset flag after autonomous is done
            autonRunning = false;
            
            // Display completion message
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1, 1);
            Controller.Screen.print("Skills Complete");
            Controller.Screen.setCursor(2, 1);
            Controller.Screen.print("Back to driving");
            
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("Skills autonomous complete");
            Brain.Screen.setCursor(2, 1);
            Brain.Screen.print("Back to driver control");
            
            // Wait briefly to avoid immediate re-triggering
            wait(500, msec);
        }
    } else {
        // Reset when buttons are released
        buttonPressed = false;
    }
}

void drivercontrol() {
    // Initialize driver control
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("Driver Control");
    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("X+Y: Run Skills Mode");
    
    // Main control loop
    while(true) {
        // Check for autonomous trigger before normal controls
        CheckAutonTrigger();
        
        // Only process normal controls if autonomous is not running
        if(!autonRunning) {
            MoveDrivetrain();
            MoveIntake();
            MoveDoinker();
            MoveMogo();
            MoveArm();
            MoveClamp();
            MoveLadyBrown();
        }

        wait(20, msec);
    }
}

// vexcodeInit() is defined in main.cpp
