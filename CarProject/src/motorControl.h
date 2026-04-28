/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: motorControl.h
*
* Description:: Header file for motorControl, defines bunch
*   of addresses, bits, etc. for motors A and B, functions
*   and enums
*
**************************************************************/
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <unistd.h>
#include <stdlib.h>
#include "ls7336r.h"
#include "i2cPigpio.h"

#define FRONTWHEEL_ADDRESS          0x56
#define BACKWHEEL_ADDRESS           0x40
#define MODE1                       0x00
#define MAX_SPEED_VALUE             4095

#define OFF                         0
#define ON                          1

/*MOTOR A CONTROLS*/

//PWM A
#define LED0_ON_L                   0x06
#define LED0_ON_H                   0x07
#define LED0_OFF_L                  0x08
#define LED0_OFF_H                  0x09 

#define LED0                        LED0_ON_L
#define MOTOR_A_PWM                 LED0

//AIN2
#define LED1_ON_L                   0x0A
#define LED1_ON_H                   0x0B
#define LED1_OFF_L                  0x0C
#define LED1_OFF_H                  0x0D

#define LED1                        LED1_ON_L
#define MOTOR_A_DIRECTION1          LED1

//AIN1
#define LED2_ON_L                   0x0E
#define LED2_ON_H                   0x0F
#define LED2_OFF_L                  0x10
#define LED2_OFF_H                  0x11

#define LED2                        LED2_ON_L
#define MOTOR_A_DIRECTION2         LED2

/*MOTOR B CONTROLS*/

//BIN1
#define LED3_ON_L                   0x12
#define LED3_ON_H                   0x13
#define LED3_OFF_L                  0x14
#define LED3_OFF_H                  0x15 

#define LED3                        LED3_ON_L
#define MOTOR_B_DIRECTION1          LED3

//BIN2
#define LED4_ON_L                   0x16
#define LED4_ON_H                   0x17
#define LED4_OFF_L                  0x18
#define LED4_OFF_H                  0x19

#define LED4                        LED4_ON_L
#define MOTOR_B_DIRECTION2          LED4

//PWM B
#define LED5_ON_L                   0x1A
#define LED5_ON_H                   0x1B
#define LED5_OFF_L                  0x1C
#define LED5_OFF_H                  0x1D

#define LED5                        LED5_ON_L
#define MOTOR_B_PWM                 LED5

extern int frontHandle;
extern int backHandle;

typedef enum{
    FRONT,
    BACK
} Handle;

// void restartRegisters(int);
// int setSpeedPercentage(int, int, int);
// void switchLED(int, int, int);
// void wakeMotorDriverHat(int);

// void turnOnPWM(int, int);
// void turnOffPWM(int, int);

// void turnOnMotorDirection(int, int);
// void turnOffMotorDirection(int, int);

void moveForward(unsigned int speedPercentage);
void moveBackward(unsigned int speedPercentage);

void moveLeftWheelForward(Handle fd, int speedPercentage);
void moveRightWheelForward(Handle handle, int speedPercentage);

void moveLeftWheelBackward(Handle handle, int speedPercentage);
void moveRightWheelBackward(Handle handle, int speedPercentage);

int initializeMotors();
int terminateMotors();
#endif