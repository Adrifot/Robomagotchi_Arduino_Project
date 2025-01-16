#ifndef SENSORS_H
#define SENSORS_H
#include <DHT.h>

#define PHOTO_PIN A2

#define TRIG_PIN 5
#define ECHO_PIN 4

#define DHT_PIN 7

#define PROX_CHECK_INTV 2500
#define MIN_PROX 10

#define POT_PIN A1

void initSensors();

int getLight();
bool checkLightLow();

int getDistance();

#endif