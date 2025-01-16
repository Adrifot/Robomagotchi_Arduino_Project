#include "state_machine.h"
#include "mood.h"
#include "display.h"
#include "sensors.h"
#include <Arduino.h>

#define INTERRUPT_A_PIN 2
#define INTERRUPT_B_PIN 3

volatile State currentState = IDLE;
volatile bool B_triggered = false;
volatile bool A_triggered = false;
volatile int A_value;
unsigned int lastATime = 0;
unsigned int lastBTime = 0;

void ISR_A() {
    A_triggered = true;
}

void ISR_B() {
    B_triggered = true;
}

void setup() {
    
    Serial.begin(9600);

    Wire.begin();

    initSensors(); //Serial.println("Sensors init done.");

    initMood(); //Serial.println("Mood init done.");
    
    initOLED();
    
    pinMode(INTERRUPT_A_PIN, INPUT);
    pinMode(INTERRUPT_B_PIN, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_A_PIN), ISR_A, FALLING); 
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_B_PIN), ISR_B, FALLING);
}

void loop() {
    runStateMachine();
}

