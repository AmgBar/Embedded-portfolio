/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
*
* File:: classifyColor.c
*
* Description:: Functions used to help convert RGB struct
* 	into color names
*
**************************************************************/
#include "classifyColor.h"
#include "rgbSensor.h"

uint8_t confidence = 0;


/*
* Measures the distance of color to a given preset color via
* a 3D graph representation
*
* @param c1: rgb struct 1 (usually input)
* @param c2: rgb struct 2 (static color)
*
* Returns: distance from start --> end
*/
double colorDistance(RGB c1, RGB c2) {
	uint16_t redDist, greenDist, blueDist, totalDist;

	// Tones down the preset rgb values if min or maxed
	// for better confidence value
	c2.r = scaleValue(c2.r);
	c2.b = scaleValue(c2.b);
	c2.g = scaleValue(c2.g);

	redDist = pow(c1.r - c2.r, 2);
	greenDist = pow(c1.g - c2.g, 2);
	blueDist = pow(c1.b - c2.b, 2);

	totalDist = sqrt(redDist + blueDist + greenDist);
	
    return totalDist;
}

/*
* Scaled an rgb value up or down depending if its maxed or min
*
* @param val: an rgb val ranging from 0 - 255
*
* Returns: int of the new value
*/
int scaleValue(int val){
	if(val <= 0){
		val += 50;
	} else if(val >= 255){
		val -= 50;
	}

	return val;
}

/*
* Calculates the approxamation of what kind of color it is
*
* @param input: rgb struct input
*
* Returns: String of the approxamation of color
*/
const char * classifyColor(RGB input){
	return enumToString(classifyColorEnum(input));
}

/*
* Calculates the approxamation of what kind of color it is
*
* @param input: rgb struct input
*
* Returns: Enum of the approxamation of color
*/
enum ColorEnum classifyColorEnum(RGB input){
    enum ColorEnum bestMatch = COLOR_UNKNOWN;
	double minDistance = 1e11;
	double dist = 0.0;
	
	if(input.r == 0 && input.g == 0 && input.b){
		return COLOR_BLACK;
	}

    for (int i = 0; i < COLOR_COUNT; i++) {
        dist = colorDistance(input, colors[i]);

        if (dist < minDistance) {
            minDistance = dist;
            bestMatch = i;
        }
    }

	calcConfidence(dist);
    
	return bestMatch;
}


/*
* Calculates the confidence value based off given min distance
*
* @param dist: min distance found
*/
void calcConfidence(double dist){
	double d = (dist - 25)/442; // (min distance - leeway)/max distance)
	confidence = (1 - d) * 100; // into percentage
	if(confidence > 100){
		confidence = 100;
	}	
}

/*
* Returns the confidence value of the previously calculated color
*
* Returns: the confidence value
*/
uint8_t getConfidence(){
	return confidence;
}

/*
* Converts given color enum to string variant
*
* @param color: color enum val
*
* Returns: A color string
*/
const char * enumToString(enum ColorEnum color){
	switch(color) {
    	case COLOR_BLACK:
			return "Black";
			break;
    	case COLOR_WHITE:
			return "White";
			break;
    	case COLOR_RED:
			return "Red";
			break;
    	case COLOR_GREEN:
			return "Green";
			break;
		// case COLOR_TAPE_GREEN:
		// 	return "Tape Green";
		// 	break;
		case COLOR_TARP:
			return "Tarp";
			break;
        default:
	    	return "Unknown";
    }
}