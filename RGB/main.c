/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: main.c
*
* Description:: The example of how one would import and use
*   our created library
*
**************************************************************/

#include "./src/rgbSensor.h"
#include <signal.h>
#include <stdlib.h>

#define LED_PIN     22

void signalHandler(int signal){
    printf("\n");
    exit(terminateRGBSensor());
}

int main(){
    if(initRGBSensor(LED_PIN) != 0){
        printf("ERROR: failed to initalize RGB Sensor!\n");
        return -1;
    }

    RGB rgb;

    signal(SIGINT, signalHandler);

    sleep(1.5);
    for(int i = 0; i < 2; i++){
        rgb = getRGB();
        printAll(rgb);
        sleep(1);
    }

    return terminateRGBSensor();
}
