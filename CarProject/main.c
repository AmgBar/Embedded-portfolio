/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: main.c
*
* Description:: Activates the car
*
**************************************************************/

#include "src/car.h"
#include <stdio.h>
#include <unistd.h>

//Front Wheels connected to motor hat with address 56
//  Left Wheel: Motor 0
//              Hat MA2 connected to 1 slot
//              Hat MA1 connected to 2 slot
//              Speed read with CE0
//
// Right Wheel: Motor 1
//              Hat MB2 connected to 1 slot
//              Hat MB1 connected to 2 slot
//              Speed read with CE1

//Back Wheels address 40
//  Left Wheel: Motor 1
//              Hat MA2 connected to 2 slot
//              Hat MA1 connected to 1 slot
//              Read with CE2 (GPIO 20) (GPIO 20 to pin CE2 on enocoder board)
//
// Right Wheel: Motor 0
//              Hat MB2 connected to 2 slot
//              Hat MB1 connected to 1 slot
//              Read with CE3 (GPIO 21) (GPIO 21 to pin CE1 on enocoder board)

int main(){
    if(initCar() != 0){
        printf("ERROR: Could not init car\n");
        return 1;
    }

    printf("Car ready to start!\n");
    startCar();
    sleep(1);

    terminateCar();

    sleep(1);
    return 0;
}