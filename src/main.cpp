#include "state_machine.h"
#include "mood.h"
#include "display.h"
#include "sensors.h"
#include <Arduino.h>

// #define INTERRUPT_A_PIN 2
// #define INTERRUPT_B_PIN 3
// #define A_VALUE_PIN A3

State currentState = IDLE;
// volatile bool B_triggered = false;
// volatile bool A_triggered = false;
// volatile int A_value;
// unsigned long lastATime = 0;
// unsigned long lastBTime = 0;

// void ISR_A() {
//     // unsigned long currentTime = millis();
//     // if (currentTime - lastAISR >= DEBOUNCE_TIME) {
//         // lastAISR = currentTime;
//         A_triggered = true;
//         A_value = analogRead(A_VALUE_PIN);
//     // }
// }

// void ISR_B() {
//     // unsigned long currentTime = millis();
//     // if (currentTime - lastBISR >= DEBOUNCE_TIME) {
//         // lastBISR = currentTime;
//         B_triggered = true;
//     // }
// }

void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial communication started.");
    // delay(100);

    Wire.begin();
    Serial.println("I2C Ready.");
    // delay(100);

    initSensors(); Serial.println("Sensors init done.");

    initMood(); Serial.println("Mood init done.");
    
    initOLED();
    updateFace(currentMood.mood);
    
    // pinMode(INTERRUPT_A_PIN, INPUT);
    // pinMode(A_VALUE_PIN, INPUT);
    // pinMode(INTERRUPT_B_PIN, INPUT);
    
    // attachInterrupt(digitalPinToInterrupt(INTERRUPT_A_PIN), ISR_A, RISING); 
    // attachInterrupt(digitalPinToInterrupt(INTERRUPT_B_PIN), ISR_B, RISING);
}

void loop() {
    runStateMachine();
}

