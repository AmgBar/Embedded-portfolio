/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: lineSensor.c
*
* Description:: Controls the line sensor for reading, and
*   decides what direction the car should go into
*
**************************************************************/
#include <myPigpio.h>
#include <unistd.h>
#include "lineSensor.h"

#define LEFT_LINE_GPIO 25
#define MIDDLE_LINE_GPIO 24
#define RIGHT_LINE_GPIO 23

volatile int leftLine = 0;
volatile int middleLine = 0;
volatile int rightLine = 0;

int endLineSensorThread = 0;
int currentPriority = 1;

// Initalizes the line sensors
// Returns 0 on success
int initLineSensors() {
    endLineSensorThread = 1;
    initPin(LEFT_LINE_GPIO, PI_INPUT);
    initPin(MIDDLE_LINE_GPIO, PI_INPUT);
    initPin(RIGHT_LINE_GPIO, PI_INPUT);

    return 0;
}

// Terminates the line sensors
// Returns 0 on success
int terminateLineSensors(){
    endLineSensorThread = 0;
    usleep(100);
    initPin(LEFT_LINE_GPIO, PI_OUTPUT);
    initPin(MIDDLE_LINE_GPIO, PI_OUTPUT);
    initPin(RIGHT_LINE_GPIO, PI_OUTPUT);

    return 0;
}

// Function used by threads to run the line sensors
void *readLineSensors(void *arg) {
    while(endLineSensorThread != 0) {
        
        leftLine = readPin(LEFT_LINE_GPIO);
        middleLine = readPin(MIDDLE_LINE_GPIO);
        rightLine = readPin(RIGHT_LINE_GPIO);
        
        usleep(70000);
    }
    return NULL;
}

/*
*   Calculates the direction the car should go based
*   off the last read line sensor values
*   Returns: Dir enum of where to go
*/
Dir getDirection() {
    Dir dir = NONE;

    if(middleLine && leftLine && rightLine){
        return NONE;
    }

    if (middleLine) {
        if (leftLine){
            dir = CURVE_LEFT;
        }else if (rightLine){
            dir = CURVE_RIGHT;
        }else
            dir = FORWARD;
    }
    else {
        if (leftLine && !rightLine)
            dir = FORWARD_LEFT;
        else if (!leftLine && rightLine)
            dir = FORWARD_RIGHT;
        else
            dir = NONE;
    }

    return dir;
}