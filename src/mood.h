#ifndef MOOD_H
#define MOOD_H

#define SAT_INTV 1000
#define MAINT_INTV 5000
#define JOY_INTV 3000
#define ENERGY_INTV 3000

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
