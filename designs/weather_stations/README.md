# weather station
Here's my submission for my weather station! Under the asylum "dragons_weather"

## Features:
- Displays:
    - Date
    - Temperature 
    - Settings
- 4 WS2812Bs for dynamic LED effects
- A switch for turning on and off
- Slider for settings


## PCB
Here's a picture of my schematic, I wired a Wemos ESP32-S3 module to a TFT display, 5 WS2812B LEDs, a slider for settings

Schematic            |  PCB
:-------------------------:|:-------------------------:
![Screenshot 2025-01-27 211234](https://github.com/user-attachments/assets/2088f276-877b-47b5-9cea-305067c11d55)
tic.png)  |  ![Screenshot 2025-01-27 211213](https://github.com/user-attachments/assets/6c694724-561b-40c4-a9fa-53a2c9137b01)


[ x ] I ran DRC in KiCad and have made sure there are 0 errors!

## CAD Model:
Everything fits together using 4 M3 Heatset inserts

![Screenshot 2025-01-27 211705](https://github.com/user-attachments/assets/9a4c252e-04fb-4102-9352-95bd7987d6c8)

![Screenshot 2025-01-27 211719](https://github.com/user-attachments/assets/ff207bfb-3439-4747-8868-8af1710aee0b)


## Firmware overview
Firmware is written in aurdino, it grabs data from a API. Code for turining it off and on, slider and basic settings are written

[ x ] I remembered to exclude any personal information, including API Keys, WiFi passwords, etc

I will be sourcing the following parts with my grant:
- 1x PCB from JLCPCB
    - $2 for 5x + $1.50 shipping

- 1x SPDT slide switch [(ADAFRUIT)](https://www.adafruit.com/product/4219) $2.95



Total before tax: $6.5

I'll also be source the following parts myself since I already have them and would like to help Hack Club:

- 3d PRINT
