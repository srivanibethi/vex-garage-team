#pragma once
using namespace vex;


extern brain Brain;
extern controller Controller;

extern motor FL;
extern motor ML;
extern motor BL;
extern motor_group LeftDrive;
extern motor FR;
extern motor MR;
extern motor BR;
extern motor_group RightDrive;

extern digital_out P;
extern digital_out D;

extern motor Intake1;
extern motor Intake2;
extern motor_group Intake;
extern rotation Rotation;
extern motor WallStake;

extern inertial Inertial;

void vexcodeInit(void);
