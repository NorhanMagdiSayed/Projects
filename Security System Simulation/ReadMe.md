
# Embedded Security System with UART Communication

This is a simulation of a microcontroller-based security system designed using two **ATmega32** microcontrollers. The system integrates a PIR sensor, keypad, LCD, LEDs, buzzer, 7-segment display, and DC motor to emulate a complete access control and intruder alert system. The project is developed and simulated using **Proteus Design Suite**, with all driver files written manually in C.

---

## Components Used

- 2 × ATmega32 Microcontrollers (Master & Slave)
- PIR Motion Sensor
- 4×4 Keypad
- 16×2 LCD Display
- 7-Segment Display
- 2 × Green LEDs (Access Granted)
- 2 × Red LEDs (Intruder Alert)
- DC Motor (Door Simulation)
- Buzzer
- Custom-written peripheral drivers in C

---

## System Overview

### Communication:
- **UART Serial Communication** is used between the two ATmega32 MCUs:
  - **Master MCU** handles keypad input.
  - **Slave MCU** controls the LCD, LEDs, motor, buzzer, and PIR sensor.

### Workflow:
1. **Motion Detection:**
   - When the PIR sensor detects motion (logic high), the LCD prompts the user to enter a password.

2. **Password Verification:**
   - If the entered password is correct:
     - LCD shows `Access Approved`
     - Green LEDs light up
     - DC motor activates (door opens)
   - If the password is incorrect:
     - LCD shows `Access Denied`
     - 7-segment display increments attempt count

3. **Intruder Alert:**
   - After 3 failed attempts:
     - LCD displays `There is an intruder!!`
     - Red LEDs turn on
     - Buzzer is activated

---

## 🛠 Development Notes

- Designed and simulated using **Proteus**
- All `.c` driver files for the LCD, keypad, UART, and other components were developed manually
- Simulation showcases real-world logic for home/office security systems

---

## 📸 Simulation Preview
![image](https://github.com/user-attachments/assets/5210aa6e-d9c4-44e3-8c4a-482f54d445d5)
![image](https://github.com/user-attachments/assets/f3bb4011-2565-43e2-b2ed-46a032d8bf49)
![image](https://github.com/user-attachments/assets/e04b1bf4-da82-4a17-b731-81a2431b623e)
![image](https://github.com/user-attachments/assets/03c75437-94bd-489d-bdd2-8ba89843b503)
![image](https://github.com/user-attachments/assets/053d749f-e2ed-4926-bac1-7ee9ddfe7266)
![image](https://github.com/user-attachments/assets/6fbbd1ce-e5fe-4d1c-843b-019eeb149024)








---



