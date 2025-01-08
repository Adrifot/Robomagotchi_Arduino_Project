#include <Arduino.h>
#include <Wire.h>

// Sensor libs
#include <DHT.h>

// Display Libs
#include <Adafruit_GFX.h> //graphics
#include <Adafruit_SSD1306.h> // oled
#include <Adafruit_ST7735.h> // spi tft

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define TRIG_PIN A2
#define ECHO_PIN 12
#define TFT_CS 4
#define TFT_RST 8
#define TFT_DC 7
#define PHOTO_PIN A0
#define DHT_PIN A3
#define BUZZ_PIN 6

DHT dht(DHT_PIN, DHT11);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void dht_read_data();
void oled_init();
int getProximity();
int get_light();
void startBuzzer(int frequency, unsigned long duration);
void updateBuzzer();

unsigned long buzzStartTime = 0, buzzDuration = 0;
bool buzzActive = false;

void setup() {
    Serial.begin(9600);
    Serial.println("Serial began successfuly.");

    dht.begin();
    Serial.println("DHT initialized.");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
    } else Serial.println("OLED initialized.");
    oled_init();

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT); 
    digitalWrite(TRIG_PIN, LOW);
    Serial.println("Proximity sensor initialized.");

    pinMode(PHOTO_PIN, INPUT);
    pinMode(BUZZ_PIN, OUTPUT);
}

int noteFrequencies[] = {262, 294, 330, 349, 392, 440, 494}; 
int noteDurations[] = {1500, 1500, 500, 500, 1500, 100, 500}; // 500 ms for each note
int currentNoteIndex = 0; // Track the current note being played


void loop() {
  // If no note is playing, start the next note in the sequence
  if (!buzzActive && currentNoteIndex < 7) {
    startBuzzer(noteFrequencies[currentNoteIndex], noteDurations[currentNoteIndex]);
    currentNoteIndex++; // Move to the next note
  }

  // Check if the buzzer duration has expired
  updateBuzzer();

  // Reset the sequence when all notes are played
  if (currentNoteIndex >= 7 && !buzzActive) {
    currentNoteIndex = 0; // Restart the sequence
  }
}

void dht_read_data() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    if(isnan(temperature) || isnan(humidity)) Serial.println("Failed to read from DHT sensor");
    else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
}

void oled_init() {
    display.clearDisplay();
    display.setTextSize(2);             
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 0);          
    display.println("Hello");
    display.setCursor(0, 20);
    display.println("world!");
    display.display();  
}

int getProximity() {
    float duration, distance;
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if(duration > 0) {
        distance = (duration * 0.0343) / 2;
        return distance;
    } else return -1;
}

int get_light() {
    return(analogRead(PHOTO_PIN));
}

void buzz(int frequency, int duration) {
    tone(BUZZ_PIN, frequency, duration);
}

void startBuzzer(int frequency, unsigned long duration) {
    tone(BUZZ_PIN, frequency);
    buzzStartTime = millis();
    buzzDuration = duration;
    buzzActive = true;
    delay(1);
}

void updateBuzzer() {
    if(buzzActive && (millis() - buzzStartTime >= buzzDuration)) {
        noTone(BUZZ_PIN);
        buzzActive = false;
        delay(1);
    }
}