#include "display.h"
#include "mood.h"

#define DEBOUNCE_TIME 200
#define MENU_COUNT 4

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

uint8_t menu_option = 0;
extern volatile bool A_triggered;
extern volatile bool B_triggered;

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

void updateFace(State st, bool urgent) {
    unsigned long currentTime = millis();
    switch(st) {
        case IDLE:
            if (currentTime - lastUpdate >= FACE_UPDATE_INTERVAL || urgent) {
                currentMood.maintenance = max(0, currentMood.maintenance - 1); 
                currentMood.energy = max(0, currentMood.energy - 2); 
                currentMood.relaxation = max(0, currentMood.relaxation - 3); 
                currentMood.joy = max(0, currentMood.joy - 2); 
                lastUpdate = currentTime;
                displayEmotion(currentMood.mood / 25);
            }
            break;

        case SLEEPING:
            if (currentTime - lastUpdate >= FACE_UPDATE_INTERVAL || urgent) {
                currentMood.maintenance = max(0, currentMood.maintenance - 1); 
                currentMood.energy = min(99, currentMood.energy + 6); 
                currentMood.relaxation = max(0, currentMood.relaxation - 2); 
                currentMood.joy = max(0, currentMood.joy - 1); 
                lastUpdate = currentTime;
                displayEmotion(4);
            }
            break;

        default:
            Serial.println(F("Fatal error in Mood Update function"));
    }
    
    // currentMood.mood = (currentMood.joy + currentMood.relaxation + currentMood.energy + currentMood.maintenance) / 4;
    
    showMoodValue();
}

void showMoodValue() {
    display.fillRect(0, 0, 128, 15, BLACK);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Happiness: ");
    currentMood.mood = (currentMood.joy + currentMood.relaxation + currentMood.energy + currentMood.maintenance) / 4;
    display.print(currentMood.mood);
    display.display();
}

void processMenuInput() {
    displayMainMenu();
    if (A_triggered) {
        A_triggered = false;
        menu_option = (menu_option + 1) % MENU_COUNT;
    }
    if (B_triggered) {
        B_triggered = false;
        switch(menu_option) {
            case 0:
                currentState = SINGING;
                // Serial.println("STATUS CHECK");
                // displayFeed();
                break;
            case 1:
                // currentState = GAME_LOOP;
                // Serial.println("FEEDING");
                // FEEDING FUNC
                break;
            case 2:
                // currentState = MAINTENANCE;
                // Serial.println("GAME MENU");
                // show game menu
                break;
            case 3:
                currentState = IDLE;
                updateFace(IDLE, true);
                break;
            default:
                Serial.println(F("Fatal error in menu input processing!"));
        }
    }    
}


void displayMainMenu() {
    const char* menuOptions[] PROGMEM = { "SING", "PLAY A GAME", "MAINTENANCE", "< back" };
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("MAIN MENU");

    display.setTextSize(1);

    for (int i = 0; i < MENU_COUNT; i++) {
        if (menu_option == i) {
            display.fillRect(0, 10 * i + 3 + TOP_OFFSET, 128, 9, WHITE); 
            display.setTextColor(BLACK);
        } else {
            display.setTextColor(WHITE);
        }

        display.setCursor(1, 10 * i + 4 + TOP_OFFSET);
        display.print(menuOptions[i]);
    }

    display.display();
}

void displayFeed() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("PRESS BTN A");
    display.setCursor(1, 1 + TOP_OFFSET);
    display.print("Feed your");
    display.setCursor(1, 11 + TOP_OFFSET);
    display.print("Robomagotchi");
    display.setCursor(1, 21 + TOP_OFFSET);
    display.print("by pressing BTN A!");

    display.display();
}