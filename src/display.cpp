#include "display.h"
#include "mood.h"

#define BTN1_MIN 720
#define BTN1_MAX 740
#define BTN2_MIN 770
#define BTN2_MAX 800
#define BTN3_MIN 1010

#define DEBOUNCE_TIME 200
#define MENU_COUNT 3

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

uint8_t menu_option = 0;
extern volatile bool A_triggered;
extern volatile int A_value;

unsigned long lastUpdate = 0;

extern unsigned int lastATime;
extern unsigned int lastBTime;

void initOLED() {
    Serial.println(F("Initializing OLED..."));
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);  
    }
    Serial.println(F("OLED initialized successfully!"));
    display.clearDisplay();
}

void displayEmotion(uint8_t emotion) {
    display.clearDisplay();
    switch (emotion) {
        case 0:
            display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
            display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
            display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
            display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
            display.drawLine(32, 42 + TOP_OFFSET, 40, 34 + TOP_OFFSET, WHITE);
            display.drawLine(40, 34 + TOP_OFFSET, 90, 34 + TOP_OFFSET, WHITE);
            display.drawLine(90, 34 + TOP_OFFSET, 98, 42 + TOP_OFFSET, WHITE);
            break;

        case 1:
            display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
            display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
            display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
            display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
            display.drawLine(31, 42 + TOP_OFFSET, 99, 42 + TOP_OFFSET, WHITE);
            break;

        case 2:
            display.fillRect(32, 1 + TOP_OFFSET, 10, 21, WHITE); 
            display.fillRect(88, 1 + TOP_OFFSET, 10, 21, WHITE);
            display.drawLine(31, 35 + TOP_OFFSET, 41, 45 + TOP_OFFSET, WHITE);
            display.drawLine(41, 45 + TOP_OFFSET, 89, 45 + TOP_OFFSET, WHITE);
            display.drawLine(89, 45 + TOP_OFFSET, 99, 35 + TOP_OFFSET, WHITE);
            break;
            
        case 4:
            display.fillRect(32, 5 + TOP_OFFSET, 20, 5, WHITE); 
            display.fillRect(78, 5 + TOP_OFFSET, 20, 5, WHITE);
            display.fillCircle(64, 35 + TOP_OFFSET, 6, WHITE);
            
            display.setTextColor(WHITE);
            display.setCursor(80, 20 + TOP_OFFSET);
            display.setTextSize(3);
            display.print("z");
            display.setCursor(100, 15 + TOP_OFFSET);
            display.setTextSize(2);
            display.print("z");
            display.setCursor(112, 8 + TOP_OFFSET);
            display.setTextSize(1);
            display.print("z");
            break;
    }
    display.display();
}

void updateFace(uint8_t mood, State st) {
    unsigned long currentTime = millis();
    switch(st) {
        case IDLE:
            if (currentTime - lastUpdate >= FACE_UPDATE_INTERVAL) {
                currentMood.maintenance = max(0, currentMood.maintenance - 1); 
                currentMood.energy = max(0, currentMood.energy - 2); 
                currentMood.satiation = max(0, currentMood.satiation - 3); 
                currentMood.joy = max(0, currentMood.joy - 2); 
                lastUpdate = currentTime;
                displayEmotion(mood / 25);
            }
            break;

        case SLEEPING:
            if (currentTime - lastUpdate >= FACE_UPDATE_INTERVAL) {
                currentMood.maintenance = max(0, currentMood.maintenance - 1); 
                currentMood.energy = min(99, currentMood.energy + 4); 
                currentMood.satiation = max(0, currentMood.satiation - 2); 
                currentMood.joy = max(0, currentMood.joy - 1); 
                lastUpdate = currentTime;
                displayEmotion(4);
            }
            break;

        default:
            Serial.println(F("Fatal error in Mood Update function"));
    }
    
    currentMood.mood = (currentMood.joy + currentMood.satiation + currentMood.energy + currentMood.maintenance) / 4;
    
    showMoodValue();
}

void showMoodValue() {
    display.fillRect(0, 0, 128, 15, BLACK);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Happiness: ");
    display.print(currentMood.mood);
    display.display();
}

void processMenuInput() {
    if (A_triggered) {
        A_triggered = false;
        if (A_value >= BTN1_MIN && A_value <= BTN1_MAX) {
            menu_option = (menu_option - 1 + MENU_COUNT) % MENU_COUNT;
        } else if (A_value >= BTN2_MIN && A_value <= BTN2_MAX) {
            menu_option = (menu_option + 1) % MENU_COUNT;
        } else if (A_value >= BTN3_MIN) {
            switch(menu_option) {
                case 0:
                    // currentState = STATUS_CHECK;
                    // Serial.println("STATUS CHECK");
                    // show status func
                    break;
                case 1:
                    // currentState = FEEDING;
                    // Serial.println("FEEDING");
                    // FEEDING FUNC
                    break;
                case 2:
                    // currentState = GAME_MENU;
                    // Serial.println("GAME MENU");
                    // show game menu
                    break;
                case 3:
                    // currentState = MAINTENANCE;
                    // Serial.println("MAINTENANCE");
                    // show sensor data
                    break;
                default:
                    Serial.println(F("Fatal error in menu input processing!"));
            }
        }
        displayMainMenu();
    }
}


void displayMainMenu() {
    const char* menuOptions[] PROGMEM = { "FEED", "PLAY A GAME", "MAINTENANCE" };
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("MAIN MENU");

    display.setTextSize(1);

    for (int i = 0; i < MENU_COUNT; i++) {
        if (menu_option == i) {
            display.fillRect(0, 12 * i + 1 + TOP_OFFSET, 128, 9, WHITE); 
            display.setTextColor(BLACK);
        } else {
            display.setTextColor(WHITE);
        }

        display.setCursor(1, 12 * i + 2 + TOP_OFFSET);
        display.print(menuOptions[i]);
    }

    display.display();
}
