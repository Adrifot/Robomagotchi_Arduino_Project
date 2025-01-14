#ifndef MOOD_H
#define MOOD_H

#define SAT_INTV 5000
#define MAINT_INTV 15000
#define JOY_INTV 7000
#define ENERGY_INTV 10000

struct Mood {
    int joy;
    int satiation;
    int energy;
    int maintenance;
    int mood;
};

extern Mood currentMood;

void initMood();
void updateMood();

#endif
