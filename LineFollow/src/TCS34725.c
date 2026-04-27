/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: TCS34725.c
*
* Description:: The file used for controlling the use of
*   retrieving colors from the rgb sensor and calculating
*   it to human vision
*   
*   Code built off from:
*   https://github.com/adafruit/Adafruit_TCS34725/tree/master
*
**************************************************************/

#include "TCS34725.h"
#include "myPigpio.h"
#include "i2cPigpio.h"
#include <math.h>

unsigned int cmdBit = 0x00;

int rgbFD = -1;

/*
* Inits the sensor, call before use
* 
*  Returns: 0 --> success | 1 --> fail
*/
int initTCS34725(unsigned int newCmdBit){
    cmdBit = newCmdBit;

    rgbFD = initI2C(RGB_SENSOR_ADDRESS);
    if(rgbFD < 0){
        terminatePiGPIO();
        return 1;
    }

    // Set integration time to average
    if(writeByteI2C(rgbFD, INTEGRATION_TIME | cmdBit, INTEGRATIONTIME_24MS)){
        return 1;
    }
    
    // Set gains to 60x
    if(writeByteI2C(rgbFD, GAIN | cmdBit, GAIN_60X)){
        return 1;
    }

    // Actually enables the RGB device
    if(writeByteI2C(rgbFD, ENABLE_REG | cmdBit, ENABLE_PON)){
        return 1;
    }

    createDelay(3);
    if(writeByteI2C(rgbFD, ENABLE_REG | cmdBit, ENABLE_PON | ENABLE_AEN)){
        return 1;
    }

    createDelay(70);

    return 0;
}

/*
* Gets the raw color detected from the sensor
*
* Returns: RGB struct of the color read by sensor
*/
RGB getRawColor(){
    RGB rgb = getSensor();
    uint16_t sum = rgb.c;
 
    if(sum == 0){
        rgb.r = 0;
        rgb.b = 0;
        rgb.g = 0;

        return rgb;
    }

    // Normalized values in the raw state
    rgb.c = (float)rgb.c / 65535.0;
    rgb.r =  (float)rgb.r / (float)sum * 256;
    rgb.g = (float)rgb.g / (float)sum * 256;
    rgb.b =  (float)rgb.b / (float)sum * 256;

    return rgb;
}

/*
* Gets the color detected from the sensor, recalcs the human vison color
*
* Returns: RGB struct of the color read calcutated towards human vision
*/
RGB getColor(){
    RGB rgb = getSensor();
    rgb = recalcColor(rgb);
    return rgb;
}

/*
* Gets the color detected from the sensor, recalcs the human vison color
*
* Returns: Color enum of the color read calcutated towards human vision
*/
enum ColorEnum getEnum(){
    RGB rgb = getSensor();
    rgb = recalcColor(rgb);
    // printf("rgb is %d %d %d\n", rgb.r, rgb.g, rgb.b);
    if(rgb.r == 0 && rgb.g == 0 && rgb.b == 0){
        return COLOR_BLACK;
    }
    return classifyColorEnum(rgb);
}

/*
* Gets the color dected from the sensor
*
* Returns: RGB struct of the color read, returns 0, 0, 0, 0 if error
*/
RGB getSensor(){
    RGB temp;
    double clear, red, green, blue;

    clear = readWordI2C(rgbFD, CLEAR_DATA_LOW_BYTE | cmdBit);
    createDelay(10);
    red = readWordI2C(rgbFD, RED_DATA_LOW_BYTE | cmdBit);
    createDelay(10);
    green = readWordI2C(rgbFD, GREEN_DATA_LOW_BYTE | cmdBit);
    createDelay(10);
    blue = readWordI2C(rgbFD, BLUE_DATA_LOW_BYTE | cmdBit);
    createDelay(10);

    if(clear < 0 || red < 0 || green < 0 || blue < 0){
        temp.c = 0;
        temp.r = 0;
        temp.g = 0;
        temp.b = 0;

        return temp;
    }

    temp.c = (uint16_t) clear;
    temp.r = (uint16_t) red;
    temp.g = (uint16_t) green;
    temp.b = (uint16_t) blue;

    return temp;
}

/*
* Determines if the color closely resembles black or white and
* switches it to the respective color if so
*
* @param color: color
*
* Returns: new RGB struct
*/
RGB checkBlackWhite(RGB color){
    uint8_t largest = 0, id = 0;
	uint8_t colors[] = {color.r, color.g, color.b};
	uint8_t difference[] = {0, 0};
	uint16_t clear = color.c;
	
	// Finds largest color value
	for(uint8_t i = 0; i < 3; i++){
		if(colors[i] > largest){
			largest = colors[i];
			id = i;
		}
	}

	// Finds the difference between largest color val and other 2
	uint8_t j = 0;
	for(uint8_t i = 0; i < 3; i++){
		if(i != id){
			difference[j] = largest - colors[i];
			j += 1;
		}
	}

    // Too much difference in rgb, most likely not black nor white
    if(difference[0] > 40 || difference[1] > 40){
        return color;
    }

    // Most likely white
    if(clear > 800){
        RGB new = {255, 255 , 255, clear};
        return new;
    } 
    // Most likely black
    if(largest < 60 && clear < 250){
        RGB new = {0, 0 , 0, clear};
        return new;
    }

    return color;
}

/*
* Calcs the norm of the color based off the clear and clamps
* it down to either 0 or 255 if less than or greater. Also
* recalibrates the normalized value if the clear is low or high enough
*
* @param val: color to be calced
* @param clear: value of clear
* @param clearNorm: value of clearNorm
*
* Returns: uint16 of color norm value
*/
uint16_t calcColorNorm(int val, int clear, int clearNorm){
    // Most likely color would be black based off clear
    if(clear < 250){
        val = (val - 40) * (1 + clearNorm)/1.5;

    // Most likely color would be white based off clear value
    } else if(clear > 650){
        val = (val + 40) * (1 + clearNorm)*1.5;

    } else {
        val = val * (1 + clearNorm);

    }

    if(val > 255){
        val = 255;
    } else if(val < 0){
        val = 0;
    }

    return val;
}

/*
* Recalculates the color given into more human readable RGB
*
* @param color: A color struct collected from sensor
*
* Returns: RGB struct of the color based on human vision
*/
RGB recalcColor(RGB color){
    RGB rgb = color;
    uint16_t sum = rgb.c;
    
    if(sum == 0){
        rgb.r = 0;
        rgb.b = 0;
        rgb.g = 0;

        printf("HELLO WORLD!\n");
        return rgb;
    }
    // Calcs initial norm values
    int clearNorm = (float)rgb.c / 65535.0;
    int redNorm =  (float)rgb.r / (float)sum * 256;
    int greenNorm = (float)rgb.g / (float)sum * 256;
    int blueNorm =  (float)rgb.b / (float)sum * 256;

    redNorm = calcColorNorm(redNorm, sum, clearNorm);
    greenNorm = calcColorNorm(greenNorm, sum, clearNorm);
    blueNorm = calcColorNorm(blueNorm, sum, clearNorm);
    
    rgb.r = redNorm;
    rgb.g = greenNorm;
    rgb.b = blueNorm;

    // Sensor cannot detect black or white easily
    rgb = checkBlackWhite(rgb);

    return rgb;
}
