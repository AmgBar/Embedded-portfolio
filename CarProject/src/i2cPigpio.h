/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: i2cPigpio.h
*
* Description:: Header for i2c functions used as a library
*   for motors & rgb sensor
*
**************************************************************/

#ifndef I2C_PIGPIO_H
#define I2C_PIGPIO_H

#include "myPigpio.h"

int initI2C(unsigned int address);
int readWordI2C(unsigned int handle, unsigned int reg);
int readByteI2C(unsigned int handle, unsigned int reg);
int writeByteI2C(unsigned int handle, unsigned int reg, unsigned int value);
int terminateI2C(unsigned int handle);

#endif