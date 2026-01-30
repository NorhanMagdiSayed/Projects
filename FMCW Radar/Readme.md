
# FMCW Radar Prototype (Hardware Build)

![FMCW Radar Setup](<Images/1.jpeg>)

## Overview
This project is a practical implementation of a **Frequency Modulated Continuous Wave (FMCW) radar**.  
I built the **IF (baseband) circuitry** on a breadboard, connected it with an **RF front-end**, and assembled a complete radar setup capable of producing a **beat (IF) signal** that can be analyzed using FFT to detect targets.

## How FMCW Radar Works (Short)
FMCW radar transmits a frequency-modulated RF signal (triangular ramp). The received echo is delayed, and when it is mixed with the transmitted signal, it produces a **beat frequency**.  
That beat frequency is used to estimate **range** (and can also be used for motion depending on the waveform and processing).

---

## System Architecture
The radar consists of three main parts:
1. **Analog front-end (RF TX/RX):** transmit, receive, and mixing stages  
2. **Antennas:** for transmission and reception  
3. **IF/Baseband chain + processing:** filtering/amplification and signal analysis

![Block Diagram](<Images/Block diagram of the target FMCW radar.png>)

---

## IF / Baseband Hardware (Breadboard)
The IF chain was assembled step-by-step and verified at each stage:

### 1) Power Supply
Provides stable rails for the baseband circuitry.

![Power Supply Schematic](<Images/Schematic of power supply.png>)

### 2) Ramp (Triangle) Generator
Generates the modulation ramp (and sync) used to drive the RF modulation.

![Ramp Generator Schematic](<Images/Schematic of the ramp generator.png>)

### 3) Low-pass Filter
Limits the bandwidth of the IF/beat signal and reduces high-frequency noise.

![Low-pass Filter Schematic](<Images/Schematic of the Low-pass Filter.png>)

### 4) Video Amplifier
Amplifies the IF/beat signal to a measurable level (gain can be adjusted).

![Video Amplifier Schematic](<Images/Schematic of the Video Amplifier.png>)

---

## Build Photos
### Full setup
![Full setup](<Images/6.jpeg>)

### Setup with measurement/laptop
![Setup with laptop](<Images/2.jpeg>)
![Setup with laptop](<Images/3.jpeg>)

### Top views / wiring
![Top view](<Images/4.jpeg>)
![Top view](<Images/5.jpeg>)
![Breadboard close-up](<Images/7.jpeg>)

---

## How to Run / Test (Quick)
1. Power the circuit and confirm stable supply voltages.
2. Check the ramp generator output (triangle + sync if available).
3. Connect the RF chain and verify the modulated RF output and mixer output.
4. Feed the mixer output into the IF chain (LPF + amplifier).
5. Capture the **video/beat signal** and apply FFT to identify peaks (targets).

---

## Notes
- Verify each stage independently before connecting the full system.
- Keep wiring short and ensure solid grounding to reduce coupling and noise.
- If the signal clips, reduce gain in the video amplifier stage.

## Keywords
FMCW Radar, RF Front-End, Mixer, LNA, VCO, Beat Frequency, IF Signal, FFT
