#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h> //graphics
#include <Adafruit_SSD1306.h> // oled

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define TOP_OFFSET 15

#define MAX_MOOD 100
#define MIN_MOOD 1

#define WHITE SSD1306_WHITE

void oledInit();

#endif