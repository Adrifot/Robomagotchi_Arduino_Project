#include <Arduino.h>

#define TRIG_PIN A2
#define ECHO_PIN 12

float duration, distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); 

  if (duration > 0) {
    distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
  } else {
    Serial.println("No Echo detected");
  }

  delay(100);
}
