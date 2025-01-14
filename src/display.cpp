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
    if (mood>=85) displayHappy();
    else if (mood >= 70) displayNormal();
    else if (mood >= 40) displayBored();
    else displaySad(); 
    showHappiness();
}

void showHappiness() {
    display.fillRect(0, 0, 128, 15, BLACK);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Happiness: ");
    display.print(currentMood.mood);
    display.display();
}

void displayHappy() {
    display.clearDisplay();
    display.fillRect(32, 1 + TOP_OFFSET, 10, 21, WHITE); 
    display.fillRect(88, 1 + TOP_OFFSET, 10, 21, WHITE);
    display.fillRect(39, 33 + TOP_OFFSET, 51, 13, WHITE);
    display.fillTriangle(28, 33 + TOP_OFFSET, 39, 33 + TOP_OFFSET, 39, 45 + TOP_OFFSET, WHITE);
    display.fillTriangle(89, 33 + TOP_OFFSET, 101, 33 + TOP_OFFSET, 89, 45 + TOP_OFFSET, WHITE);

    display.display();
}

void displayNormal() {
    display.clearDisplay();
    display.fillRect(32, 1 + TOP_OFFSET, 10, 21, WHITE); 
    display.fillRect(88, 1 + TOP_OFFSET, 10, 21, WHITE);
    display.drawLine(31, 35 + TOP_OFFSET, 41, 45 + TOP_OFFSET, WHITE);
    display.drawLine(41, 45 + TOP_OFFSET, 89, 45 + TOP_OFFSET, WHITE);
    display.drawLine(89, 45 + TOP_OFFSET, 99, 35 + TOP_OFFSET, WHITE);

    display.display();
}

void displayBored() {
    display.clearDisplay();
    display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
    display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
    display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
    display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
    display.drawLine(31, 42 + TOP_OFFSET, 99, 42 + TOP_OFFSET, WHITE);

    display.display();
}

void displaySad() {
    display.clearDisplay();
    display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
    display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
    display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
    display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
    display.drawLine(32, 42 + TOP_OFFSET, 40, 34 + TOP_OFFSET, WHITE);
    display.drawLine(40, 34 + TOP_OFFSET, 90, 34 + TOP_OFFSET, WHITE);
    display.drawLine(90, 34 + TOP_OFFSET, 98, 42 + TOP_OFFSET, WHITE);

    display.display();
}
