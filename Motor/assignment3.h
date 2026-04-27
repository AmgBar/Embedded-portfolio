/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 3 - Start Your Motor
*
* File:: assignment3.h
*
* Description:: This file contains the definitions of the values
* that represent addresses of the registers used in the Motor Driver HAT
* It also contains definitions for the functions which will control
* basic functionality for the motor such as setting speed percentage,
* restarting registers, and switching states of the motor input.
*
**************************************************************/
#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H
#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MOTOR_HAT_I2C_ADDRESS       0x40
#define MODE1                       0x00
#define MAX_SPEED_VALUE             4095

#define OFF                         0
#define ON                          1

#define BUTTON_GPIO_PIN                  17

/*MOTOR A CONTROLS*/

//PWM A
#define LED0_ON_L                   0x06
#define LED0_ON_H                   0x07
#define LED0_OFF_L                  0x08
#define LED0_OFF_H                  0x09 
#define LED0                        LED0_ON_L

//AIN2
#define LED1_ON_L                   0x0A
#define LED1_ON_H                   0x0B
#define LED1_OFF_L                  0x0C
#define LED1_OFF_H                  0x0D
#define LED1                        LED1_ON_L

//AIN1
#define LED2_ON_L                   0x0E
#define LED2_ON_H                   0x0F
#define LED2_OFF_L                  0x10
#define LED2_OFF_H                  0x11
#define LED2                        LED2_ON_L


/*MOTOR B CONTROLS*/

//BIN1
#define LED3_ON_L                   0x12
#define LED3_ON_H                   0x13
#define LED3_OFF_L                  0x14
#define LED3_OFF_H                  0x15 
#define LED3                        LED3_ON_L

//BIN2
#define LED4_ON_L                   0x16
#define LED4_ON_H                   0x17
#define LED4_OFF_L                  0x18
#define LED4_OFF_H                  0x19
#define LED4                        LED4_ON_L

//PWM B
#define LED5_ON_L                   0x1A
#define LED5_ON_H                   0x1B
#define LED5_OFF_L                  0x1C
#define LED5_OFF_H                  0x1D
#define LED5                        LED5_ON_L

void restartRegisters(int);
int setSpeedPercentage(int, int);
void switchLED(int, int, int);

#endif