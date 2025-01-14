#include "state_machine.h"
#include "mood.h"
#include "display.h"
#include <Arduino.h>

State currentState = IDLE;

void setup() {
    Serial.begin(9600);
    Serial.println("Serial communication started.");

    initMood();

    initOLED();

    updateFace(currentMood.mood);
}

void loop() {
    runStateMachine();
}