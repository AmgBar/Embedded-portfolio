/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: assignment2.h
*
* Description:: This file contains definitions, librariesm and
* helper functions in order to measure real time distance with 
* the HC SR04 echo sensor using a raspberry pi and its GPIO pins
*
**************************************************************/

#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define TRIGGER 22
#define ECHO 17

//Ctrl-c and ctrl-z signal Handler
void handleUsrInterrupt(int sig);
void triggerPulse(int pin, int microseconds);