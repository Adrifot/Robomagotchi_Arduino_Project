#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define TOP_OFFSET 15

void initOLED();
void updateFace(int mood);

#endif
