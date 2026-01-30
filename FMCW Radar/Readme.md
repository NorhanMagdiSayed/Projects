# FMCW Radar Prototype (Hardware Build)

<p align="center">
  <img src="Images/1.jpeg" width="550">
</p>

## Overview
This project is a practical implementation of a **Frequency Modulated Continuous Wave (FMCW) radar**.  
I built the **IF (baseband) circuitry** on a breadboard, connected it to an **RF front-end**, and assembled a complete radar setup capable of producing a **beat (IF) signal** that can be analyzed using FFT to detect targets.

## How FMCW Radar Works 
FMCW radar transmits a frequency-modulated RF signal (triangular ramp). The received echo is delayed, and when it is mixed with the transmitted signal, it produces a **beat frequency**.  
That beat frequency is used to estimate **range** (and can also be used for motion depending on waveform and processing).

---

## System Architecture

<p align="center">
  <img src="Images/Block diagram of the target FMCW radar.png" width="700">
</p>

The radar consists of three main parts:
1. **Analog front-end (RF TX/RX):** transmit, receive, and mixing stages  
2. **Antennas:** for transmission and reception  
3. **IF/Baseband chain + processing:** filtering/amplification and signal analysis  

---

## IF / Baseband Hardware (Breadboard)

### 1) Power Supply
<p align="center">
  <img src="Images/Schematic of power supply.png" width="650">
</p>

### 2) Ramp (Triangle) Generator
<p align="center">
  <img src="Images/Schematic of the ramp generator.png" width="650">
</p>

### 3) Low-pass Filter
<p align="center">
  <img src="Images/Schematic of the Low-pass Filter.png" width="650">
</p>

### 4) Video Amplifier
<p align="center">
  <img src="Images/Schematic of the Video Amplifier.png" width="650">
</p>

---

## Build Photos

### Full radar setup
<p align="center">
  <img src="Images/1.jpeg" width="420">
  <img src="Images/4.jpeg" width="420">
 
</p>

### Top views / wiring
<p align="center">
  <img src="Images/2.jpeg" width="420">
  <img src="Images/3.jpeg" width="420">
  <img src="Images/5.jpeg" width="420">
</p>

### Measurement / test setup
<p align="center">
  <img src="Images/7.jpeg" width="520">
</p>

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
