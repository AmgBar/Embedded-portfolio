/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: myPigpio.c
*
* Description:: pigpio library functions for quick and easy
*   access for things like initalizing pins
*
**************************************************************/
#include "myPigpio.h"


// Initializes the PiGPIO DMA setup, call before use
int initalizePiGPIO(){
    // DEBUG: printf("Using PI GPIO Version: %d\n", gpioVersion());
    if(gpioInitialise() < 0){
        // GPIO FAILED
        printf("ERROR, initalizePiGPIO failed! Pi Init Failed!\n");
        return 1;
    } 
    return 0;
}

// Terminates the DMA, call before exiting
int terminatePiGPIO(){
    gpioTerminate();
    return 0;
}

/*
* Initalizes a given pin to input/output 
*
* @param pin: given gpio pin
* @param pinMode: Selected pin mode
*
* returns: 0 on success, 1 on bad pin mode, -1 on gpio failure
*/
int setPWM(unsigned int pin, unsigned int power){
    int feedback = 0;

    if(power > 255){
        power = 255;
    }

    feedback = gpioPWM(pin, power);

    switch(feedback){
        case PI_BAD_USER_GPIO:
            printf("ERROR, setPWM failed! Bad PI user GPIO detected!\n");
            break;
        
        case PI_BAD_DUTYCYCLE:
            printf("ERROR, setPWM failed! Bad Dutycycle!\n");
            break;
        
        default: 
            createDelay(50);// ensures pwm change goes through
            
    }

    return feedback;
}

/*
* Initalizes a given pin to input/output 
*
* @param pin: given gpio pin
* @param pinMode: Selected pin mode
*
* returns: 0 on success, 1 on bad pin mode, -1 on gpio failure
*/
int initPin(unsigned int pin, unsigned pinMode){
    int gpioResult = -1;
    if(pinMode != PI_INPUT && pinMode != PI_OUTPUT){
        printf("Error: Invalid pin mode(0-1) given: %d\n", pinMode);
        return 1;
    }

    gpioResult = gpioSetMode(pin, pinMode);

    if(gpioResult != 0){
        switch (gpioResult){
            case PI_BAD_GPIO:
                printf(
                    "%s%d%s%d\n", 
                    "ERROR, set mode failed due to bad GPIO pin on pin ", 
                    pin, 
                    "\nError code: ", 
                    gpioResult
                );
                break;
            
            
            case PI_BAD_MODE:
                printf(
                    "%s%d%s%d\n", 
                    "ERROR, bad mode for GPIO pin ", 
                    pin, 
                    "\nError code: ", 
                    gpioResult
                );
                break;
            
    
            default:
                printf(
                    "%s%d%s%d\n", 
                    "ERROR, unexpected error occured on pin ", 
                    pin, 
                    "\nError code: ", 
                    gpioResult
                );            
        }
        
        return -1;
    
    }
    
    return 0;
}

/*
* Sets a given pin to a given pin pull mode
*
* @param pin: Given GPIO pin
* @param mode: Selected mode (0 - 2)
*
* returns 0 on success, 1 on invalid pull mode
*/
int setPinPull(unsigned int pin, unsigned mode){
    if(mode < 0 || mode > 2){
        printf("Error: mode given is out of bounds(0-2): %d\n", mode);
        return 1;
    }
    gpioSetPullUpDown(pin, mode);
    return 0;
}

uint32_t createDelay(unsigned int time){
    return gpioDelay(time);
}