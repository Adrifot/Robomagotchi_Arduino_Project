#include "state_machine.h"
#include "display.h"
#include "mood.h"

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
            f_SLEEPING():
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
            Serial.println("fatal error in state machine");
    }
}