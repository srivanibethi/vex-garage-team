#include "vex.h"
#include "auton.h"
#include <iostream>
#include "robot-config.hpp"

/*void drivePID(double k, double taui, double taud, double tolerance, double target) {
    double setpoint = target;
    double leftprocessvalue = LeftDrive.position(turns) * M_PI * 3.25 * 0.75;
    double rightprocessvalue = RightDrive.position(turns) * M_PI * 3.25 * 0.75;
    
    double plefterror = 0;
    double lefterror = 0;
    double leftreset = 0;
    double lefttotal = 0;

    double prighterror = 0;
    double righterror = 0;
    double rightreset = 0;
    double righttotal = 0;

    while(((fabs(lefterror) + fabs(righterror))/2) > tolerance) {
        lefterror = setpoint - leftprocessvalue;
        righterror = setpoint - rightprocessvalue;
        
        leftreset += ((k/taui) * lefterror) * 50;
        rightreset += ((k/taui) * righterror) * 50;

        lefttotal = k * lefterror + leftreset + ((plefterror - lefterror) * (k/taud));
        righttotal = k * righterror + rightreset + ((prighterror - righterror) * (k/taud));

        LeftDrive.spin(forward, lefttotal, pct);
        RightDrive.spin(forward, righttotal, pct);

        plefterror = lefterror;
        prighterror = righterror;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

static double getError(double target) {
    if((std::max(target, Inertial.heading()) - std::min(target, Inertial.heading())) > 180) {
        if(std::min(target, Inertial.heading()) == target) {
            return (360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
        else {
            return -(360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
    }
    else {
        return (target - Inertial.heading());
    }
}

static void turnPID(double k, double taui, double taud, double tolerance, double target) {
    double setpoint = target;
    double processvalue = target - getError(target);

    double perror = 0;
    double error = 0;
    double reset = 0;
    double total = 0;

    while(error > tolerance) {
        error = setpoint - processvalue;
        reset += ((k/taui) * error) * 50;
        total = k * error + reset + ((perror - error) * (k/taud));

        LeftDrive.spin(forward, total, pct);
        RightDrive.spin(reverse, total, pct);

        perror = error;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}*/

static void drivePID(double kp, double ki, double kd, double target) {
    double lefterror = target;
    double plefterror = lefterror;
    double leftd = 0;
    double lefti = 0;
    double reallefti = 0;
    double plefttotal = 0;
    double lefttotal = 0;
    double leftsaturation = 0;
    double leftsign = 0;

    double righterror = target;
    double prighterror = righterror;
    double rightd = 0;
    double righti = 0;
    double realrighti = 0;
    double prighttotal = 0;
    double righttotal = 0;
    double rightsaturation = 0;
    double rightsign = 0;
    
    LeftDrive.resetPosition();
    RightDrive.resetPosition();
    
    while((fabs(lefterror) + fabs(righterror)) / 2 > 0.5) {
        lefterror = target - LeftDrive.position(turns) * 3.25 * M_PI * 0.75;
        righterror = target - RightDrive.position(turns) * 3.25 * M_PI * 0.75;
        
        leftd = (lefterror - plefterror) * 40;
        rightd = (righterror - prighterror) * 40;
        
        lefttotal = lefterror * kp + lefti * ki - leftd * kd;
        righttotal = righterror * kp + righti * ki - rightd * kd;

        if(plefttotal == lefttotal) {
            leftsaturation = 0;
        }
        else {
            leftsaturation = 1;
        }
        if((plefttotal < 0) && (lefttotal < 0)) {
            leftsign = -1;
        }
        else {
            leftsign = 1;
        }

        if(prighttotal == righttotal) {
            rightsaturation = 0;
        }
        else {
            rightsaturation = 1;
        }
        if((plefttotal < 0) && (lefttotal < 0)) {
            rightsign = -1;
        }
        else {
            rightsign = 1;
        }

        LeftDrive.spin(forward, lefttotal, pct);
        RightDrive.spin(forward, righttotal, pct);

        if((leftsaturation == 1) || (leftsign == 1 )) {
            lefti = 0;
        }
        else {
           lefti = reallefti; 
        }
        if(fabs(lefterror) < 10) {
            reallefti += lefterror / 50;
        }
        
        if((rightsaturation == 1) || (rightsign == 1 )) {
            righti = 0;
        }
        else {
          righti = realrighti;  
        }
        if(fabs(righterror) < 10) {
            realrighti += righterror / 50;
        }

        plefterror = lefterror;
        prighterror = righterror;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

static double geterror(double target) {
    if((std::max(target, Inertial.heading()) - std::min(target, Inertial.heading())) > 180) {
        if(std::min(target, Inertial.heading()) == target) {
            return (360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
        else {
            return -(360 - std::max(target, Inertial.heading()) + std::min(target, Inertial.heading()));
        }
    }
    else {
        return (target - Inertial.heading());
    }
}

static void turnPID(double kp, double ki, double kd, double target) {
    double error = geterror(target);
    double perror = error;
    double d = 0;
    double i = 0;
    double reali = 0;
    double ptotal  = 0;
    double total = 0;
    double saturation = 0;
    double sign = 0;
    //Bohan is the sigmest rookie this year asdfasdfasdfasdfasdfasdfasdf
    while(fabs(error) > 1 || (d > 3)) {
        error = geterror(target);
        d = (error - perror) * 40;
        ptotal = total;
        total = error * kp + i * ki - d * kd;
        if(ptotal == total) {
            saturation = 0;
        }
        else {
            saturation = 1;
        }
        if((ptotal < 0) && (total < 0)) {
            sign = -1;
        }
        else {
            sign = 1;
        }
        
        LeftDrive.spin(forward, total, pct);
        RightDrive.spin(reverse, total, pct);

        if((saturation == 1) && (sign == 1)) {
            i = 0;
        }
        else {
            i = reali;
        }
        if(fabs(error) < 20) {
            i += error/50;
        }
        
        perror = error;

        wait(20, msec);
    }

    LeftDrive.stop(brake);
    RightDrive.stop(brake);

    wait(100, msec);
}

static void drive(std::string direction, double target) {
    if(direction == "forward") {            
        drivePID(1.8, 0.001, 0.75, target);
    }

    if(direction == "reverse") {
        drivePID(1.8, 0.001, 0.75, -target);
    }
}

static void turn(double target) {
    turnPID(0.42, 0.001, 0, target);
}

void AWPRed() {
    turn(90);
}

void AWPBlue() {

}

void Red() {

}

void Blue() {

}

void AutonSkills() {

}

void TestPID() {
    // Initial setup
    Intake.setVelocity(100, pct);
  
    // Step 1: Drive forward to approach the scoring location
    drive("forward", 20); // Drive forward 20 inches
  
    // Step 2: Score a ring using the intake
    Intake.spin(reverse); // Eject the ring
    wait(500, msec);
    Intake.stop();
  
    // Step 3: Turn right towards the center tower
    turn(90); // Turn 90 degrees right
  
    // Step 4: Drive forward to touch center tower
    drive("forward", 15); // Drive forward 15 inches to reach tower
    wait(300, msec); // Brief wait to ensure contact
  
    // Step 5: Back away from tower
    drive("reverse", 10); // Back up 10 inches
  
    // Step 6: Turn towards corner
    turn(135); // Turn to face corner
  
    // Step 7: Drive to corner with mobile goal
    drive("forward", 25); // Drive to corner
  
    // Step 8: Secure the mobile goal using pneumatic
    P.set(true); // Activate pneumatic to secure the mobile goal
  
    // Step 9: Small adjustment to position better in corner
    drive("forward", 2); // Fine adjustment
}

// Alternative autonomous function approach (without PID functions)
void CustomAuton() {
    // Initial setup
    Intake.setVelocity(100, pct);
    LeftDrive.setVelocity(50, pct);
    RightDrive.setVelocity(50, pct);
  
    // Move forward to approach scoring location
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    wait(2000, msec);  // Time-based movement instead of PID
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
  
    // Score a ring using the intake
    Intake.spin(reverse);
    wait(500, msec);
    Intake.stop();
  
    // Turn right towards the center tower
    LeftDrive.spin(forward);
    RightDrive.spin(reverse);
    wait(1000, msec);  // Time-based turning
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
  
    // Drive forward to touch center tower
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    wait(1500, msec);
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
    
    // Brief wait to ensure contact
    wait(300, msec);
  
    // Back away from tower
    LeftDrive.spin(reverse);
    RightDrive.spin(reverse);
    wait(1000, msec);
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
  
    // Turn towards corner
    LeftDrive.spin(forward);
    RightDrive.spin(reverse);
    wait(1300, msec);  // ~135 degrees based on timing
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
  
    // Drive to corner with mobile goal
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    wait(2500, msec);
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
  
    // Secure the mobile goal using pneumatic
    P.set(true);
  
    // Optional: small adjustment to position better in corner
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    wait(200, msec);  // Small movement
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
}
