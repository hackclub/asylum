This is my first PCB design:


![PCB](https://github.com/user-attachments/assets/f8f9c4fe-892f-42b5-af5d-2206a75f467d)


This is the Case for it:


<img width="610" alt="Screenshot 2024-12-21 at 1 17 18 PM" src="https://github.com/user-attachments/assets/cddb1763-db29-4d2e-88c6-5455ead36fd9" />


There are four pillars designed to hold the PCB, allowing it to slide in and out of the enclosure easily.


<img width="899" alt="Screenshot 2025-02-19 at 2 31 27 PM" src="https://github.com/user-attachments/assets/3c4947ff-bde6-49ce-885f-627d74da129c" />


This the Wokwi Script:  https://wokwi.com/projects/417352360582221825




## Overview

This project is a weather station built using the Wemos C3 Mini, a 1.8-inch TFT display, and multiple buttons for user interaction. It also features an emergency button system connected to a Raspberry Pi Pico W to send alerts to the display when triggered.

## Bill of Materials (BOM)

| Component                                                                                                                                                                | Quantity      | Description                                               | Price             |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------- | --------------------------------------------------------- | ---------------- |
| Wemos C3 Mini                                                                                                                                                            | 1             | ESP32-C3-based microcontroller with WiFi support          | HackClub          |
| 1.8-inch TFT Display                                                                                                                                                     | 1             | SPI-based TFT LCD for graphical display                   | HackClub          |
| SMD Tactile Switches ([TSD003B07026A03](https://robu.in/product/tsd003b07026a03-bzcn-6mm-7mm-50ma-round-button-standing-paste-6mm-260gf-12v-smd-tactile-switches-rohs/)) | 4             | 6mm, SMD push-button switches                             | Rs 8 each        |
| **Emergency Button (LA38-11ZS)** ([LA38-11ZS](https://robu.in/product/la38-11zs-mushroom-head-emergency-push-button-switch/?gad_source=1&gclid=CjwKCAiAt4C-BhBcEiwA8Kp0CeTryFRPVeAwR5uKaNZ_vN4STMENM_ef8wTu3p2f-RRopzExGq2cXxoCmYAQAvD_BwE)) | 1             | Large mushroom-head emergency switch                      | Rs 139           |
| Raspberry Pi Pico W                                                                                                                                                      | 1             | Connected to the emergency button for WiFi-based alerting | I already have it |
| Resistors (Pull-down)                                                                                                                                                    | 4 (if needed) | 10kΩ for button inputs if necessary                       | I already have it |
| PCB / Prototype Board                                                                                                                                                    | 1             | For assembling components                                 | $17.01            |
| Connecting Wires / Headers                                                                                                                                               | As needed     | Jumper wires or soldered connections                      | -                |


### its not been coded but will do it after my exams 


## Button Functions

### 1. **Button 1: Switch Data Display Mode**

- Toggles between different weather data views:
  - **Mode 1:** Temperature & Humidity
  - **Mode 2:** Pressure & Wind Speed
  - **Mode 3:** Forecast Summary

### 2. **Button 2: Graph Mode / History View**

- Displays graphical trends for temperature, humidity, and pressure over time.
- Can cycle through different graphs with multiple presses.

### 3. Button 3: Settings 

- Opens a settings menu to adjust brightness, 

### 4. **Button 4: Alert Acknowledgment / Sound Alarm**

- If an emergency alert is triggered by the Pico W, pressing this button will acknowledge it and clear the alert.
- Can also be used to trigger a sound or flash an LED as a local notification.

## Emergency Button Integration

- The **LA38-11ZS emergency button** is connected to the Raspberry Pi Pico W(which i have already ).
- When pressed, the Pico W sends an **MQTT message** or **HTTP request** to the Wemos C3.
- The TFT display will show an alert like **"Emergency! Grandparent needs help!"**.
- I already have the design a enclosure for it in mind I will make the enclouser when my exam end(its not 3d printed let me be creative :p )
## Pricing

- emergency button = ₹ 139.00
- buttons = ₹ 2 * 4 = ₹ 8
- PCB = $ 17
- Delevery(for components) = ₹ 49
## Total: $ 19.46

---
## PCB Price :



<img width="1440" alt="Screenshot 2025-02-27 at 3 01 09 PM" src="https://github.com/user-attachments/assets/d7429aad-98a6-45d1-acd1-022fab92ae70" />


