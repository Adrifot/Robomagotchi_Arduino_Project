#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define TOP_OFFSET 15
#define FACE_UPDATE_INTERVAL 15000

void initOLED();
void updateFace(int mood);

void displayHappy();
void displayNormal();
void displaySad();
void displayBored();
void displaySleepy(); // not yet implemented

#endif
