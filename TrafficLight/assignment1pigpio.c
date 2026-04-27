/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 1 - Traffic Light
*
* File:: assignment1pigpio.c
*
* Description:: This program utilizes the pigpio library to control
* the gpio pins of the raspberry pi. The library already comes with 
* initialize functions, directions functions, and value functions.
*
**************************************************************/
#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "definitions.h"

//Turns on led for a specified amount of time in microseconds
void turnOnTimer(int pin, int microseconds){
	gpioWrite(pin, HIGH);
	usleep(microseconds);
	gpioWrite(pin, LOW);
}

int main(){
	printf("Controlling LEDs with PiGPIO\n");
	if(gpioInitialise() < 0){
		printf("pigpio failed to initialise\n");
		return -1;
	}
	//Initialize pins that will be used to output
	printf("Initializing GPIO pins\n");
	gpioSetMode(GREENLED, OUT);
	gpioSetMode(YELLOWLED, OUT);
	gpioSetMode(REDLED, OUT);

	//Blink LEDs for number of cycles specified
	printf("Running...\n");
	for(int i = 0; i < CYCLES; i++){
		turnOnTimer(GREENLED, 6 * 1000000);
		turnOnTimer(YELLOWLED, 1.5 * 1000000);
		turnOnTimer(REDLED, 5 * 1000000);
	}
	printf("Terminating.\n");
	gpioTerminate();
	return 0;
}

