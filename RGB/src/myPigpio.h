/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: myPigpio.h
*
* Description:: mypigpio header to define functions for it
*
**************************************************************/


#ifndef MY_PIGPIO_H
#define MY_PIGPIO_H

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <stdint.h>

int initalizePiGPIO(void);
int terminatePiGPIO(void);
int initPin(unsigned int pin, unsigned pinMode);
int setPinPull(unsigned int pin, unsigned mode);
int setPWM(unsigned int pin, unsigned int power);
uint32_t createDelay(unsigned int time);

#endif