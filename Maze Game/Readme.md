
# 🎮 Maze Game 

A smart and engaging maze game designed for one or two players using servo-controlled tilt mechanics. Players control the maze using either a **joystick** or an **app**, and aim to guide a ball to the goal within a time limit. The project combines **mechanical design**, **Arduino programming**, **real-time feedback**, and **user interaction** in a fun, challenging experience.

---

## Project Overview

- Controlled via **joystick** or **Bluetooth app**
- Moves on **X and Y axes** using two **servo motors**
- Features **single-player (5 rounds)** and **two-player (2 rounds)** modes
- Displays game status and score on **LCD**
- Includes **custom animated characters** and sound feedback
- Touch sensor detects goal completion
- Developed using **Arduino**, **Fusion 360**, and **Laser Cutting**

---

## Project Motivation

Inspired by classic marble maze games, this project adds an interactive and competitive twist by integrating electronics and embedded programming. The countdown timer and animated characters make the game more dynamic and rewarding, while the two-player mode adds social competition.

---

## Tools & Materials

- **Software:**
  - Fusion 360 (CAD)
  - Arduino IDE (code development)
  - Laser Maze Designer Website (maze layout)
  - LaserWork (laser cutting prep)

- **Hardware:**
  - Arduino Uno
  - 2 × Servo Motors
  - 1 × TTP223 Touch Sensor
  - Joystick Module
  - LCD I2C
  - Buzzer
  - Breadboard + Wires
  - 3mm Plywood

---

## Mechanical Design

### Maze Board
- Designed in **Fusion 360**
- Constructed with **3mm plywood**
- Consists of a base, inner rotating frame, and an outer frame for support
- Uses **t-slots** and **fillets** for easy assembly and a polished look

### Assembly Box
- Houses Arduino, joystick, and LCD
- Angled design for better screen visibility
- Components projected and cut via laser for precision fitting

---

## Fabrication Process

1. Maze layout generated using **Laser Maze Designer** and exported to DXF
2. Parts designed in Fusion, projected as sketches, and saved as DXF
3. Laser cut using speed/power:
   - **Black cuts:** Speed 20, Power 65
   - **Red engraving:** Speed 300, Power 25
4. Servo mounts and support designed for secure fitting

---

## Electronics & Circuit

### Inputs
- **Joystick:** X and Y analog control + push button
- **Touch Sensor:** Detects ball reaching goal

### Outputs
- **Servo Motors:** Tilt the maze
- **LCD I2C:** Shows messages, scores, and turn info
- **Buzzer:** Gives audible feedback

### Power
- Initially used 5V adapter, switched to **mobile charger 5V** for better current supply

### Wiring Summary
- Joystick → A0 (Y), A1 (X), D8 (button)
- Touch sensor → D9
- Servo motors → D3 (Y-axis), D5 (X-axis)
- LCD I2C → A4 (SDA), A5 (SCL)

---

## Programming

- **Libraries used:**
  - `Metro` for non-blocking timers
  - `VarSpeedServo` for smooth servo movement
  - `LiquidCrystal_I2C` for LCD display

- **Game Functions:**
  - `initiate()`: Startup screen + animation
  - `two_modes()`: Choose control mode (joystick or app)
  - `game_mode()` / `choose()`: Mode selection using joystick
  - `player()`: Countdown before each round
  - `round_5()` / `round_2()`: Core gameplay loops
  - `slowmove()`: Maps joystick values to servo angles

- **Modes Supported:**
  - Single player: 5 timed rounds, scoring based on ball touches
  - Two player: Alternating rounds with individual score tracking

---

## Demo / Showcase 
https://drive.google.com/drive/folders/10wYWjVl33bLUCOvKVC3OORXUD0XfY7GZ?usp=sharing


