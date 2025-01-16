#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "mood.h"
#include "sensors.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define TOP_OFFSET 15
#define FACE_UPDATE_INTERVAL 5000

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

void initOLED();
void updateFace(uint8_t mood, State st = IDLE);

void displayEmotion(uint8_t emotion);

void showMoodValue();

void displayMainMenu();
void processMenuInput();

#endif
