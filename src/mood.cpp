#include "mood.h"
#include <Arduino.h>

Mood currentMood;

unsigned long lastMaintenanceUpdate = 0;
unsigned long lastJoyUpdate = 0;
unsigned long lastEnergyUpdate = 0;
unsigned long lastSatiationUpdate = 0;

void initMood() {
    currentMood.joy = 50;
    currentMood.satiation = 50;
    currentMood.energy = 50;
    currentMood.maintenance = 50;
    currentMood.mood = 50; 
}

void updateMood() {
    unsigned long currentTime = millis();
    if (currentTime - lastMaintenanceUpdate >= MAINT_INTV) {
        currentMood.maintenance--;
        lastMaintenanceUpdate = currentTime;
    }

    if (currentTime - lastJoyUpdate >= JOY_INTV) {
        currentMood.joy--;
        lastJoyUpdate = currentTime;
    }

    if (currentTime - lastEnergyUpdate >= ENERGY_INTV) {
        currentMood.energy--;
        lastEnergyUpdate = currentTime;
    }

    if (currentTime - lastSatiationUpdate >= SAT_INTV) {
        currentMood.satiation--;
        lastSatiationUpdate = currentTime;
    }

    currentMood.joy = constrain(currentMood.joy, 0, 100);
    currentMood.satiation = constrain(currentMood.satiation, 0, 100);
    currentMood.energy = constrain(currentMood.energy, 0, 100);
    currentMood.maintenance = constrain(currentMood.maintenance, 0, 100);

    currentMood.mood = (currentMood.joy + currentMood.satiation + currentMood.energy + currentMood.maintenance) / 4;
} 

