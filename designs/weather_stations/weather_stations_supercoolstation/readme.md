# My Super Cool Weather Station!  
![image](https://github.com/user-attachments/assets/94a3b657-5180-463f-adc2-64936ae2276c)

![image](https://github.com/user-attachments/assets/ffc0935a-66c9-4125-a8d5-e90a2455ce4c)
![image](https://github.com/user-attachments/assets/302b1d6e-805b-4ab0-b1ad-7a012314721c)

## Features:
- Displays the current temperature and humidity.
- Fetches real-time data from [Open-Meteo](https://open-meteo.com/).
- Portable design powered by a LiPo battery

## Components:
- **C3 Mini**
- **TFT ST7735**
- **LiPo Battery and TP4056 Board**
- **1x 10 ohm resistor**
- **2x switch push buttons**
- **2x 10k ohm resistor**
- **1x Battery toggle switch**
- **1x 1n5817 schottky diode**

## How It Works:
1. Connects to a Wi-Fi network to fetch data from Open-Meteo API.
2. Parses the received JSON payload for temperature, humidity, and time data.
3. Displays the parsed data on the tft screen
