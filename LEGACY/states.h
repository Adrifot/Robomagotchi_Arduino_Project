#ifndef STATES_H
#define STATES_H

enum State {
    IDLE,
    MAIN_MENU,
    GAME_MENU,
    GAME_LOOP,
    SLEEPING,
    STATUS_CHECK,
    MAITENANCE,
    FEEDING
};

extern volatile State currentState;
extern int satiation, energy, joy, maintenance;

void f_IDLE();
void f_MAIN_MENU();
void f_GAME_MENU();
void f_GAME_LOOP();
void f_SLEEPING();
void f_STATUS_CHECK();
void f_MAINTENANCE();
void f_FEEDING();

void updateValues();
void updateMood();

void displayHappy();
void displayNormal();
void displaySad();
void displayBored();
void displaySleepy();

#endif
