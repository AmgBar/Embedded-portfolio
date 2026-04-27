/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: TCS34725.h
*
* Description:: The header file for TCS34725.c to define
*   functions and macros for addresses in the sensor
*
*   Code built off from:
*   https://github.com/adafruit/Adafruit_TCS34725/tree/master
*
**************************************************************/

#ifndef TCS34725_H
#define TCS34725_H

#include <stdint.h>
#include "classifyColor.h"

#define TCS34725_CMD_BIT        0x80
#define RGB_SENSOR_ADDRESS      0x29

#define ENABLE_REG              0x00
#define INTEGRATION_TIME        0x01
#define GAIN                    0x0F

#define INTEGRATIONTIME_24MS    0xFF
#define INTEGRATIONTIME_300MS   0x83
#define INTEGRATIONTIME_614MS   0x00

#define GAIN_1X                 0x00
#define GAIN_4X                 0x01
#define GAIN_16X                0x02
#define GAIN_60X                0x03  

#define ENABLE_PON              0x01
#define ENABLE_AEN              0x02

#define CLEAR_DATA_LOW_BYTE     0x14
#define CLEAR_DATA_HIGH_BYTE    0x15

#define RED_DATA_LOW_BYTE       0x16
#define RED_DATA_HIGH_BYTE      0x17

#define GREEN_DATA_LOW_BYTE     0x18
#define GREEN_DATA_HIGH_BYTE    0x19

#define BLUE_DATA_LOW_BYTE      0x1A
#define BLUE_DATA_HIGH_BYTE     0x1B

RGB readSensor();
RGB getSensor();
RGB getRawColor();
RGB recalcColor(RGB color);
RGB getColor();
enum ColorEnum getEnum();
RGB checkBlackWhite(RGB color);
const char * classifyColor(RGB input);
uint16_t calcColorNorm(int val, int clear, int clearNorm);
int initTCS34725(unsigned int newCmdBit);

#endif
