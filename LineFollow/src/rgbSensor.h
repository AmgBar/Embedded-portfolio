/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: rgbSensor.h
*
* Description:: The header for rgbSensor for defining
*   RGB related functions
*
**************************************************************/

#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include "i2cPigpio.h"
#include "myPigpio.h"
#include "TCS34725.h"
#include "classifyColor.h"

int initRGBSensor();
int terminateRGBSensor();
RGB getRGB();
enum ColorEnum getColorEnum();
void printAll(RGB rgb);
void printRGB(RGB rgb);
void printHex(RGB rgb);
void printColorName(RGB rgb);
#endif