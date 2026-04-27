/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 1 - Traffic Light
*
* File:: assignment1b.h
*
* Description:: This file declares the functions that will be used
* to control the LEDs.These functions make use of sysfs to write 
* to files that control the GPIO pins of the raspberrypi. First 
* are the low level functions that write to the GPIO files then
* wrapper functions that use the other functions in the context 
* of the GPIO pins being used to connect LEDs.
*
**************************************************************/
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "definitions.h"


static int exportPin(int pin);
static int unexportPin(int pin);
static int setDirection(int pin, int dir);
static int setValue(int pin, int value);
static void initializeLed(int pin);
static void uninitializeLed(int pin);
static void turnOnLed(int pin);
static void turnOffLed(int pin);
static void turnOnTimer(int pin, int microseconds);

