/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: rgbSensor.h
*
* Description:: The header for rgbSensor for defining
*   some functions
*
**************************************************************/

#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include "i2cPigpio.h"
#include "myPigpio.h"
#include "TCS34725.h"
#include "classifyColor.h"

int initRGBSensor(uint8_t pin);
int terminateRGBSensor();
RGB getRGB();
void printAll(RGB rgb);
void printRGB(RGB rgb);
void printHex(RGB rgb);
void printColorName(RGB rgb);
#endif