# Dual NRF24 Serial-Controlled Jammer

A dual-radio RF jammer built using two NRF24L01+ modules on independent SPI buses.  
Designed for experimenting with **RF channel interference**, **BLE/Wi-Fi spectrum flooding**, and **channel hopping techniques**.

---

## Features

- **Interactive Serial Interface**  
  Menu-driven CLI over serial for real-time mode switching
- **Targeted Jamming**  
  Set NRF24 radios to Wi-Fi-mapped channels
- **Random Sweep Mode**  
  Continuously hops across 2.4 GHz spectrum (1–84)
- **Aggressive Blast Mode**  
  Floods a narrow channel range with rapid randomized switching
- **Dual-Radio Parallel Operation**  
  Controlled via SPI1 and SPI2 simultaneously
- [BLE Spoof Mode] *(Coming soon...)*

---

## Hardware Setup

| Component      | Description                     |
|----------------|---------------------------------|
| MCU            | ESP32-based board (e.g., XIAO ESP32-C6) |
| Radio Modules  | 2 × NRF24L01+                   |
| SPI Buses      | SPI1 (VSPI), SPI2 (HSPI)        |
| Connections    | Custom pinout for CE/CSN lines  |

> **Ensure your ESP32 supports multiple SPI buses (VSPI & HSPI)**  
> Use **decoupling capacitors** near NRF24 power pins for stable operation

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

---

## Modes Overview

| Mode                 | Input | Behavior                                                       |
|----------------------|-------|----------------------------------------------------------------|
|   Target Channel     | `1`   | Prompts user for Wi-Fi channel (1–13), maps to NRF channels    |
|   Random Sweep       | `2`   | Continuously hops NRF channels randomly (1–84)                 |
|   Aggressive Flood   | `4`   | Rapid random flooding on NRF CH 3 ± 1                          |
|   Idle Mode          | `5`   | Stops all activity                                             |
|   BLE Spoof Mode     | `3`   | *(Coming soon...)*                                             |

---

## Sample Serial Output

```text
===== CYPHER JAMMER =====
1. Target specific wifi channel
2. Random sweep (Wi-Fi + BLE)
3. BLE flood spoof [coming soon]
4. Aggressive static flood
5. Exit
>>
```

---

## Technical Notes

- Uses `RF24` Arduino library
- `radio.write_register(0x1D, 0x06);` enables continuous carrier mode on the NRF24L01+
- `radio.write_register(0x00, 0x3E);` sets TX mode without auto-ack, no CRC, no retries
- Built without `beginTransmission()` — uses low-level register access

---

## Disclaimer

This project is intended **strictly for academic research** into RF signal interference, side-channel analysis, and anti-jamming techniques.  
**Do not use this tool maliciously** or interfere with public or private networks.

---

## Related Projects

- 🔗 BLE Beacon Flooder  
- 🔗 NRF24 Constant Carrier Analyzer  
- 🔗 BLE Packet Decoder & Analyzer  
- 🔗 BLE Anti-Jamming Testbed (WIP)

---

## Contact

**Nishant Keni**  
📧 [keninish7965@gmail.com](mailto:keninish7965@gmail.com)  
🔗 [LinkedIn](https://www.linkedin.com/in/your-link)

> "Obsessed with building the future, one byte at a time."
