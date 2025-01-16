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

#define BTN1_MIN 720
#define BTN1_MAX 740
#define BTN2_MIN 770
#define BTN2_MAX 800
#define BTN3_MIN 1010

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

void initOLED();
void updateFace(State st = IDLE, bool urgent = 0);

void displayEmotion(uint8_t emotion);

void showMoodValue();

void displayMainMenu();
void processMenuInput();

void displayMusic();

void displayData();

void displayGame();
void displayUp();
void displayDown();
void displayWin();

#endif
