/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: i2cPigpio.c
*
* Description:: File for the use of the i2c pigpio functions
*   for the RGB LED sensors
*
**************************************************************/

#include "i2cPigpio.h"

int fd = -1;
uint16_t cmdBit = 0x00;

/*
* Call to initalize the use of i2cPigpio, opens the i2c to the specified
* address
*
* @param address: address of the i2c
*
* Returns: >= 0 --> handle | -1 --> fd initalized previously | 
*          < -1 --> error occured
*/
int initI2C(unsigned int address){
    if(fd >= 0){
        return -1;

    }

    fd = i2cOpen(1, address, 0);

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
* Sets the cmd bit from TCS34725, offsets reads and write functions
*
* @param bit: new cmd bit offset
*/
void setCmdBit(uint16_t bit){
    cmdBit = bit;
}

/*
* Reads a 1 byte from the handle from a given register
*
* @param reg: Register to read from
*
* Returns: >= 0 --> Byte Read | -1 --> handle is not initalized |
*          < -1 --> error occured
*/
int readByteI2C(unsigned int reg){
    int readByte = -1;
    if(fd < 0){
        return -1;

    }
    readByte = i2cReadByteData(fd, cmdBit | reg);

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
* Returns: >= 0 --> Byte Read | -1 --> handle is not initalized |
*          < -1 --> error occured
*/
int readWordI2C(unsigned int reg){
    int readByte = -1;
    if(fd < 0){
        return -1;
    }

    readByte = i2cReadWordData(fd, cmdBit | reg);

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
* Returns: 0 --> Success | -1 --> handle not initialized |
*          < -1 --> error occurred
*/
int writeI2C(unsigned int reg, unsigned int value){
    if(fd < 0){
        return -1;
    }

    int result = i2cWriteByteData(fd, cmdBit | reg, value);

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
* Call to terminate the current i2c
*
* Returns: 0 --> success | -1 --> no handle initalized | -2 on failure
*/
int terminateI2C(){
    int feedback = -1;
    if(fd < 0){
        return -1;
    }

    feedback = i2cClose(fd);
    if(feedback == PI_BAD_HANDLE){
        printf("ERROR, terminateI2C failed! Bad PI Handle detected!\n");
        return -2;
    }

    fd = -1;

    return feedback;
}