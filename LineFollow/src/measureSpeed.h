/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: measureSpeed.h
*
* Description:: Define struct use for keeping track of an individual
* motor with its CE pin number, last count read, and time
*
**************************************************************/
#ifndef MEASURE_SPEED_H
#define MEASURE_SPEED_H

#include <stdlib.h>
#include "ls7336r.h"
#include <math.h>


typedef struct {
    int CE;
    int lastCount;
    uint32_t lastTimeMicroseconds;
} MotorSpeedTracker;

extern MotorSpeedTracker * motorA;
extern MotorSpeedTracker * motorB;
extern MotorSpeedTracker * motorC;
extern MotorSpeedTracker * motorD;


MotorSpeedTracker * initSpeedCounter(int CE);

double getSpeed(MotorSpeedTracker * motor);
int initSpeedTrackers();
void terminateSpeedTrackers();
void printAllSpeed();

#endif