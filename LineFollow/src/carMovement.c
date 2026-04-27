/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: carMovement.c
*
* Description:: Makes the car actually move forward, backward,
*   forward left/right, etc. called by carBrain.c to move car
*
**************************************************************/
#include "carMovement.h"
#include "lineSensor.h"
#include "motorControl.h"
#include "measureSpeed.h"

Dir currentDirection = NONE;
OmniDir currentOmniDirection = IDLE;


void moveCarForward(int speedPercentage){
    moveForward(speedPercentage);
}

void moveCarBackward(int speedPercentage){
    moveBackward(speedPercentage);
}

void stationaryRightTurn(int speedPercentage){
    moveRightWheelBackward(frontHandle, 0);
    moveRightWheelBackward(backHandle, speedPercentage);

    moveLeftWheelForward(frontHandle, speedPercentage);
    moveLeftWheelForward(backHandle, speedPercentage);    
}

void stationaryLeftTurn(int speedPercentage){
    moveLeftWheelBackward(frontHandle, 0);
    moveLeftWheelBackward(backHandle, speedPercentage);

    moveRightWheelForward(frontHandle, speedPercentage);
    moveRightWheelForward(backHandle, speedPercentage);
    
}

void moveForwardRight(int speedPercentage){
    moveRightWheelForward(frontHandle, speedPercentage * .15);
    moveLeftWheelForward(backHandle, speedPercentage);

    moveRightWheelForward(backHandle, speedPercentage * .15);
    moveLeftWheelForward(frontHandle, speedPercentage);
}

void moveForwardLeft(int speedPercentage){
    moveRightWheelForward(frontHandle, speedPercentage);
    moveLeftWheelForward(backHandle, speedPercentage * .15);

    moveRightWheelForward(backHandle, speedPercentage);
    moveLeftWheelForward(frontHandle, speedPercentage * .15);
}

void omniForwardLeft(int speedPercentage){
    moveRightWheelForward(frontHandle, speedPercentage);
    moveLeftWheelForward(backHandle, speedPercentage);

    moveRightWheelForward(backHandle, 0);
    moveLeftWheelForward(frontHandle, 0);

}

void omniBackwardRight(int speedPercentage){
    moveLeftWheelForward(frontHandle, 0);
    moveRightWheelForward(backHandle, 0);

    moveRightWheelBackward(frontHandle, speedPercentage);
    moveLeftWheelBackward(backHandle, speedPercentage);
}

void omniBackwardLeft(int speedPercentage){
    moveLeftWheelBackward(frontHandle, speedPercentage);
    moveRightWheelBackward(backHandle, speedPercentage);

    moveRightWheelBackward(frontHandle, 0);
    moveLeftWheelBackward(backHandle, 0);
}

void omniMoveLeft(int speedPercentage){
    moveRightWheelForward(frontHandle, speedPercentage);
    moveLeftWheelForward(backHandle, speedPercentage);

    moveRightWheelBackward(backHandle, speedPercentage);
    moveLeftWheelBackward(frontHandle, speedPercentage);
}

void omniMoveRight(int speedPercentage){
    moveRightWheelForward(backHandle, speedPercentage);
    moveLeftWheelForward(frontHandle, speedPercentage);

    moveLeftWheelBackward(backHandle, speedPercentage);
    moveRightWheelBackward(frontHandle, speedPercentage);
}

// Stops the car
void pauseCar(){
    moveRightWheelForward(frontHandle, 0);
    moveLeftWheelForward(backHandle, 0);

    moveLeftWheelBackward(frontHandle, 0);
    moveRightWheelBackward(backHandle, 0);
}

/* 
*   Moves the car based off direction given from line sensor enum
*   @param direction: Line sensor enum direction the car moves towards
*   @param speed: Speed of car
*/
void moveCar(Dir direction, unsigned int speed){
    if(direction != currentDirection && direction != NONE){
        sleep(.35);
        Dir prevDir = currentDirection;
        currentDirection = direction;

        if(speed > 100){
            speed = 100;
        }

        switch(direction){
            case FORWARD:
                moveCarForward(speed);
                break;
            case BACKWARD:
                moveCarBackward(speed);
                break;
            case CURVE_RIGHT:
                // Sleeps car to give enough time to
                // actually rotate and orient it to center line
                sleep(.6);
                if(prevDir != CURVE_LEFT){
                    stationaryRightTurn(speed);
                }   
                sleep(.8);

                break;
            case CURVE_LEFT:
                // Sleeps car to give enough time to
                // actually rotate and orient it to center line
                sleep(.7);
                if(prevDir != CURVE_RIGHT){
                    stationaryLeftTurn(speed);
                }
                sleep(.8);
                break;
            case FORWARD_RIGHT:
                moveForwardRight(speed);
                break;
            case FORWARD_LEFT:
                moveForwardLeft(speed);
                break;

            default: 
                printf("detecting nothing\n");
                sleep(.2);
        }
        sleep(.5);
    }
}

/*
*   Uses the omni-directional wheels to shift
*   the car in a certain direction (either left or right)
*   @param direction: OmniDir enum direction
*   @param speed: Speed of car
*/
void omniMoveCar(OmniDir direction, unsigned int speed){
    if(speed > 100){
        speed = 100;
    }
    currentDirection = NONE;
    currentOmniDirection = direction;

    switch(direction){
        case OMNI_LEFT:
            omniMoveLeft(speed);
            break;
        
        case OMNI_RIGHT:
            omniMoveRight(speed);
            break;
    }
}

/*
*   Used to rotate the car 90 degrees left or right
*   @param direction: Direction enum from line sensor *CURVE_RIGHT/LEFT
*   @param speed: Speed of the car
*/
void rotateCar(Dir direction, unsigned int speed){
    // Sleep for different times as wheels have different powers
    if(direction == CURVE_RIGHT){
        stationaryRightTurn(speed); 
        createDelaySec(1);
        createDelay(274100);
    } else if(direction == CURVE_LEFT){
        stationaryLeftTurn(speed);
        createDelaySec(4);
        createDelay(574100);
    }
}


// Used to rotate the car a full 360 degrees clockwise
void doDonut(){
    stationaryRightTurn(100); 
    createDelaySec(2);
    while(getDirection() != FORWARD);
    while(getDirection() == FORWARD);
    while(getDirection() != FORWARD);
    moveCar(FORWARD, 100);
}
