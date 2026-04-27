/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: carMovement.h
*
* Description:: Defines functions and an enum used for
*   moving the car
*
**************************************************************/
#ifndef CAR_MOVEMENT_H
#define CAR_MOVEMENT_H

#include "lineSensor.h"

typedef enum{
    OMNI_LEFT,
    OMNI_RIGHT,
    IDLE
} OmniDir;

void moveCar(Dir direction, unsigned int speed);
void omniMoveCar(OmniDir direction, unsigned int speed);
void pauseCar();
void rotateCar(Dir direction, unsigned int speed);
void doDonut();
void stationaryRightTurn(int speedPercentage);
void stationaryLeftTurn(int speedPercentage);

#endif