#include "state_machine.h"
#include "display.h"
#include "mood.h"
#include "sensors.h"
#include <Arduino.h>

unsigned long lastFaceUpdate = 0;
unsigned long lastAnimationUpdate = 0;
unsigned long lastProxCheck = 0;

extern volatile bool B_triggered;
extern unsigned long lastBTime;

#define DEBOUNCE_TIME 200

void runStateMachine() {
    switch (currentState) {
        case IDLE:
            f_IDLE();
            break;
        case MAIN_MENU:
            f_MAIN_MENU();
            break;
        case GAME_MENU: 
            f_GAME_MENU();
            break;
        case GAME_LOOP:
            f_GAME_LOOP();
            break;
        case SLEEPING:
            f_SLEEPING();
            break;
        case STATUS_CHECK:
            f_STATUS_CHECK();
            break;
        case MAINTENANCE:
            f_MAINTENANCE();
            break;
        case FEEDING:
            f_FEEDING();
            break;
        default:
            Serial.println("Fatal error in state machine.");
    }
}

void f_IDLE() {
    unsigned long currentTime = millis();
    updateMood();
    if (currentTime - lastFaceUpdate >= FACE_UPDATE_INTERVAL) {
        updateFace(currentMood.mood);
        lastFaceUpdate = currentTime;
    }

    if (currentMood.energy <= 10 || checkLightLow()) {
        currentState = SLEEPING;
        Serial.println("Transition to SLEEPING state.");
    }

    // if (B_triggered) {
    //     B_triggered = false;
    //     currentState = MAIN_MENU;
    //     displayMainMenu();
    //     Serial.println("Transition to MAIN_MENU state.");    
    // }
}

void f_SLEEPING() {
    unsigned long currentTime = millis();

    if (currentTime - lastAnimationUpdate >= SLEEP_ANIMATION_INTV) {
        displaySleeping();
        lastAnimationUpdate = currentTime;
    }

    updateMood(SLEEPING);

    if (currentTime - lastProxCheck >= PROX_CHECK_INTV) {
        float distance = getDistance();
        lastProxCheck = currentTime;
        if((distance <= MIN_PROX && distance != -1) && (!checkLightLow() && currentMood.energy > 10)) {
            currentState = IDLE;
            updateFace(currentMood.mood);
        } 
    }
}

void f_MAIN_MENU() {
    // processMenuInput();
    // if (B_triggered) {
    //     B_triggered = false;
    //     currentState = IDLE;
    //     updateFace(currentMood.mood);
    // }
    // displayMainMenu();
}

void f_GAME_MENU() {
    
}

void f_GAME_LOOP() {

}

void f_FEEDING() {

}

void f_STATUS_CHECK() {

}

void f_MAINTENANCE() {

}