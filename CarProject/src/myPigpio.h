/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: myPigpio.h
*
* Description:: pigpio header to define pigpio related functions
*
**************************************************************/


#ifndef MY_PIGPIO_H
#define MY_PIGPIO_H

#include <pigpio.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int initializePiGPIO(void);
int terminatePiGPIO(void);
int initPin(unsigned int pin, unsigned pinMode);
int initBtn(unsigned int pin);
int setPinPull(unsigned int pin, unsigned mode);
int cleanBtn(unsigned int pin);
int awaitButtonPress(unsigned int pin);
int readPin(unsigned int pin);
int setPWM(unsigned int pin, unsigned int power);
int awaitStateChange(unsigned int pin, unsigned int start);
uint32_t createDelay(unsigned int time);
uint32_t createDelaySec(unsigned int time);

#endif