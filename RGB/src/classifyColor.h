
/**************************************************************
* Class:: CSC-615-01 Spring 2024
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: AmgBar
* Project:: Assignment 5 - RGB Sensor
*
* File:: classifyColor.h
*
* Description:: Header file for classify color, defines
*   the struct and enums used for color storage and calcs
*
**************************************************************/

#ifndef CLASSIFY_COLOR_H
#define CLASSIFY_COLOR_H

#include <math.h>
#include <stdint.h>

typedef struct{
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
} RGB;

enum ColorEnum{
    COLOR_BLACK,
    COLOR_GRAY,
    COLOR_WHITE,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_MAROON,
    COLOR_OLIVE,
    COLOR_LIME,
    COLOR_NAVY,
    COLOR_TEAL,
    COLOR_PURPLE,
    COLOR_SILVER,
    COLOR_UNKNOWN,  // for fallback
    COLOR_COUNT     // total number of colors
};

static RGB colors[COLOR_COUNT - 1] = {
    {0, 0, 0},       // Black
    {128, 128, 128}, // Gray
    {255, 255, 255}, // White
    {255, 0, 0},     // Red
    {0, 255, 0},     // Green
    {0, 0, 255},     // Blue
    {255, 255, 0},   // Yellow
    {0, 255, 255},   // Cyan
    {255, 0, 255},   // Magenta
    {128, 0, 0},     // Maroon
    {128, 128, 0},   // Olive
    {0, 255, 128},   // Lime
    {0, 0, 128},     // Navy
    {0, 128, 128},   // Teal
    {128, 0, 128},   // Purple
    {192, 192, 192}, // Silver
};

double colorDistance(RGB c1, RGB c2);
int scaleValue(int val);
const char * classifyColor(RGB input);
const char * enumToString(enum ColorEnum color);
uint8_t getConfidence();
void calcConfidence(double dist);

#endif