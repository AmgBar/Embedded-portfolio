/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Andres Garcia Barros
* Student ID:: 921107769
* Github-Name:: AmgBar
* Project:: Assignment 4 - Follow The line but stop
*
* File:: followLine.c
*
* Description:: Using the IR Obstacle Sensor and the Line sensor, 
* their input will be read in order tell tell the user whether the 
* sensors are over Black or white and the other sensor will be used 
* to tell the user if there is an obstruction in front of the sensor
* or not. This will be done using threads, one thread for each sensor
* and a main loop that checks values. This file contains the working
* source code running each sensor in its own thread while the main while
* loop checks the values of each sensor individually.
*
**************************************************************/
#include "followLine.h"

//Threads for sensors
pthread_t obstacleSensorThread;
pthread_t lineSensorThread;

//Integers to write sensor values
int * obstacleSensorReading;
int * lineSensorReading;

//Mutex locks for main loop and respective sensors to use
pthread_mutex_t obstacleSensorLock;
pthread_mutex_t lineSensorLock;

bool programIsRunning = true;
struct sigaction sa;

int main(){
    //Initialization of gpio library, mutex locks, gpio pins, and signal handler
    if(gpioInitialise() < 0){
        printf("GPIO initialization failed\n");
        return -1;
    }
    obstacleSensorReading = malloc(sizeof(int));
    lineSensorReading = malloc(sizeof(int));

    sa.sa_handler = handleUsrInterrupt;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    gpioSetMode(OBSTACLE_SENSOR_GPIO_PIN, PI_INPUT);
    gpioSetMode(LINE_SENSOR_GPIO_PIN, PI_INPUT);

    pthread_mutex_init(&obstacleSensorLock, NULL);
    pthread_mutex_init(&lineSensorLock, NULL);

    //Have to pass constants into int variables or else code won't work :(
    int obsPin = OBSTACLE_SENSOR_GPIO_PIN;
    int linSPin = LINE_SENSOR_GPIO_PIN;

    pthread_create(&obstacleSensorThread, NULL, sensorRead, (void *) &obsPin);
    pthread_create(&lineSensorThread, NULL, sensorRead, (void *) &linSPin);

    printf("\033[2J");
    printf("\033[H");

    //Prints values of sensors, grabs lock of sensor that it will read
    //as to not load a value that may have changed
    while(1){
        printf("\033[H");

        pthread_mutex_lock(&obstacleSensorLock);
        printf("\rOBSTACLE SENSOR READS:\t%d\t%-20s\n", *obstacleSensorReading, obstacleSensorOutput(*obstacleSensorReading));
        pthread_mutex_unlock(&obstacleSensorLock);

        pthread_mutex_lock(&lineSensorLock);
        printf("LINE SENSOR READS:\t%d\t%-20s\n", *lineSensorReading, lineSensorOutput(*lineSensorReading));
        pthread_mutex_unlock(&lineSensorLock);

        fflush(stdout);

        sigaction(SIGINT, &sa, NULL);  
        sigaction(SIGTSTP, &sa, NULL);

        usleep(10000);
    }


    return 0;
}

void handleUsrInterrupt(int sig){
    printf("\nUser interrupt detected...exiting follow line\n");
    //Stop loops inside threads and wait for them to finish
    programIsRunning = false;
    pthread_join(obstacleSensorThread, NULL);
    pthread_join(lineSensorThread, NULL);
    
    //Clean up
    gpioTerminate();
    free(obstacleSensorReading);
    free(lineSensorReading);
    pthread_mutex_destroy(&lineSensorLock);
    pthread_mutex_destroy(&obstacleSensorLock);

    exit(0);
}

//Reads respective sensor value and places into the pointer
void * sensorRead(void * sensor){
    // Lock will vary depending on which sensor this function was entered from
    pthread_mutex_t * sensorLock;
    int sensorPin = *(int * )sensor;

    // Sets this thread's lock accordingly
    if(sensorPin == OBSTACLE_SENSOR_GPIO_PIN)
        sensorLock = &obstacleSensorLock;
    else
        sensorLock = &lineSensorLock;
    
    // Sets this thread's place to store values accordingly
    int * reading; 
    if(sensorPin == OBSTACLE_SENSOR_GPIO_PIN)
        reading = obstacleSensorReading;
    else
        reading = lineSensorReading;

    // Lock makes sure that thread will not change value as it is 
    // read by main loop and vice versa
    while(programIsRunning){
        pthread_mutex_lock(sensorLock);
        *reading = gpioRead(sensorPin);
        pthread_mutex_unlock(sensorLock);
    }
    return NULL;
}

// Descriptive meanings of readings
static char * lineSensorOutput(int reading){
    if(reading == 1)
        return "(On Line)\0";
    else
        return "(Off Line)\0";

}
static char * obstacleSensorOutput(int reading){
    if(reading == 1)        
        return "(No Obstruction)\0";

    else
        return "(Sensor Obstructed)\0";


}