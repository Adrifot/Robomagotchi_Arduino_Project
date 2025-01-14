#include "display.h"
#include <Wire.h>

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void initOLED() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for(;;);
    }
    display.clearDisplay();
}

void updateFace(int mood) {
    
}