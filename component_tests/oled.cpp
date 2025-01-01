#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128 
#define OLED_HEIGHT 64  

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }

  display.clearDisplay();

  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0);          
  display.println("Hello");
  display.setCursor(0, 20);
  display.println("world!");
  display.display();                  
  delay(2000);                       
}

void loop() {
 
}
