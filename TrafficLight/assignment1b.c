/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 1 - Traffic Light
*
* File:: assignment1b.c
*
* Description:: This file defines the functions declared in the 
* assignment1b.h file. These functions make use of sysfs to write 
* to files that control the GPIO pins of the raspberrypi. First 
* are the low level functions that write to the GPIO files then
* wrapper functions that use the other functions in the context 
* of the GPIO pins being used to connect LEDs.
*
**************************************************************/
#include "assignment1b.h"


//Exports pin to be able to be used
static int exportPin(int pin){
	pin = pin + 512;
	char buffer[BUFFER_MAX];
	int fd;
	//Opens the export file 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	int bytesToWrite;
	if(fd < 0){
		printf("Failed to open GPIO export file\n");
		return -1;
	}
	//Writes pin number to export file so that system knows that 
	// it can be used
	bytesToWrite = snprintf(buffer, BUFFER_MAX, "%d", pin);
	if(write(fd, buffer, bytesToWrite) <= 0){
		printf("Unable to write to GPIO export file\n");
		return -1;
	}
	close(fd);
	return 0;
}

//Unexports pin so that it can not be used
static int unexportPin(int pin){
	pin = pin + 512;

	char buffer[BUFFER_MAX];
	int fd;
	//Opens unexport file
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	int bytesToWrite;
	if(fd < 0){
		printf("Failed to open GPIO unexport file\n");
		return -1;
	}
	//Write to the unexport file so that system knows that it
	//cannot be used anymore
	bytesToWrite = snprintf(buffer, BUFFER_MAX, "%d", pin);
	if(write(fd, buffer, bytesToWrite) <= 0){
		printf("Unable to write to GPIO unexport file\n");
		return -1;
	}
	close(fd);
	return 0;
}

//Sets the behavior of exported pin to either transmit output or 
//receive input
static int setDirection(int pin, int direction){
	pin = pin + 512;

	char path[PATH_MAX];
	int fd;
	int writtenSuccessfully;
	char directionString[4];
	int  bytesToWrite;

	//Open direction file of respective pin
	snprintf(path, PATH_MAX, "/sys/class/gpio/gpio%d/direction\0", pin);
	fd = open(path, O_WRONLY);
	if (fd < 0) {
		printf("Failed to open %s file\n", path);
		return -1;
	}

	//Write direction into direction file
	if(direction == OUT){
		bytesToWrite = snprintf(directionString, DIRECTION_STR_MAX, "out");
	}else{
		if(direction == IN){
			bytesToWrite = snprintf(directionString, DIRECTION_STR_MAX, "in");
		}else{
			printf("Direction not recognized\n");
			return -1;
		}
	}

	writtenSuccessfully = write(fd, directionString, bytesToWrite);

	if (writtenSuccessfully < 0) {
		printf("Failed to set direction!\n");
		return -1;
	}

	close(fd);
	return(0);
}

//Sets value of gpio pin to either emit a high voltage or a low voltage
static int setValue(int pin, int value){
	pin = pin + 512;

	char valueString[2];
	char path[PATH_MAX];
	int fd;
	int writtenSuccessfully;
	int bytesToWrite;
	//Open value file for the GPIO pin
	snprintf(path, PATH_MAX, "/sys/class/gpio/gpio%d/value\0", pin);
	fd = open(path, O_WRONLY);
	bytesToWrite = snprintf(valueString, 2, "%d", value);

	if (fd < 0) {
		printf("Failed to open gpio value for writing! %s\n", path);
		return(-1);
	}
	
	writtenSuccessfully = write(fd, valueString, bytesToWrite);

	if (writtenSuccessfully == -1) {
		printf("Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

//Gets the specified led ready to turn on
static void initializeLed(int pin){
	printf("Initializing GPIO pin %d\n", pin);
	exportPin(pin);
	setDirection(pin, OUT);
}

//Turn off led and make it unusable
static void uninitializeLed(int pin){
	printf("Unitializing GPIO pin %d\n", pin);
	turnOffLed(pin);
	unexportPin(pin);
}
static void turnOnLed(int pin){
	setValue(pin, HIGH);
}
static void turnOffLed(int pin){
	setValue(pin, LOW);
}
//Turns on led for a specified amount of time in microseconds
static void turnOnTimer(int pin, int microseconds){
	turnOnLed(pin);
	usleep(microseconds);
	turnOffLed(pin);
}


int main(){
	printf("Controlling LEDs with sysfs\n");
	//Initialize pins that will be used to turn on LEDs
	initializeLed(GREENLED);
	initializeLed(YELLOWLED);
	initializeLed(REDLED);

	//Blink LEDs for number of cycles specified
	printf("Running...\n");
	for(int i = 0; i < CYCLES; i++){
		turnOnTimer(GREENLED, 6 * 1000000);
		turnOnTimer(YELLOWLED, 1.5 * 1000000);
		turnOnTimer(REDLED, 5 * 1000000);
	}
	
	//Turn off and unexport LEDs
	uninitializeLed(GREENLED);
	uninitializeLed(YELLOWLED);
	uninitializeLed(REDLED);
	
	return 0;
}
