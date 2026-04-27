/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: assignment2.c
*
* Description:: This file contains the working source code to 
* measure real time distance with the HC SR04 echo sensor using
* a raspberry pi and its GPIO pins
*
**************************************************************/
#include "assignment2.h"

int main(){

    int startTimeSeconds;
    int startTimeMicroseconds;
    int endTimeSeconds;
    int endTimeMicroseconds;

    //Setup to safely handle interrupt signal and exit program
    struct sigaction sa;
    sa.sa_handler = handleUsrInterrupt;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(gpioInitialise() < 0){
        printf("Unable to initialize GPIO library\n");
        return -1;
    }

    gpioSetMode(TRIGGER, PI_OUTPUT);
    gpioSetMode(ECHO, PI_INPUT);

    //Delay to make sure components are ready
    gpioWrite(TRIGGER, PI_LOW);
    usleep(2000);
  
    //Program will continue running until user interrupts with ctrl-c or ctrl-z
    while(1){

        triggerPulse(TRIGGER, 10);
    
        //Record start time as right before ECHO pin is pulled up by transmitter sending ultrasonic
        while(gpioRead(ECHO) == 0)
            gpioTime(PI_TIME_RELATIVE, &startTimeSeconds, &startTimeMicroseconds);

        //Record end time as right before ECHO pin is pulled down by receiver receiving ultrasonic
        while(gpioRead(ECHO) == 1)
            gpioTime(PI_TIME_RELATIVE, &endTimeSeconds, &endTimeMicroseconds); 


        //Calculations
        double timeTravelled = (endTimeSeconds - startTimeSeconds) +  ((endTimeMicroseconds - startTimeMicroseconds) / 1000000.0);
        double distance = timeTravelled * 340 / 2 * 100;
        printf("Object distance: %.2fcm\n", distance);

        //Handle interrupt signal
        sigaction(SIGINT, &sa, NULL);  
        sigaction(SIGTSTP, &sa, NULL);

        usleep(200000);
    }
    return 0;

}


void handleUsrInterrupt(int sig){
    //Close GPIO library before exiting
    printf("\nUser interrupt detected...exiting tapeless ruler\n");
    gpioTerminate();
    exit(0);
}

void triggerPulse(int pin, int microseconds){
    //Trigger pulse
    gpioWrite(pin, PI_HIGH);
    usleep(microseconds);
    gpioWrite(pin, PI_LOW);
}

