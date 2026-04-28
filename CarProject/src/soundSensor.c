/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: soundSensor.c
*
* Description:: File for the use of a HC-SR04 sensors via
*   thread, initalization, termination, and getting distance
*   in cm.
*
**************************************************************/

#include <pthread.h>
#include "myPigpio.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "soundSensor.h"

#define FRONT_TRIG          26
#define FRONT_ECHO          16

#define SPEED_OF_SOUND      0.03430 // Speed of sound in cm/microseconds
#define MAX_TIME            2750*2 // Max possible time the module can read

pthread_mutex_t soundLock;

double frontDist = -1.0;

int endSensor = 1;

// Initalizes the use of the sound sensor
// Return 0 on success, 1 on failure
int initSoundSensor(){
    if(initPin(FRONT_ECHO, PI_INPUT) || initPin(FRONT_TRIG, PI_OUTPUT)){
        return 1;
    }

    if (pthread_mutex_init(&soundLock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    return 0;
}

// Terminates the sound sensor
// Return 0 on success, 1 on failure
int terminateSoundSensor(){
    endSensor = 0;
    usleep(60000);
    while(readPin(FRONT_ECHO) == 1);
    if(initPin(FRONT_ECHO, PI_OUTPUT)){
        return 1;
    }
    pthread_mutex_destroy(&soundLock);

    return 0;
}

// Shoots sound from trig pin
void shootSound(int pin){
    gpioWrite(pin, 1);
    usleep(10);
    gpioWrite(pin, 0);
}


/*
*   Code found: https://stackoverflow.com/questions/38831057/
*   Accurately calculates the time difference in microseconds
*   between a start and end time 
*   Returns the time difference
*/
__uint64_t calculateTime(struct timeval start, struct timeval end){
    __uint64_t time = 0;
    __uint64_t seconds = (end.tv_sec - start.tv_sec);
    __uint64_t useconds = (end.tv_usec - start.tv_usec);
    // printf("seconds vs useconds: %d %d\n", seconds, useconds);
    time = seconds * 1000000 + useconds;

    return time;
}

__uint64_t releasePulse(){
    struct timeval start, end;
    __uint64_t elapsed = 0, temp = 0;

    unsigned int trig, echo;
    trig = FRONT_TRIG;
    echo = FRONT_ECHO;

    // Don't shoot the sound until the echo pin
    // is properly back to 0 - LOW state
    while(readPin(echo) == 1);
    createDelay(10);

    // Shoot sound and wait until echo is not low
    shootSound(trig);
    while(readPin(echo) == 0);

    // Starts time reading
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    // Waits until echo is low again or scuffed timer exceeds max time
    while(readPin(echo) != 0 && temp < MAX_TIME){
        temp += 1;
        gettimeofday(&end, NULL);
    }

    if(temp >= MAX_TIME){
        elapsed = 0;
    } else {
        elapsed = calculateTime(start, end);
    }
    
    return elapsed;
}

/*
*   Calls func to activate the sound pulse and calcs the distance
*   from the time value returned
*   Returns the calculated distance in cm
*/
double measureCM(){    
    double dist = 0;
    dist = (double)(releasePulse() * SPEED_OF_SOUND)/2;
    return dist;
}

// Threaded function to run and get distance from super sonic sensor
void* runSoundSensor(void* args){
    
    while(endSensor != 0){
        double newDist = -1;

        newDist = measureCM();
        pthread_mutex_lock(&soundLock);
        frontDist = newDist;
        pthread_mutex_unlock(&soundLock);
        createDelay(500);
    }    
    return NULL;
}

// Called by other functions, gets the last read distance,
// Returns: double of the distance in cm
double getDistance(){
    double r = -1;
    pthread_mutex_lock(&soundLock);
    r = frontDist;
    pthread_mutex_unlock(&soundLock);

    if(r <= 2){
        r = 0;
    }
    return r;
}