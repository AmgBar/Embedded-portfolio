/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: measureSpeed.c
*
* Description:: Implementation of using MotorSpeedTracker stuct
* to keep track of motor speed.
*
**************************************************************/
#include "measureSpeed.h"

MotorSpeedTracker * motorA = NULL;
MotorSpeedTracker * motorB = NULL;
MotorSpeedTracker * motorC = NULL;
MotorSpeedTracker * motorD = NULL;

// Initalizes the speed trackers for the hall effect motors
// Returns 0 on success, -1 on failure to init
int initSpeedTrackers(){
    motorA = initSpeedCounter(SPI0_CE0);
    motorB = initSpeedCounter(SPI0_CE1);
    motorC = initSpeedCounter(SPI0_CE2);
    motorD = initSpeedCounter(SPI0_CE3);

    if(motorA == NULL || motorB == NULL || motorC == NULL || motorD == NULL){
        return -1;
    }

    return 0;
}

// Terminates all speed trackers
void terminateSpeedTrackers(){
    bbSPIClose(SPI0_CE0);
    bbSPIClose(SPI0_CE1);
    bbSPIClose(SPI0_CE2);
    bbSPIClose(SPI0_CE3);

    free(motorA);
    free(motorB);
    free(motorC);
    free(motorD);

    motorA = NULL;
    motorB = NULL;
    motorC = NULL;
    motorD = NULL;
}

// Initalizes a speed counter on a motor
// Returns NULL if fails to allocate, struct on success
MotorSpeedTracker * initSpeedCounter(int CE){
    if (initLS7336RChip(CE) != 0) {
        return NULL;
    }

    MotorSpeedTracker * motor = (MotorSpeedTracker*)malloc(sizeof(MotorSpeedTracker));

    if (motor == NULL) {
        return NULL; 
    }

    motor->CE = CE;
    motor->lastCount = 0;
    motor->lastTimeMicroseconds;

    return motor;
}

// Gets the speed of a specific motor
double getSpeed(MotorSpeedTracker * motor){
    int result = readLS7336RCounter(motor->CE);
    // Gets current time
    uint32_t currentTimeMicroseconds = gpioTick();

    int countDifference = result - motor->lastCount;
    uint32_t timeDifferenceMicroseconds = currentTimeMicroseconds - motor->lastTimeMicroseconds;

    double timeDifferencseconds = timeDifferenceMicroseconds / 1e6;

    //Calculate speed: absoulute value prevents negative values due to relative motor direction
    //4 * 540 is the value that the encoder board reads after one full rotation with the 4 byte counter mode enabled
    //.065 is the diameter of the wheels in meters
    double speedInMetersPerSecond = fabs(((result - motor->lastCount)/(4*540.0))*3.1415926 * .065) / timeDifferencseconds;
    motor->lastCount = result;
    motor->lastTimeMicroseconds = currentTimeMicroseconds;

    return speedInMetersPerSecond;
}


void printAllSpeed(){
    printf(
        "\nSpeed of motor A: %f\nSpeed of motor B: %f \nSpeed of motor C: %f\nSpeed of motor D: %f\n",
        getSpeed(motorA), 
        getSpeed(motorB), 
        getSpeed(motorC), 
        getSpeed(motorD)
    );
}