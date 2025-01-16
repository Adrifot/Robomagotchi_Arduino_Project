#include "sensors.h"
#include <Arduino.h>

const uint8_t lightThreshold = 20;

int duration, distance;

DHT dht(DHT_PIN, DHT11);

void initSensors() {
    pinMode(PHOTO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    dht.begin();
    pinMode(POT_PIN, INPUT);
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