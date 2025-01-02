#include <Arduino.h>

#define PHOTO_PIN A0

void setup() {
    pinMode(PHOTO_PIN, INPUT);
    Serial.begin(9600);
}

void loop() {
   int light = analogRead(A0);
    Serial.println(light);
    delay(2000);
}