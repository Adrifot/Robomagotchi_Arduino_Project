#include "mood.h"
#include "display.h"
#include <Arduino.h>

Mood currentMood;

void initMood() {
    currentMood.joy = 50;
    currentMood.relaxation = 50;
    currentMood.energy = 50;
    currentMood.maintenance = 50;
    currentMood.mood = 50; 
}

