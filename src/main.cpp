// #include <Arduino.h>
// #include <Wire.h>

// // Sensor libs
// #include <DHT.h>

// // Display Libs
// #include <Adafruit_GFX.h> //graphics
// #include <Adafruit_SSD1306.h> // oled
// #include <Adafruit_ST7735.h> // spi tft

// #define OLED_WIDTH 128
// #define OLED_HEIGHT 64

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
// Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

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

// /****display funcs***/
// void happyFace();
// void showStatus();
// void showData();
// /******************/

// unsigned long buzzStartTime = 0, buzzDuration = 0;
// bool buzzActive = false;
// volatile int happiness = 100;


// void setup() {
//     Serial.begin(9600);
//     Serial.println("Serial began successfuly.");

//     dht.begin();
//     Serial.println("DHT initialized.");

//     if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//         Serial.println(F("SSD1306 allocation failed"));
//     } else Serial.println("OLED initialized.");
//     oledInit();

//     pinMode(TRIG_PIN, OUTPUT);
//     pinMode(ECHO_PIN, INPUT); 
//     digitalWrite(TRIG_PIN, LOW);
//     Serial.println("Proximity sensor initialized.");

//     pinMode(PHOTO_PIN, INPUT);
//     pinMode(BUZZ_PIN, OUTPUT);

//     tft.initR(INITR_BLACKTAB);
//     tft.fillScreen(ST77XX_BLACK);
//     Serial.println("TFT initialized.");

//     pinMode(BTN_GROUP, INPUT);
//     pinMode(BTN_EXT, INPUT);

//     attachInterrupt(digitalPinToInterrupt(3), ext_ISR, RISING);
//     interrupts();

//     happyFace();
//     showStatus();
// }

// void loop() {
//     if(!dataOn && dataOn != exDataOn) {
//         happyFace();
//         showStatus();
//     } else if(dataOn != exDataOn) {
//         showData();
//     }
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

// void oledInit() {
//     display.clearDisplay();
//     display.setTextSize(2);             
//     display.setTextColor(SSD1306_WHITE); 
//     display.setCursor(0, 0);          
//     display.println("Hello");
//     display.setCursor(0, 20);
//     display.println("world!");
//     display.display();  
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

// void showData() {
//     // tft.fillScreen(ST7735_GREEN);
//     // int t = dht.readTemperature();
//     // int h = dht.readHumidity();
//     // tft.setCursor(5, 5);
//     // tft.setTextSize(2);
//     // tft.setTextColor(ST7735_BLACK);
//     // tft.print("Temp: ");
//     // tft.print(t);
//     // tft.println("*C");
//     // tft.print("Humidity: ");
//     // tft.print(h);
//     // tft.println("%");
//     display.clearDisplay();
//     int t = dht.readTemperature();
//     int h = dht.readHumidity();
//     display.setCursor(0, 16);
//     display.setTextSize(2);
//     display.setTextColor(SSD1306_WHITE);
//     display.print("Temp: ");
//     display.print(t);
//     display.println("*C");
//     display.print("Humidity: ");
//     display.print(h);
//     display.println("%");
//     display.display();
// }

#include <Wire.h>
 
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}