# Project Idea - Interactive Mini-Robot Companion/Pet
## A Tamagotchi/Furby inspired Arduino Project
This project is a mini-robot "companion" designed to simulate the care and interaction experience of a classic virtual pet. Users can interact with the robot by satisfying its needs, playing minigames, and enjoying its quirky behaviors.

<!-- ##Table of Contents -->

## Intro
### Initial Idea and Inspiration
The inspiration for this project came from the popularity of electronic toys like the Tamagotchi (especially in the late '90s) and Furby (popular in the early 2000s).

### Usefulness
Designing this little robot is useful for developing practical skills in both hardware and software engineering. Additionally, it can serve as an educational (or just fun) toy for children.

## Overview
### Features
- Basic Needs System:
    - Tracks hunger, happiness, and energy levels
    - Needs decrease over time and require user interaction
- Minigames:
    - To satisfy the robot's happiness needs, the user needs to play minigames with it: a reaction-based minigame or a simple "guess the number" game.
- Expressive outputs:
    - The robot will display its mood using a small OLED screen and an RGB LED.
    - It will also remind the user of its needs or react to certain interactions using a buzzer.
- Interactive controls:
    - Buttons to feed, play, and interact with the robot.
    - Additional sensors: a gyroscope and a proximity sensor for better interaction.

### Block Diagram
[ADD BLOCK DIAGRAM]

## Hardware Design
### Bill of Materials (BoM)
| Component    | Quantity | Description |
| ---------    | :------: | ----------- |
| Arduino Uno  |    2     | 2 Microcontrollers to act as Master and Slave |
| Push Buttons |   3-5    | Buttons for interacting |
| OLED Display |    1     | For showing expressions and information |
| RGB LED      |    1     | To indicate mood with color changes |
| Piezo Buzzer |    1     | For sound effects and alerts |
| Resistors (various)| ? | TBD
| Breadboard and wires | 1 set | For assembling the circuit |
| Battery pack (5V?) | 1 | To power the system |
| Servo Motor | 1-2 | For movable parts (like hands or ears) |
| Gyroscope | 1 | For position angle detection |
| Proximity Sensor | 1 | TBD

## Software Design
- IDE: PlatformIO (Visual Studio Code extension)
- Used libraries: TBD
- TBD

## Setup
TBD

> [!CAUTION]
> This README file is still a work in progress! It will be updated together with the project's progress.