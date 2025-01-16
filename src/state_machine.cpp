#include "state_machine.h"
#include "display.h"
#include "mood.h"
#include "sensors.h"
#include <Arduino.h>

#define BUZZER_PIN 6
#define MIN_NOTE 100
#define MAX_NOTE 1000

unsigned int lastFaceUpdate = 0;
unsigned int lastAnimationUpdate = 0;
unsigned int lastProxCheck = 0;

unsigned long lastNoteTime = 0;
unsigned int noteDuration = 0;
int currentNote = 0;

extern int potValue;

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
        case SINGING:
            f_SINGING();
            break;
        default:
            Serial.println(F("Fatal error in state machine."));
    }
}

void f_IDLE() {
    updateFace();
        
    if (checkLightLow()) {
        currentState = SLEEPING;
        displayEmotion(4);
    }

    if (A_triggered || B_triggered) {
        A_triggered = false;
        B_triggered = false;
        currentState = MAIN_MENU;
        displayMainMenu();   
    }
}

void f_SLEEPING() {
    unsigned long currentTime = millis();
 
    updateFace(SLEEPING);

    if (currentTime - lastProxCheck >= PROX_CHECK_INTV) {
        int distance = getDistance();
        lastProxCheck = currentTime;
        if((distance <= MIN_PROX && distance != -1) && !checkLightLow()) {
            currentState = IDLE;
            updateFace(IDLE, true);
        } 
    }
}

void f_MAIN_MENU() {
    processMenuInput();
}

void f_GAME_LOOP() {
    displayGame();
    int guess = -1;

    while (!B_triggered) {

        if (guess == -1) guess = random(0, 65) * 10;

        if (A_triggered) {
            A_triggered = false;

            if (potValue < guess) displayUp(); 
            else if (potValue > guess) displayDown(); 
            else {  
                while (!A_triggered && !B_triggered) displayWin();
                A_triggered = false;
                B_triggered = false;
                break;
            }
        }
        displayGame(); 
    }

    B_triggered = false;

    currentMood.joy = min(currentMood.joy + 30, 99);
    currentState = IDLE;
    updateFace(IDLE, true);
}

void f_SINGING() {
    pinMode(BUZZER_PIN, OUTPUT);
    while(!A_triggered && !B_triggered) {
        unsigned long currentTime = millis();
        if (currentTime - lastNoteTime >= noteDuration) {
            currentNote = random(MIN_NOTE, MAX_NOTE);
            noteDuration = random(100, 500);
            tone(BUZZER_PIN, currentNote, noteDuration);
            lastNoteTime = currentTime;
        }
    }
    A_triggered = false;
    B_triggered = false;
    currentState = IDLE;
    updateFace(IDLE, true);
    currentMood.relaxation = min(currentMood.relaxation + 30, 99);
}

void f_MAINTENANCE() {
    displayData();
    while(!A_triggered && !B_triggered) {}
    A_triggered = false;
    B_triggered = false;
    currentMood.maintenance = min(currentMood.maintenance + 20, 99);
    currentState = IDLE;
    updateFace(IDLE, true);
}