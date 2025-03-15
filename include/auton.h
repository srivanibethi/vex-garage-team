#ifndef AUTON_H
#define AUTON_H

// Autonomous mode definitions
enum AutonMode {
    AUTON_MODE_RED_POSITIVE = 0,
    AUTON_MODE_BLUE_POSITIVE,
    AUTON_MODE_RED_NEGATIVE,
    AUTON_MODE_SKILLS,
    AUTON_MODE_COUNT
};

// Global definition of which autonomous mode to use
// Change this value when uploading to different brain slots
extern const AutonMode CURRENT_AUTON_MODE;

// Main autonomous functions
void SimpleAutonomous(const char* position);  // Legacy function
void redPositiveAutonomous();
void bluePositiveAutonomous();
void RedNegativeAutonomous();
void skillsAutonomous();
void autonomousRunner(const char* input);

// Helper movement functions
void goForward(double time, int speed);
void goBackward(double time, int speed);
void turnLeft(double time, int speed);
void turnRight(double time, int speed);
void runIntake(int speed);
void stopIntake();
void scoreRings();

// Maintained for backwards compatibility
void ladyBrownUp(double time, int speed);
void ladyBrownDown(double time, int speed);

// String descriptors for each autonomous mode
extern const char* const AUTON_MODE_NAMES[AUTON_MODE_COUNT];

#endif
