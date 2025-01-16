#ifndef SENSORS_H
#define SENSORS_H

#define PHOTO_PIN A2

#define TRIG_PIN 5
#define ECHO_PIN 4

#define PROX_CHECK_INTV 2500
#define MIN_PROX 10

void initSensors();

int getLight();
bool checkLightLow();

int getDistance();

// int getTemperature();
// int getHumidity();

#endif