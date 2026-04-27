/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: i2cPigpio.h
*
* Description:: Header file for i2cPigpio to control i2c
*   within gpio functions
*
**************************************************************/

#ifndef I2C_PIGPIO_H
#define I2C_PIGPIO_H

#include <pigpio.h>
#include <stdint.h>
#include <stdio.h>

int initI2C(unsigned int address);
void setCmdBit(uint16_t bit);
int readWordI2C(unsigned int reg);
int readByteI2C(unsigned int reg);
int writeI2C(unsigned int reg, unsigned int value);
int terminateI2C();

#endif