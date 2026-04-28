/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: lineSensor.h
*
* Description:: Header for line sensor, defines functions
*   and an enum used to help tell where teh car should go
*
**************************************************************/

#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

typedef enum{
    FORWARD,
    BACKWARD,
    FORWARD_RIGHT,  // Soft Forward-Right Turn
    FORWARD_LEFT,   // Soft Forward-Left Turn
    BACKWARD_RIGHT,
    BACKWARD_LEFT,
    CURVE_RIGHT,    // Hard Forward-Right Turn
    CURVE_LEFT,     // Hard Forward-Left Turn
    NONE
} Dir;

int initLineSensors();
int terminateLineSensors();
void* readLineSensors(void* arg);
Dir getDirection();

extern volatile int leftLine;
extern volatile int middleLine;
extern volatile int rightLine;

#endif