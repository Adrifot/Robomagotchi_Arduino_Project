#include <Arduino.h>
#include "states.h"
#include "oled.h"

volatile State currentState = IDLE;

// mood values
int satiation = 50, energy = 50, joy = 50, maintenance = 50, mood;

// timers
unsigned long maintenanceTimer = 0, joyTimer = 0, hungerTimer = 0, energyTimer = 0;
unsigned long faceUpdateTimer = 0;

// update intervals
const unsigned long maintenanceInterval = 60000;
const unsigned long joyInterval = 30000;
const unsigned long hungerInterval = 15000;
const unsigned long energyInterval = 30000;
const unsigned long faceUpdateInterval = 15000;

void ISR_BTN_2() {
    // TO DO: code
}

void updateValues() {
    unsigned long currentTime = millis();

    if (currentTime - maintenanceTimer >= maintenanceInterval) {
        maintenance = max(maintenance - 1, 0);
        maintenanceTimer = currentTime;
    }
    if (currentTime - joyTimer >= joyInterval) {
        joy = max(joy - 1, 0);
        joyTimer = currentTime;
    }
    if (currentTime - hungerTimer >= hungerInterval) {
        satiation = max(satiation - 1, 0);
        hungerTimer = currentTime;
    }
    if (currentTime - energyTimer >= energyInterval) {
        energy = max(energy - 1, 0);
        energyTimer = currentTime;
    }
}

void updateMood() {
    mood = joy + satiation + energy + maintenance;
    mood /= 4;
    if(energy <= 10) {
        currentState = SLEEPING;
    } else {
        if (mood >= 85) displayHappy();
        else if (mood >= 70) displayNormal();
        else if (mood >= 40) displayBored();
        else displaySad();
    }
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