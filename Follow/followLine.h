/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 4 - Follow The line but stop
*
* File:: followLine.h
*
* Description:: Using the IR Obstacle Sensor and the Line sensor, 
* their input will be read in order tell tell the user whether the 
* sensors are over Black or white and the other sensor will be used 
* to tell the user if there is an obstruction in front of the sensor
* or not. This will be done using threads, one thread for each sensor
* and a main loop that checks values. This file contains the function
* definitions of those used in the working program, dependencies, and
* GPIO pin definitions for the sensors.
*
**************************************************************/
#ifndef FOLLOWLINE_H
#define FOLLOWLINE_H

#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

#define OBSTACLE_SENSOR_GPIO_PIN    22
#define LINE_SENSOR_GPIO_PIN        17

void handleUsrInterrupt(int);
void * sensorRead(void * );
static char *  lineSensorOutput(int reading);
static char *  obstacleSensorOutput(int reading);
#endif