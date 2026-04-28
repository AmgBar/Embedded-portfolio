/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: motorControl.c
*
* Description: Implementation of car movements and manuevers. 
* Implemented in this file is the code necessary to configure
* the motor hat to allow movements.
*
**************************************************************/
#include "motorControl.h"
#include "lineSensor.h"

int frontHandle = -1;
int backHandle = -1;

// "Wakes" up motor hat to enable use
void wakeMotorDriverHat(int handle){
    writeByteI2C(handle, MODE1, 0x01);
}

// Enables pwm for motor hat
void turnOnPWM(int handle, int motorPWM){
    writeByteI2C(handle, motorPWM + 3, 0x00);
}

// Disables pwm
void turnOffPWM(int handle, int motorPWM){
    writeByteI2C(handle, motorPWM + 3, 0x10);
}

// Sets the speed of a hat
int setSpeed(int handle, int motorPWM, unsigned int speed){
    // Edge Cases
    if(speed > 100){
        speed = 100;
    }

    if(speed == 100){
        writeByteI2C(handle, motorPWM + 1, 0x10);
        writeByteI2C(handle, motorPWM, 0x00);
        return 1;
    }
    
    float truePercentage = (100 - speed) / 100.0;
    int calculatedSpeedValue = (MAX_SPEED_VALUE * truePercentage) / 1;

    // Separate speed value's bits in order 
    // to put them in their respective registers
    int valueInLow = calculatedSpeedValue & 0xFF;
    int valueInHigh = (calculatedSpeedValue >> 8) & 0xF;

    writeByteI2C(handle, motorPWM, valueInLow);
    writeByteI2C(handle, motorPWM + 1, valueInHigh);

    return calculatedSpeedValue;
}

// Return all registers to their default states using LED_ALL registers
void restartRegisters(int motorDriverHandle){
    // Turn LED_ON_H registers off
    writeByteI2C(motorDriverHandle, 0xFB, 0x00);
    // Turn LED_ON_L registers off
    writeByteI2C(motorDriverHandle, 0xFA, 0x00);
    // Turn LED_OFF_H registers on
    writeByteI2C(motorDriverHandle, 0xFD, 0x10);
    // Set sleep bit
    writeByteI2C(motorDriverHandle, 0x00, 0x11);
}

// Turns on or off and LED by setting the respective registers to that state
void switchLED(int handle, int LED, int state){
    // Modify LED_ON registers
    writeByteI2C(handle, LED, state);
    writeByteI2C(handle, LED + 1, state);
    // Modify LED_OFF registers
    writeByteI2C(handle, LED + 2, (state + 1) % 2);
    writeByteI2C(handle, LED + 3, (state + 1) % 2);
}

void turnOnMotorDirection(int handle, int motorDirection){
    switchLED(handle, motorDirection, ON);
}

void turnOffMotorDirection(int handle, int motorDirection){
    switchLED(handle, motorDirection, OFF);

}

void moveLeftWheelForward(Handle fd, int speedPercentage){
    int handle = frontHandle;
    if(fd == BACK){
        handle = backHandle;
    }
    
    turnOffMotorDirection(handle, MOTOR_A_DIRECTION2);
    turnOnMotorDirection(handle, MOTOR_A_DIRECTION1);
    setSpeed(handle, MOTOR_A_PWM, speedPercentage);
}

void moveLeftWheelBackward(Handle fd, int speedPercentage){
    int handle = frontHandle;
    if(fd == BACK){
        handle = backHandle;
    }

    turnOffMotorDirection(handle, MOTOR_A_DIRECTION1);
    turnOnMotorDirection(handle, MOTOR_A_DIRECTION2);
    setSpeed(handle, MOTOR_A_PWM, speedPercentage);
}

void moveRightWheelForward(Handle fd, int speedPercentage){
    int handle = frontHandle;
    if(fd == BACK){
        handle = backHandle;
    }

    turnOffMotorDirection(handle, MOTOR_B_DIRECTION2);
    turnOnMotorDirection(handle, MOTOR_B_DIRECTION1);
    setSpeed(handle, MOTOR_B_PWM, speedPercentage);
    
}

void moveRightWheelBackward(Handle fd, int speedPercentage){
    int handle = frontHandle;
    if(fd == BACK){
        handle = backHandle;
    }

    turnOffMotorDirection(handle, MOTOR_B_DIRECTION1);
    turnOnMotorDirection(handle, MOTOR_B_DIRECTION2);
    setSpeed(handle, MOTOR_B_PWM, speedPercentage);

}

void moveForward(unsigned int speedPercentage){
    moveLeftWheelForward(frontHandle, speedPercentage);
    moveLeftWheelForward(backHandle, speedPercentage);

    moveRightWheelForward(frontHandle, speedPercentage);
    moveRightWheelForward(backHandle, speedPercentage);
}

void moveBackward(unsigned int speedPercentage){
    moveLeftWheelBackward(frontHandle, speedPercentage);
    moveLeftWheelBackward(backHandle, speedPercentage);

    moveRightWheelBackward(frontHandle, speedPercentage);
    moveRightWheelBackward(backHandle, speedPercentage);
}

int openHandle(unsigned int address){
    int handle = initI2C(address);
    if(handle < 0){
        printf("Unable to open MOTOR DRIVER HAT i2c device\n");
        return -1;
    }
    wakeMotorDriverHat(handle);

    turnOnPWM(handle, MOTOR_A_PWM);
    turnOnPWM(handle, MOTOR_B_PWM);

    setSpeed(handle, MOTOR_A_PWM, 0);
    setSpeed(handle, MOTOR_B_PWM, 0);
    
    return handle;
}


int initializeMotors(){
    frontHandle = openHandle(FRONTWHEEL_ADDRESS);
    backHandle = openHandle(BACKWHEEL_ADDRESS);

    if(frontHandle < 0 || backHandle < 0){
        frontHandle = -1;
        backHandle = -1;
        return -1;
    }

    return 0;
}

int terminateMotors(){
    restartRegisters(frontHandle);
    restartRegisters(backHandle);

    if(terminateI2C(frontHandle) || terminateI2C(backHandle)){
        return 1;
    }
    
    
    return 0;
}