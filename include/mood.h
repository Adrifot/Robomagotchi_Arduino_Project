#ifndef MOOD_H
#define MOOD_H

#include "state_machine.h"
#include <Arduino.h>

struct Mood {
    uint8_t joy;
    uint8_t satiation;
    uint8_t energy;
    uint8_t maintenance;
    uint8_t mood;
};

extern Mood currentMood;

void initMood();

#endif
