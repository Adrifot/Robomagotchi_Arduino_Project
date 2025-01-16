#include "state_machine.h"
#include "display.h"
#include "mood.h"
#include "sensors.h"
#include <Arduino.h>

unsigned int lastFaceUpdate = 0;
unsigned int lastAnimationUpdate = 0;
unsigned int lastProxCheck = 0;

extern volatile bool A_triggered;
extern unsigned int lastATime;

extern volatile bool B_triggered;
extern unsigned int lastBTime;

#define DEBOUNCE_TIME 200

void runStateMachine() {
    switch (currentState) {
        case IDLE:
            f_IDLE();
            break;
        case MAIN_MENU:
            f_MAIN_MENU();
            break;
        case GAME_LOOP:
            f_GAME_LOOP();
            break;
        case SLEEPING:
            f_SLEEPING();
            break;
        case MAINTENANCE:
            f_MAINTENANCE();
            break;
        case FEEDING:
            f_FEEDING();
            break;
        default:
            Serial.println(F("Fatal error in state machine."));
    }
}

void f_IDLE() {
    unsigned int currentTime = millis();
    if (currentTime - lastFaceUpdate >= FACE_UPDATE_INTERVAL) {
        updateFace(currentMood.mood);
        lastFaceUpdate = currentTime;
    }

    if (checkLightLow()) {
        currentState = SLEEPING;
        displayEmotion(4);
    }

    if (A_triggered) {
        A_triggered = false;
        currentState = MAIN_MENU;
        displayMainMenu();   
    }
}

void f_SLEEPING() {
    unsigned long currentTime = millis();
 
    updateFace(currentMood.mood, SLEEPING);

    if (currentTime - lastProxCheck >= PROX_CHECK_INTV) {
        int distance = getDistance();
        lastProxCheck = currentTime;
        if((distance <= MIN_PROX && distance != -1) && !checkLightLow()) {
            currentState = IDLE;
            updateFace(currentMood.mood);
        } 
    }
}

void f_MAIN_MENU() {
    processMenuInput();
    if (B_triggered) {
        B_triggered = false;
        currentState = IDLE;
        updateFace(currentMood.mood);
    } 
}

void f_GAME_LOOP() {

}

void f_FEEDING() {

}

void f_MAINTENANCE() {

}