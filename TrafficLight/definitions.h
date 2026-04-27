/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 1 - Traffic Light
*
* File:: definitions.h
*
* Description:: This file defines constants which both assignment1b.c
* and assignment1pigpio.c use to clearly label the behavior of the GPIO pins
* in the context of controlling LEDs
*
**************************************************************/

#define CYCLES	3

#define GREENLED 22
#define YELLOWLED 27
#define REDLED 17

#define LOW  0
#define HIGH 1

#define IN 0
#define OUT 1

#define BUFFER_MAX 5
#define PATH_MAX 50
#define DIRECTION_STR_MAX 4