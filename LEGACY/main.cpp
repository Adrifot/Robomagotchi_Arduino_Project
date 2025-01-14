// #include <Arduino.h>
// #include <Wire.h>

// // Sensor libs
// #include <DHT.h>

// #define TRIG_PIN A2
// #define ECHO_PIN 12
// #define TFT_CS 4
// #define TFT_RST 8
// #define TFT_DC 7
// #define PHOTO_PIN A0
// #define DHT_PIN A3
// #define BUZZ_PIN 6
// #define BTN_GROUP 2
// #define BTN_EXT 3

// DHT dht(DHT_PIN, DHT11);

// volatile int dataOn = 0, exDataOn = 1;

// void dhtReadData();
// void oledInit();
// int getProximity();
// int getLight();
// void startBuzzer(int frequency, unsigned long duration);
// void updateBuzzer();
// void ext_ISR() {
//     exDataOn = dataOn;
//     dataOn = dataOn==1 ? 0 : 1;
//     Serial.print(dataOn);
//     Serial.print(" ");
//     Serial.println(exDataOn);
// }

// unsigned long buzzStartTime = 0, buzzDuration = 0;
// bool buzzActive = false;
// volatile int happiness = 100;


// void setup() {
//     Serial.begin(9600);
//     Serial.println("Serial began successfuly.");

//     dht.begin();
//     Serial.println("DHT initialized.");

//     pinMode(TRIG_PIN, OUTPUT);
//     pinMode(ECHO_PIN, INPUT); 
//     digitalWrite(TRIG_PIN, LOW);
//     Serial.println("Proximity sensor initialized.");

//     pinMode(PHOTO_PIN, INPUT);
//     pinMode(BUZZ_PIN, OUTPUT);

//     pinMode(BTN_GROUP, INPUT);
//     pinMode(BTN_EXT, INPUT);

//     attachInterrupt(digitalPinToInterrupt(3), ext_ISR, RISING);
//     interrupts();

//     happyFace();
//     showStatus();
// }


// void dhtReadData() {
//     float temperature = dht.readTemperature();
//     float humidity = dht.readHumidity();
//     if(isnan(temperature) || isnan(humidity)) Serial.println("Failed to read from DHT sensor");
//     else {
//         Serial.print("Temperature: ");
//         Serial.print(temperature);
//         Serial.println(" °C");
//         Serial.print("Humidity: ");
//         Serial.print(humidity);
//         Serial.println(" %");
//     }
// }

// int getProximity() {
//     float duration, distance;
//     digitalWrite(TRIG_PIN, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TRIG_PIN, LOW);

//     duration = pulseIn(ECHO_PIN, HIGH, 30000);
//     if(duration > 0) {
//         distance = (duration * 0.0343) / 2;
//         return distance;
//     } else return -1;
// }

// int getLight() {
//     return(analogRead(PHOTO_PIN));
// }

// void startBuzzer(int frequency, unsigned long duration) {
//     tone(BUZZ_PIN, frequency);
//     buzzStartTime = millis();
//     buzzDuration = duration;
//     buzzActive = true;
//     delay(1);
// }

// void updateBuzzer() {
//     if(buzzActive && (millis() - buzzStartTime >= buzzDuration)) {
//         noTone(BUZZ_PIN);
//         buzzActive = false;
//         delay(1);
//     }
// }

// void happyFace() {
//     display.clearDisplay();
//     display.fillRect(32, 16, 8, 20, SSD1306_WHITE); // Y 16 MINIMUM
//     display.fillRect(88, 16, 8, 20, SSD1306_WHITE);
//     display.drawLine(30, 48, 36, 58, SSD1306_WHITE);
//     display.drawLine(92, 58, 98, 48, SSD1306_WHITE);
//     display.drawLine(36, 58, 92, 58, SSD1306_WHITE);

//     display.display();
// }

// void showStatus() {
//     display.fillRect(0, 0, 128, 15, SSD1306_BLACK);
//     display.setCursor(0, 0);
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);
//     display.print("Happiness: ");
//     display.print(happiness);
//     display.print("/100");
//     display.display();
// }


#include <Arduino.h>
#include "states.h"
#include <Adafruit_GFX.h> //graphics
#include <Adafruit_SSD1306.h> // oled

unsigned long maintenanceTimer = 0;
unsigned long joyTimer = 0;
unsigned long satiationTimer = 0;
unsigned long energyTimer = 0;

const unsigned long maintenanceInterval = 60000;
const unsigned long joyInterval = 30000;
const unsigned long satiationInterval = 15000;
const unsigned long energyInterval = 30000;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println("SSD1306 allocation failed");
    } else Serial.println("OLED initialized.");
}

void loop() {
  unsigned long currentTime = millis();
      if (currentTime - maintenanceTimer >= maintenanceInterval) {
          maintenance = max(maintenance - 1, 0);
          maintenanceTimer = currentTime;
      }
      if (currentTime - joyTimer >= joyInterval) {
          joy = max(joy - 1, 0);
          joyTimer = currentTime;
      }
      if (currentTime - hungerTimer >= hungerInterval) {
          hunger = max(hunger - 1, 0);
          hungerTimer = currentTime;
      }
      if (currentTime - energyTimer >= energyInterval) {
          energy = max(energy - 1, 0);
          energyTimer = currentTime;
      }
}