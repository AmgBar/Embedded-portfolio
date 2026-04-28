/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: car.c
*
* Description:: Acts as the controller for the car, used
*   for initalizing, terminating, and starting the car
*
**************************************************************/

#include <pthread.h>
#include "rgbSensor.h"
#include "car.h"
#include "motorControl.h"
#include "lineSensor.h"
#include "carBrain.h"
#include "measureSpeed.h"
#include "soundSensor.h"
#include "myPigpio.h"

int enableCar = 1;

pthread_t lineTid, soundTid;

#define BTN_PIN             18

void signalHandler(int signal){
    usleep(10000); // delay to let current pulse send
    int r = terminateCar();
    
    printf("User interrupt detected, shutting down car\n");
    exit(r);
}

/*  
*   Initalizes the use of the car
*   Return 0 on success, 1 on failure
*/
int initCar(){
    if (initializePiGPIO() || initLineSensors()){
        return 1;
    }


    if(initializeMotors() || initSpeedTrackers() || initSoundSensor() ){
        return 1;
    }

    if(initBtn(BTN_PIN) != 0){
        return 1;
    }

    if(initRGBSensor()){
        return 1;
    }

    signal(SIGINT, signalHandler);
    return 0;
}

/*  
*   Terminates the program running
*   Return 0 on success, 1 on failure
*/
int terminateCar(){
    cleanBtn(BTN_PIN);
    pthread_cancel(soundTid);
    pthread_cancel(lineTid);

    if(terminateMotors() || terminateLineSensors()){
        return 1;
    }

    if(terminateRGBSensor()){
        return 1;
    }


    if(terminateSoundSensor()){
        return 1;
    }

    terminateSpeedTrackers();

    if(terminatePiGPIO()){
        return 1;
    }

    return 0;
}

/*  
*   Creates threads and starts running the car after button press
*   Return 0 on successful run, 1 on failure for threads
*/
int startCar(){
    if(pthread_create(&lineTid, NULL, readLineSensors, NULL) != 0){
        printf("ERROR: failed to pthread_create!\n");
        return 1;
    }

    if(pthread_create(&soundTid, NULL, runSoundSensor, NULL) != 0){
        printf("ERROR: failed to pthread_create!\n");
        return 1;
    }

    awaitButtonPress(BTN_PIN);
    sleep(.75);
    while(runAlgorithm() == 0){
        usleep(1000);
    }

    return 0;
}