# **Interactive Mini-Robot Companion / Pet**
## A Tamagotchi / Furby-inspired Arduino Project  

This project is a mini-robot "companion" designed to simulate the care and interaction experience of a classic virtual pet. Users can interact with the robot by satisfying its needs, playing minigames, and enjoying its quirky behaviors.

> [!CAUTION]
> This README is a work in progress. Updates will be made as the project develops.

## **Introduction**

### **Initial Idea and Inspiration**  
The inspiration for this project came from the popularity of electronic toys like the Tamagotchi (especially in the late '90s) and Furby (popular in the early 2000s).  

### **Usefulness**  
Designing this robot develops practical skills in both hardware (wiring, circuit design, sensor integration) and software engineering (C programming, modular coding, logic implementation). The project is also a fun, creative challenge and can serve as an educational toy for children.

## **Overview**

### **Features**
- **Basic Needs System**:
  - Tracks hunger, happiness, and energy levels.
  - Needs decrease over time and require user interaction.  
- **Minigames**:
  - *(TBD)*
- **Expressive Outputs**:
  - OLED screen displays emotions and statuses.
  - LCD Display for minigames and interaction.
  - Buzzer for sound effects and alerts.  
- **Interactive Controls**:
  - Buttons for feeding, playing, and interacting.
  - Infrared remote control for more complex minigames.
  - Ambient temperature and humidity sensor - keep the bot in a comfortable environment.
  - Proximity sensor for enhanced interaction.

### **Block Diagram**  
![block diagram](./schematics/images/block_diagram.jpeg)

## **Hardware Design**

### **Bill of Materials**  

| Component                      | Quantity | Description                                     |
|--------------------------------|:--------:|------------------------------------------------ |
| Arduino Uno R3                 |    1     | Microcontroller for controlling the system.     |
| Push Buttons                   |    5     | Buttons for user interaction.                   |
| Servo Motor                    |    1     | For mechanical reaction.                        |
| ST7735 SPI LCD Display         |    1     | Color LCD display for visual output.            |
| GM009605 I2C OLED Display      |    1     | Monochrome OLED display for status/moods.       |
| VS188388 IR Receiver           |    1     | Infrared sensor for remote input.               |
| HC-SR04 Proximity Sensor       |    1     | Detects user proximity for interaction.         |
| DHT11 Temp and Humidity Sensor |    1     | Measures temperature and humidity.              |
| Buzzer                         |    1     | Generates sound alerts and effects.             |
| Resistors (various)            |    6     | For limiting current and voltage division.      |
| Capacitor (100 µF)             |    1     | For noise reduction and voltage stabilization.   |
| AA Battery Holder (4 slots)    |    1     | Holds 4 AA batteries for power.                 |
| AA Batteries                   |    4     | Provide 4.8V total power.                      |
| 9V Battery                     |    1     | Provides power for the Arduino Uno             |
| Phototransistor                |    1     | Light-sensitive transistor for light detection |
| Wires and Breadboard           |    1 set | For circuit assembly.                          |

### **Circuit Schematic**
![circuit schematic cropped](./schematics/images/kicad_schematic%20-%20cropped.png)
*Please refer to the [schematics/files](./schematics/files) folder for the KiCAD project file. 

## **Software Design**  
- **IDE**: PlatformIO (Visual Studio Code extension)  

- **Libraries**:  
  (*TBD*)  

- **Functionality**:  
  - Manage user input from buttons and sensors.
  - Control OLED, LCD, servo and buzzer outputs for feedback.
  - Execute game logic and manage the needs system.  
  - Modular design for scalability and debugging.

## **Setup**  
(*TBD*)

## **References and Resources**  
### **Software Resources**  
- PlatformIO: https://platformio.org

### **Hardware Resources**  
- Arduino Uno Datasheet: https://www.arduino.cc/en/main/arduinoBoardUno

## License
This project is licensed under the [MIT License](LICENSE).  
Feel free to use, modify, and distribute this project as long as you include proper attribution.


