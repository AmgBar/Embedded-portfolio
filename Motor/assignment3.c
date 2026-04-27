/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 3 - Start Your Motor
*
* File:: assignment3.c
*
* Description:: This file contains the working source code to 
* measure control motor that is connected to a Waveshare Motor
* Driver HAT in motor slot B. The raspberry pi communicates to the
* Motor Driver HAT using I2C communication so this code uses
* PiGPIO libaray i2c functions to control the motor.
*
**************************************************************/
#include "assignment3.h"

//Return all registers to their default states using LED_ALL registers
void restartRegisters(int motorDriverHandle){
    //Turn LED_ON registers off
    i2cWriteByteData(motorDriverHandle, 0xFB, 0x00);
    //Turn LED_OFF registers on
    i2cWriteByteData(motorDriverHandle, 0xFD, 0x10);
    //Set sleep bit
    i2cWriteByteData(motorDriverHandle, 0x00, 0x11);
}

/*
4096 value is slowest speed
1 is the max speed
If I wanted to set the motor to 75 percent speed
4096 * .75 = 3072 which would actually be 25 percent speed
So get percentage argument 100 - % = truePercentage
4096 * truePercentage
*/

int setSpeedPercentage(int motorDriverHandle, int percent){
    //Edge Cases
    if(percent > 100 || percent < 0){
        printf("ERROR: Invalid speed\n");
        return -1;
    }
    if(percent == 100){
        printf("SETTING TO 100%% SPEED\n");
        i2cWriteByteData(motorDriverHandle, LED5_ON_H, 0x10);
        i2cWriteByteData(motorDriverHandle, LED5_ON_L, 0x00);
        return 1;
    }
    float truePercentage = (100 - percent) / 100.0;
    int calculatedSpeedValue = (MAX_SPEED_VALUE * truePercentage) / 1;
    //Separate speed value's bits in order to put them in their respective registers
    int valueInLow = calculatedSpeedValue & 0xFF;
    int valueInHigh = (calculatedSpeedValue >> 8) & 0xF;
    printf("SETTING TO %.0f%% SPEED\n",  100 - (calculatedSpeedValue / 4095.0 * 100) );
    i2cWriteByteData(motorDriverHandle, LED5_ON_L, valueInLow);
    i2cWriteByteData(motorDriverHandle, LED5_ON_H, valueInHigh);

    return calculatedSpeedValue;


}

//Turns on or off and LED by setting the respective registers to that state
void switchLED(int motorDriverHandle, int LED, int state){
    //Modify LED_ON registers
    i2cWriteByteData(motorDriverHandle, LED, state);
    i2cWriteByteData(motorDriverHandle, LED + 1, state);
    //Modify LED_OFF registers
    i2cWriteByteData(motorDriverHandle, LED + 2, (state + 1) % 2);
    i2cWriteByteData(motorDriverHandle, LED + 3, (state + 1) % 2);
}

int main(){

    if(gpioInitialise() < 0){
        printf("Failed to initialize  gpio\n");
        return -1;
    }

    //Set up for button
    gpioSetMode(BUTTON_GPIO_PIN, PI_INPUT);
    printf("Press button to start motor\n");
    while(gpioRead(BUTTON_GPIO_PIN) == 0){

    }

    //Handle to communicate with the Motor Driver Hat
    int motorDriverHandle = i2cOpen(1, MOTOR_HAT_I2C_ADDRESS, 0);

    if(motorDriverHandle < 0){
        printf("Unable to open i2c device\n");
        return -1;
    }

    //Clear sleep bit so motor can start working
    i2cWriteByteData(motorDriverHandle, MODE1, 0x01);

    //Turn on BIN2
    switchLED(motorDriverHandle, LED4, ON);

    //Get PWMB ready
    i2cWriteByteData(motorDriverHandle, LED5_OFF_H, 0x00);

    setSpeedPercentage(motorDriverHandle, 100);
    printf("MAX SPEED FOR 2 SECONDS\n");
    sleep(2);

    printf("SLOWING TO 15 PERCENT\n");
    for(int i = 100; i >= 15; i = i - 5){
        setSpeedPercentage(motorDriverHandle, i);
        usleep(95000);
    }
    sleep(1);

    printf("STOPPING FOR 1 SECOND\n");
    setSpeedPercentage(motorDriverHandle, 0);
    sleep(1);

    //Get motor ready for reverse by turning off BIN2 and turning on BIN1
    switchLED(motorDriverHandle, LED4, OFF);
    switchLED(motorDriverHandle, LED3, ON);

    printf("REVERSING\n");
    for(int i = 0; i <= 100; i = i + 5){
        setSpeedPercentage(motorDriverHandle, i);
        usleep(95000);
    }
    
    sleep(2);

    //Restart i2c device
    restartRegisters(motorDriverHandle);
    i2cClose(motorDriverHandle);
    gpioTerminate();

    return 0;
}

