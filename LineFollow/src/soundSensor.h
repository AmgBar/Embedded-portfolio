/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: soundSensor.h
*
* Description:: Header file for sound sensor, used for
*   defining sound sensor related functions
*
**************************************************************/

#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

void* runSoundSensor(void* args);
double getDistance();
int initSoundSensor();
int terminateSoundSensor();

#endif