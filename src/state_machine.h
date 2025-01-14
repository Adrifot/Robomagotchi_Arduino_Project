#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

enum State {
    IDLE,
    MAIN_MENU,
    GAME_MENU,
    GAME_LOOP,
    SLEEPING,
    STATUS_CHECK,
    MAINTENANCE,
    FEEDING
};

extern State currentState; 
void runStateMachine(); 

void f_IDLE();
void f_MAIN_MENU();
void f_GAME_MENU();
void f_GAME_LOOP();
void f_SLEEPING();
void f_STATUS_CHECK();
void f_MAINTENANCE();
void f_FEEDING();
void f_SLEEPING();

#endif
