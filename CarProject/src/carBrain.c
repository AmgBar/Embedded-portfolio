/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: carBrain.c
*
* Description:: The logic used to decide what the car has
*   to do in its situation based off line sensors, distance
*   given from ultrasonic sound module, and rgb sensor
*
**************************************************************/
#include "lineSensor.h"
#include "carMovement.h"
#include "soundSensor.h"
#include "carBrain.h"
#include "rgbSensor.h"
#include <stdio.h>
#include <unistd.h>

#define STOP_DISTANCE           12.0

volatile double distance = -1;
volatile Dir lineSensor = NONE; 
volatile enum ColorEnum rgbSensor = COLOR_UNKNOWN;

int canDonut = 1;
volatile int donutCounter = 0;

// Calculates the difference in distance between 2 given measurements
double distanceDifference(double d1, double d2){
    double largest = d2, smallest = d1, sum;
    if(d1 < 0|| d2 < 0){
        return -1;
    }

    if(d1 > d2){
        largest = d1;
        smallest = d2;
    }
    return largest - smallest;
}

// Makes the car rotate and spin around in a donut
void donutMode(){
    doDonut();
}

// Makes the car avoid an obstacle by using omni direction wheels to move
// left, until it passes it then goes forward, and when it reads it passes
// it from the side, it goes right then back forward when on line
void avoidObstacleMode(){
    double dist = getDistance();
    volatile Dir currentDir = getDirection();
    
    // Straighten out the car
    while(currentDir != FORWARD){
        if(currentDir == CURVE_LEFT || currentDir == FORWARD_LEFT){
            stationaryLeftTurn(100);
        } else if(currentDir == CURVE_RIGHT || currentDir == FORWARD_RIGHT){
            stationaryRightTurn(100);
        }
        currentDir = getDirection();
    }

    // Move car far enough left to avoid obstacle
    dist = getDistance();
    while(dist > 0 && dist < STOP_DISTANCE * 1.6){
        pauseCar();
        createDelay(100);
        dist = getDistance();
        createDelay(100);
        omniMoveCar(OMNI_LEFT, 100);
        createDelaySec(1);
    }
    omniMoveCar(OMNI_LEFT, 100);
    createDelaySec(3);

    // rotate car 90 degrees clockwise and omni-shift it 
    // left to move on the side of the obstacle
    rotateCar(CURVE_RIGHT, 100);
    
    createDelaySec(1);
    dist = getDistance();

    // Initially doesn't detect obstacle after rotation,
    // shift it left until it starts detecting it
    while(dist <= 0 || dist > STOP_DISTANCE * 2.25){
        pauseCar();
        createDelay(100);
        dist = getDistance();
        createDelay(100);
        omniMoveCar(OMNI_LEFT, 100);
        createDelaySec(1);
    }

    // While it continues to detect said obstacle, keep shifting left
    while(dist < STOP_DISTANCE * 2.25 && dist > 0){
        pauseCar();
        createDelay(100);
        dist = getDistance();
        createDelay(100);
        omniMoveCar(OMNI_LEFT, 100);
        createDelaySec(1);
    }
    
    // Obstacle assumed to be passed, turn and move car back onto line
    // It assumes there will be a straight line after the obstacle
    createDelaySec(3);
    // createDelay();
    rotateCar(CURVE_LEFT, 100);
    omniMoveCar(OMNI_RIGHT, 100);

    // Wait until only middle line sensor detects line, then resume
    while(getDirection() != FORWARD);
    distance = 0;
}

/* 
*   Idles in place and calibrates if the car should go around an object
*   or resume activity by comparing the starting and ending idle distances.
*   Returns 0 on resume activity, 1 to run "Avoid Obstacle Mode"
*/
int idleMode(double startDist){
    double start = startDist;
    double end;
    pauseCar();
    sleep(10);
    end = getDistance();

    // If the obstacle remains there, it will attempt to go around it
    if(end > 0 && distanceDifference(start, end) <= STOP_DISTANCE){
        printf("Obstacle remaining stationary, moving around it!\n");
        return 1;
    } else {
        printf("Obstacle no longer detected, resuming activity,\n");
        return 0;
    }
}

// Drives the car according to line sensor
void defaultMode(Dir lineSensor){
    unsigned int temp = 0;
    if(lineSensor == NONE){
        while(getDirection() == NONE && temp < 100000){
            temp += 1;
            usleep(1);
        }
    
        // Attempts to drive backwards to get back on
        // the line if the car drives out of the line
        if(temp >= 100000){
            moveCar(BACKWARD, 100);
        } else {
            moveCar(lineSensor, 100);
        }
    } else {
        moveCar(lineSensor, 100);
    }
}

// The algorithm to decide what to do with the information provided
// by the: Line sensors, rgb sensor, and ultrasonic sensor
// Returns 0 on normal execution, returns 1 on red line detected
int runAlgorithm(){
    distance = getDistance();
    lineSensor = getDirection();
    rgbSensor = getColorEnum();

    // Reset donut toggle
    if(canDonut == 0){
        donutCounter += 1;
        if(donutCounter >= 10000){
            donutCounter = 0;
            canDonut = 1;
        }
    }


    switch(rgbSensor){
        case COLOR_RED:         // red adjacent color, intential fall through
        case COLOR_RED2:
        // case COLOR_CLEAN_RED:
        // case COLOR_CLEAN_RED2:
        // case COLOR_MAROON:
            printf("Car detecting red on line; terminating!\n");
            return 1;
            break;
        // default:
        //     printf("reading %s", );

        case COLOR_GREEN:       // intential fall through
        case COLOR_GREEN2:
        // case COLOR_TAPE_GREEN:
        // case COLOR_TAPE_GREEN2:
            if(canDonut == 1){
                printf("Car detecting green on line; doing donut.\n");
                donutMode();
                canDonut = 0;
            }
            
            break;
    }

    // If object is detected closely to the car
    if(distance <= STOP_DISTANCE && distance > 0){
        // Obstacle too close, temp stop the car
        printf("an object is being detected!\n");

        // Stops the car and checks whether to proceed back to
        // resuming activity or start avoiding an obstacle
        if(idleMode(distance) == 0){
            defaultMode(lineSensor);
        } else {
            avoidObstacleMode();
        }
    } else {
        defaultMode(lineSensor);
    }

    return 0;
}





