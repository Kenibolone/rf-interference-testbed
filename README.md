# Dual NRF24 RF Interference Testbed

A dual-radio RF experimentation platform built using two NRF24L01+ modules on
independent SPI buses. This project is designed to study **RF channel occupancy**,
**interference behavior**, and **channel-hopping dynamics** in the 2.4 GHz ISM band.

---

## Overview

This system uses two NRF24L01+ transceivers operating in parallel to generate
controlled RF activity across selected or varying channels. A serial-based
interface allows dynamic reconfiguration of operating modes to observe how
continuous transmission, channel sweeps, and targeted channel selection affect
the RF environment.

The project focuses on **low-level radio behavior** rather than protocol-level
communication.

---

## Features

- **Interactive Serial Interface**  
  Menu-driven CLI for switching test modes at runtime

- **Targeted Channel Testing**  
  Maps Wi-Fi channels to corresponding NRF24 frequency bands for overlap studies

- **Random Channel Sweep Mode**  
  Pseudorandom hopping across the 2.4 GHz band (NRF channels 1–84)

- **Continuous Transmission Mode**  
  Sustained RF activity over a narrow channel range to study interference effects

- **Dual-Radio Parallel Operation**  
  Two NRF24L01+ modules controlled via independent SPI buses (VSPI & HSPI)

---

## Hardware Setup

| Component     | Description                                   |
|---------------|-----------------------------------------------|
| MCU           | ESP32-based board (e.g., XIAO ESP32-C6)       |
| RF Modules    | 2 × NRF24L01+                                 |
| SPI Buses     | ESP32 VSPI and HSPI (abstracted as SPI1/SPI2) |
| Power         | External 3.3 V with decoupling capacitors     |

> **Note:** Reliable operation requires proper power decoupling near the NRF24L01+
> modules due to high instantaneous current draw during transmission.

---

## Dependencies & Environment

- **Development Framework:** Arduino IDE
- **MCU Platform:** ESP32 (tested on ESP32-C6)
- **RF Library:**  
  - `RF24` Arduino library (TMRh20 fork)
- **Communication Interfaces:**  
  - SPI (VSPI & HSPI)
  - Serial (UART) for control interface

### Required Arduino Libraries

Install via Arduino Library Manager:
- `RF24` by TMRh20

### Board Support

- ESP32 board support package  
  (`https://dl.espressif.com/dl/package_esp32_index.json`)

---

## Notes on RF Behavior

This testbed focuses on transmission behavior at the physical layer. Protocol-
level features such as acknowledgments, CRC, and retries are intentionally
disabled to isolate RF occupancy and interference characteristics. Observations
may vary depending on antenna quality, power supply stability, and nearby RF
sources.

---

## Pin Configuration

```cpp
// SPI1 (VSPI) for radio1
SPI1.begin(5, 7, 6, 4);  // SCK, MISO, MOSI, CSN1
#define CE1 3

// SPI2 (HSPI) for radio2
SPI2.begin(10, 12, 11, 9);  // SCK, MISO, MOSI, CSN2
#define CE2 8
```
