/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: rgbSensor.c
*
* Description:: The 'main' file for the library, 
*   Will be used by the user to initalize, the use of the
*   RGB Sensor (TCS 34725) and terminate, along with 
*   getting the color in RGB value and HEX
*
**************************************************************/

#include "rgbSensor.h"

#include <stdlib.h>

int ledPin = -1;

/*
* Initalizes everything needed for the use of the RGB
* Sensor
*
* @param pin: GPIO pin connected to LED
*
* returns: 0 on success, 1 on bad pin mode, -1 on gpio failure
*/
int initRGBSensor(uint8_t pin){
    if(initalizePiGPIO()){
        return 1;
    }

    if(initI2C(RGB_SENSOR_ADDRESS)){
        terminatePiGPIO();
        return 1;
    }

    // sets up pin, pwm and starts the rgb sensor
    if(initPin(pin, PI_OUTPUT) || setPWM(pin, 150) || initTCS34725()){
        terminateI2C();
        terminatePiGPIO();
        return 1;
    }

    setCmdBit(TCS34725_CMD_BIT);
    
    ledPin = pin;
    
    // ensures every change goes through
    sleep(1);

    return 0;
}

/*
* Terminates the use of the active rgb sensor
*
* returns: 0 on success, 1 failure
*/
int terminateRGBSensor(){
    if(ledPin == -1){
        return -1;
    }

    if(setPWM(ledPin, 0) == 0){
        ledPin = -1;
    }

    createDelay(50);

    if(terminateI2C() != 0 || terminatePiGPIO() != 0){
        return 1;
    }
    

    return 0;
}

/*
* Gets the current detected color from the RGB Sensor
*
* returns: RGB Struct on success, null on failure
*/
RGB getRGB(){
    return getColor();
}


/*
* Prints the given rgb as rgb, hex, and approxmiated color
*
* @param rgb: rgb struct
*/
void printAll(RGB rgb){
    printRGB(rgb);
    printHex(rgb);
    printColorName(rgb);
}

/*
* Prints the given rgb struct as rgb [0-255] range with clear
*
* @param rgb: rgb struct
*/
void printRGB(RGB rgb){
    printf("RGB | R: %d\tG: %d\tB: %d\tC: %d\n", rgb.r, rgb.g, rgb.b, rgb.c);
}

/*
* Prints the given rgb as hex
*
* @param rgb: rgb struct
*/
void printHex(RGB rgb){
    printf("Hex Code: #%.2x%.2x%.2x\n", rgb.r, rgb.g, rgb.b);
}

/*
* Prints the given rgb as approxmiated color
*
* @param rgb: rgb struct
*/
void printColorName(RGB rgb){
    printf(
        "Color recognized as: %s, confidence: %d\%\n", 
        classifyColor(rgb), 
        getConfidence()
    );
}
