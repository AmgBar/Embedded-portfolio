
/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Ethan Lam, Kevin Chuong, Hiro Eernisse, Andy Garcia
* Student ID:: 921993953, 922176863, 923217227, 921107769
* Github-Name:: RNDME1
* Project:: Term Project - Drive On
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
    COLOR_WHITE,
    COLOR_RED,
    COLOR_RED2,
    COLOR_GREEN,
    COLOR_GREEN2,
    COLOR_TARP,
    COLOR_TARP2,
    // COLOR_TARP,
    // COLOR_CLEAN_RED,
    // COLOR_CLEAN_RED2,
    COLOR_UNKNOWN,  // for fallback
    COLOR_COUNT     // total number of colors
};

static RGB colors[COLOR_COUNT-1] = {
    {0, 0, 0},       // Black
    {255, 255, 255}, // White
    {255, 0, 0},     // Red
    {128, 20, 20},   // Red2
    {0, 255, 0},     // Green
    {40, 128, 20},   // Green2
    {52, 30, 8},    // Tarp
    {64, 64, 64},    // Tarp 2
    // {44, 57, 20},    // Tape Green
    // {16, 16, 16},    // Tarp colored
    // {92, 0, 0},      // clean red
    // {58, 36, 16}    //clean red 2
};

double colorDistance(RGB c1, RGB c2);
int scaleValue(int val);
enum ColorEnum classifyColorEnum(RGB input);
const char * classifyColor(RGB input);
const char * enumToString(enum ColorEnum color);
uint8_t getConfidence();
void calcConfidence(double dist);

#endif