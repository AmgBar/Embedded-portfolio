/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: i2cPigpio.c
*
* Description:: The pigpio i2c write functions used
*   as a library, mainly for the motors and rgb sensor
*
**************************************************************/

#include "i2cPigpio.h"

/*
* Call to initalize the use of i2cPigpio, opens the i2c to the specified
* address
*
* @param address: address of the i2c
*
* Returns: >= 0 --> handle | < 0 --> init failed
*/
int initI2C(unsigned int address){
    int fd = i2cOpen(1, address, 0);

    switch(fd){
        // i2c open failed
        case PI_BAD_I2C_BUS:
            printf("ERROR: initI2C failed! Bad PI I2C bus detected!\n");
            break;

        case PI_BAD_I2C_ADDR:
            printf("ERROR: initI2C failed! Bad PI I2C address detected!\n");
            break;

        case PI_BAD_FLAGS:
            printf("ERROR: initI2C failed! Bad PI flag detected!\n");
            break;

        case PI_NO_HANDLE:
            printf("ERROR: initI2C failed! No handle detected!\n");
            break;

        case PI_I2C_OPEN_FAILED:
            printf("ERROR: initI2C failed! i2cOpen() failed!\n");
            break;
        
        // default: do nothing, everything is ok

    }

    return fd;
}


/*
* Reads a 1 byte from the handle from a given register
*
* @param reg: Register to read from
*
* Returns: >= 0 --> Byte Read | < 0 --> error occured
*/
int readByteI2C(unsigned int handle, unsigned int reg){
    int fd = handle;
    int readByte = -1;

    readByte = i2cReadByteData(fd, reg);

    switch(readByte){
        case PI_BAD_HANDLE:
            printf("ERROR, readI2C failed! Bad PI handle detected");
            break;

        case PI_BAD_PARAM:
            printf("ERROR, readI2C failed! Bad PI parameter detected");
            break;

        case PI_I2C_READ_FAILED:
            printf("ERROR, readI2C failed! i2cReadByteData() failed!");
            break;
        
        // default: everything is okay
    }   

    return readByte;

}


/*
* Reads a 2 bytes from the handle from a given register
*
* @param reg: Register to read from
*
* Returns: >= 0 --> Byte Read | < 0 --> error occured
*/
int readWordI2C(unsigned int handle, unsigned int reg){
    int fd = handle;
    int readByte = -1;

    readByte = i2cReadWordData(fd, reg);

    switch(readByte){
        case PI_BAD_HANDLE:
            printf("ERROR, readI2C failed! Bad PI handle detected");
            break;

        case PI_BAD_PARAM:
            printf("ERROR, readI2C failed! Bad PI parameter detected");
            break;

        case PI_I2C_READ_FAILED:
            printf("ERROR, readI2C failed! i2cReadByteData() failed!");
            break;
        
        // default: everything is okay
    }   

    return readByte;

}
/*
* Writes a single byte to the handle at the given register
*
* @param reg: Register to write to
* @param value: Value to write (unsigned int, casted to byte)
*
* Returns: 0 --> Success | < 0 --> error occurred
*/
int writeByteI2C(unsigned int handle, unsigned int reg, unsigned int value){
    int fd = handle;
    int result = i2cWriteByteData(fd, reg, value);

    switch(result){
        case PI_BAD_HANDLE:
            printf("ERROR, writeI2C failed! Bad PI handle detected\n");
            break;

        case PI_BAD_PARAM:
            printf("ERROR, writeI2C failed! Bad PI parameter detected\n");
            break;

        case PI_I2C_WRITE_FAILED:
            printf("ERROR, writeI2C failed! i2cWriteByteData() failed!\n");
            break;

        // default: success
    }

    return result;
}


/*
* Call to terminate an i2c handle
*
* Returns: 0 --> success | -2 on failure
*/
int terminateI2C(unsigned int handle){
    int feedback = -1;

    feedback = i2cClose(handle);
    if(feedback == PI_BAD_HANDLE){
        printf("ERROR, terminateI2C failed! Bad PI Handle detected!\n");
        return -2;
    }

    return feedback;
}