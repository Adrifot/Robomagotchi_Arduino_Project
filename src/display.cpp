#include "display.h"

#define BTN1_MIN 720
#define BTN1_MAX 740
#define BTN2_MIN 770
#define BTN2_MAX 800
#define BTN3_MIN 1010

#define DEBOUNCE_TIME 200

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

int menu_option = 0;
const int menu_count = 4;
extern volatile bool A_triggered;
extern volatile int A_value;

extern unsigned long lastATime;
extern unsigned long lastBTime;

void initOLED() {
    Serial.println("Initializing OLED...");
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for(;;);  
    }
    Serial.println("OLED initialized successfully!");
    display.clearDisplay();
}

void updateFace(int mood) {
    if (mood>=85) displayHappy();
    else if (mood >= 70) displayNormal();
    else if (mood >= 40) displayBored();
    else displaySad(); 
    showHappiness();
}

void showHappiness() {
    display.fillRect(0, 0, 128, 15, BLACK);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Happiness: ");
    display.print(currentMood.mood);
    display.display();
}

void displayHappy() {
    display.clearDisplay();
    display.fillRect(32, 1 + TOP_OFFSET, 10, 21, WHITE); 
    display.fillRect(88, 1 + TOP_OFFSET, 10, 21, WHITE);
    display.fillRect(39, 33 + TOP_OFFSET, 51, 13, WHITE);
    display.fillTriangle(28, 33 + TOP_OFFSET, 39, 33 + TOP_OFFSET, 39, 45 + TOP_OFFSET, WHITE);
    display.fillTriangle(89, 33 + TOP_OFFSET, 101, 33 + TOP_OFFSET, 89, 45 + TOP_OFFSET, WHITE);

    display.display();
}

void displayNormal() {
    display.clearDisplay();
    display.fillRect(32, 1 + TOP_OFFSET, 10, 21, WHITE); 
    display.fillRect(88, 1 + TOP_OFFSET, 10, 21, WHITE);
    display.drawLine(31, 35 + TOP_OFFSET, 41, 45 + TOP_OFFSET, WHITE);
    display.drawLine(41, 45 + TOP_OFFSET, 89, 45 + TOP_OFFSET, WHITE);
    display.drawLine(89, 45 + TOP_OFFSET, 99, 35 + TOP_OFFSET, WHITE);

    display.display();
}

void displayBored() {
    display.clearDisplay();
    display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
    display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
    display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
    display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
    display.drawLine(31, 42 + TOP_OFFSET, 99, 42 + TOP_OFFSET, WHITE);

    display.display();
}

void displaySad() {
    display.clearDisplay();
    display.fillRect(32, 6 + TOP_OFFSET, 10, 16, WHITE); 
    display.fillRect(88, 6 + TOP_OFFSET, 10, 16, WHITE);
    display.fillTriangle(32, 6 + TOP_OFFSET, 41, 1 + TOP_OFFSET, 41, 6 + TOP_OFFSET, WHITE);
    display.fillTriangle(88, 1 + TOP_OFFSET, 88, 6 + TOP_OFFSET, 97, 6 + TOP_OFFSET, WHITE);
    display.drawLine(32, 42 + TOP_OFFSET, 40, 34 + TOP_OFFSET, WHITE);
    display.drawLine(40, 34 + TOP_OFFSET, 90, 34 + TOP_OFFSET, WHITE);
    display.drawLine(90, 34 + TOP_OFFSET, 98, 42 + TOP_OFFSET, WHITE);

    display.display();
}

void displaySleeping() {
    static int zOffset = 0;  
    display.clearDisplay();
    
    display.fillRect(32, 5 + TOP_OFFSET, 20, 5, WHITE); 
    display.fillRect(78, 5 + TOP_OFFSET, 20, 5, WHITE);
    display.fillCircle(64, 35 + TOP_OFFSET, 6, WHITE);
    
    display.setTextColor(WHITE);
    display.setCursor(80 + zOffset, 20 + TOP_OFFSET - zOffset/2);
    display.setTextSize(3);
    display.print("z");
    display.setCursor(100 + zOffset, 15 + TOP_OFFSET - zOffset/2);
    display.setTextSize(2);
    display.print("z");
    display.setCursor(112 + zOffset, 8 + TOP_OFFSET - zOffset/2);
    display.setTextSize(1);
    display.print("z");

    zOffset++;  
    if (zOffset > 10) {  
        zOffset = 0;
    }

    display.display();
}

// void processMenuInput() {
//     if (A_triggered) {
//         A_triggered = false;
//         if (A_value >= BTN1_MIN && A_value <= BTN1_MAX) {
//             menu_option = (menu_option - 1 + menu_count) % menu_count;
//         } else if (A_value >= BTN2_MIN && A_value <= BTN2_MAX) {
//             menu_option = (menu_option + 1) % menu_count;
//         } else if (A_value >= BTN3_MIN) {
//             switch(menu_option) {
//                 case 0:
//                     // currentState = STATUS_CHECK;
//                     Serial.println("STATUS CHECK");
//                     // show status func
//                     break;
//                 case 1:
//                     // currentState = FEEDING;
//                     Serial.println("FEEDING");
//                     // FEEDING FUNC
//                     break;
//                 case 2:
//                     // currentState = GAME_MENU;
//                     Serial.println("GAME MENU");
//                     // show game menu
//                     break;
//                 case 3:
//                     // currentState = MAINTENANCE;
//                     Serial.println("MAINTENANCE");
//                     // show sensor data
//                     break;
//                 default:
//                     Serial.println("Fatal error in menu input processing!");
//             }
//         }
//         displayMainMenu();
//     }
// }


// void displayMainMenu() {
//     const char* menuOptions[] = { "SHOW STATUS", "FEED", "PLAY A GAME", "MAINTENANCE" };
//     const int menuCount = sizeof(menuOptions) / sizeof(menuOptions[0]);

//     display.clearDisplay();
//     display.setTextColor(WHITE);
//     display.setTextSize(2);
//     display.setCursor(0, 0);
//     display.println("MAIN MENU");

//     display.setTextSize(1);

//     for (int i = 0; i < menuCount; i++) {
//         if (menu_option == i) {
//             display.fillRect(0, 12 * i + 1 + TOP_OFFSET, 128, 9, WHITE); 
//             display.setTextColor(BLACK);
//         } else {
//             display.setTextColor(WHITE);
//         }

//         display.setCursor(1, 12 * i + 2 + TOP_OFFSET);
//         display.print(menuOptions[i]);
//     }

//     display.display();
// }
