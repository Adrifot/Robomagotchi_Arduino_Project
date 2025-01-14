#include "sensors.h"
#include <Arduino.h>

const int lightThreshold = 20;

float duration, distance;

void initSensors() {
    pinMode(PHOTO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
}

int getLight() {
    return analogRead(PHOTO_PIN);
}

bool checkLightLow() {
    return getLight() < lightThreshold;
}

int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if(duration > 0) distance = (duration * 0.0343) / 2;
    else distance = -1;

    return distance;
}