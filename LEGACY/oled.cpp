#include "oled.h"
#include "states.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

volatile int joy, satiation, energy, maintenance;
int mood;

void oledInit() {
    
}

