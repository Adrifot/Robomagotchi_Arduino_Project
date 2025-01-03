# **Robomagotchi**
## A Tamagotchi / Furby-Inspired Arduino Project  

This project is a mini-robot companion designed to simulate the experience of caring for and interacting with a virtual pet. Users can engage with the robot by satisfying its needs, playing minigames, and interacting through various sensors, buttons, and outputs. The robot responds dynamically to user input and its environment.

> [!CAUTION]
> This README is a work in progress. Updates will be made as the project develops.

## **Table of Contents**
1. [Introduction](#introduction)  
2. [Overview](#overview)  
3. [Hardware Design](#hardware-design)  
4. [Software Design](#software-design)  
5. [Setup Instructions](#setup-instructions)  
6. [References and Resources](#references-and-resources)  
7. [License Information](#license)  



## **Introduction**

### **Initial Idea and Inspiration**  
The inspiration for this project came from the nostalgic electronic toys like Tamagotchi and Furby. These devices entertained users by simulating the care of a virtual pet. The goal was to blend this concept with modern technology and sensors to create an interactive mini-robot that is not only fun but also educational, showcasing hardware and software integration.  

### **Purpose and Usefulness**  
- **Skill Development**: The project aids in learning embedded systems, sensor integration, and modular software development.  
- **Entertainment**: It provides users with a fun, interactive experience of caring for a virtual pet.  
- **Educational Value**: Useful for teaching kids or beginners about electronics, programming, and robotics concepts.  



## **Overview**

### **Features**  
- **Basic Needs System**:  
  - Tracks virtual hunger, happiness, and energy levels.  
  - Needs decrease over time, prompting user interaction to keep the robot happy.  
- **Minigames**:  
  - *(TBD)*
- **Expressive Outputs**:  
  - OLED screen displays emotions and statuses.  
  - LCD display for additional feedback and minigame visuals.  
  - Buzzer generates alerts and sound effects for user feedback.
  - The servo motor functions as the robot's "antenna", moving in response to specific interactions or reactions.
- **Interactive Controls**:  
  - Buttons allow feeding, playing, and other interactions.  
  - Proximity sensor detects when a user is nearby.  
  - IR receiver enables control via a remote.  
  - Temperature and humidity sensor ensures the robot "lives" in a comfortable environment.  
- **Dynamic Input Sensors**:  
  - Light detection using a phototransistor for additional interactivity. 

### **Block Diagram**  
![Block Diagram](./schematics/images/block_diagram.png)  



## **Hardware Design**

### **Bill of Materials (BoM)**  

| Component                      | Quantity | Description                                     | Datasheet |
|--------------------------------|:--------:|-------------------------------------------------|:---------:|
| Arduino Uno R3                 |    1     | Microcontroller for controlling the system.     |[Link](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf)|          
| Push Buttons                   |    5     | Buttons for user interaction.                   | N/A |
| SM-S2309S Servo Motor          |    1     | For mechanical reaction.                        | [Link](https://www.rhydolabz.com/documents/22/SM_S2309S.pdf) |
| ST7735 SPI LCD Display         |    1     | Color LCD display for visual output.            | [Link](https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf) |
| GM009605 I2C OLED Display      |    1     | Monochrome OLED display for status/moods.       | [Link](https://www.datasheethub.com/wp-content/uploads/2022/08/SSD1306.pdf) |
| VS188388 IR Receiver           |    1     | Infrared sensor for remote input.               | [Link](https://eeshop.unl.edu/pdf/VS1838-Infrared-Receiver-datasheet.pdf) |
| HC-SR04 Proximity Sensor       |    1     | Detects user proximity for interaction.         | [Link](https://docs.google.com/document/d/1Y-yZnNhMYy7rwhAgyL_pfa39RsB-x2qR4vP8saG73rE/edit?pli=1&tab=t.0) |
| DHT11 Temp and Humidity Sensor |    1     | Measures temperature and humidity.              | [Link](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf) |
| Buzzer                         |    1     | Generates sound alerts and effects.             | N/A |
| Resistors (various)            |    10    | For limiting current and voltage division.      | N/A |
| Capacitor (100 µF)             |    1     | For noise reduction and voltage stabilization.  | N/A |
| 9V Battery                     |    1     | Provides power for the Arduino Uno.             | N/A |
| 9V Battery connector           |    1     | Permits battery connection using pins           | N/A |
| Phototransistor                |    1     | Light-sensitive transistor for light detection. | N/A |
| Wires and Breadboard           |    1 set | For circuit assembly and prototyping.           | N/A |
| Infrared Remote                |    1     | Controls the bot through the IR receiver.       | N/A |

### **Circuit Schematic**   
![Circuit Schematic](./schematics/images/kicad_schematic_cropped.png)  

*Refer to the [/schematics/files](./schematics/files) folder for the full KiCAD project file.*  



## **Software Design**  

- **IDE**: PlatformIO (Visual Studio Code Extension)  
- **Libraries**:  
  - *(TBD)*
- **Key Functionalities**:  
  - Manage user inputs (buttons, sensors, IR remote).  
  - Control outputs (OLED, LCD, buzzer, servo).  
  - Implement logic for virtual pet needs and decay rates.  
  - Minigame execution and feedback mechanisms.  
  - Modular code design for future scalability and debugging.  



## **Setup Instructions**  
### **Hardware Setup**
1. Connect the microcontroller and the components using the following table:

| **Component**      | **Pin Name** | **Connected to**  |
|--------------------|--------------|-------------------|
|**Servo Motor**     |PWM           |Pin 5              |
|                    |+             |9V through voltage divider (R8-R7-R6)|
|                    |-             |GND                |
|**LCD Display**     |GND           |GND                |
|                    |VCC           |3.3V               |
|                    |SCL           |Pin 13             |
|                    |SDA           |Pin 11             |
|                    |RES           |Pin 8              |
|                    |DC            |Pin 7              |
|                    |CS            |Pin 4              |
|                    |BLK           |Pin 10             |
|**OLED Display**    |GND           |GND                |
|                    |VDD           |3.3V               |
|                    |SCK           |Pin A5             |
|                    |SDA           |Pin A4             |
|**IR Receiver**     |SIG           |Pin 9              |
|                    |GND           |GND                |
|                    |VCC           |3.3V               |
|**Proximity Sensor**|VCC           |5V                 |
|                    |TRIG          |Pin A2             |
|                    |ECHO          |Pin 12             |
|                    |GND           |GND                |
|**Temp Sensor**     |Vs            |3.3V               |
|                    |Vout          |Pin A3             |
|                    |GND           |GND                |
|**Buzzer**          |+             |Pin 6 through Rb   |
|                    |-             |GND                |

  - Connect the **100μF capacitor** between the servo motor's + and - pins.   
  - Connect the **resistor and pushbutton ladder** to 3.3 volts on one side and GND on the other side, as per the [schematic](#circuit-schematic). Connect Pin 2 between R4 and R5. R5 will act as a pull-down resistor.
  - Connect the + pin on the **phototransistor** to 5V and - to GND through a 10kΩ resistor (Rq). Connect the A0 pin between the resistor and power to measure its voltage output.

2. Connect the negative pin of the 9V battery to the same ground as the Arduino board. 
3. Connect the + pin of the 9V battery connector to the breadboard and then to the **VIN** pin on the Arduino board (as shown in the schematic).

### **Software setup**
*(TBD)*

## **References and Resources**  

### **Software Resources**  
- [PlatformIO](https://platformio.org)  

### **Hardware Resources**  
See the [BoM](#bill-of-materials-bom) for datasheets for each component (if applicable).



## **License**  
This project is licensed under the [MIT License](LICENSE).  
Feel free to use, modify, and distribute this project as long as proper attribution is provided.  
