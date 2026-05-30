# HTTP Web Server Project

This project implements an HTTP web server that allows users to input Wi-Fi credentials and displays a list of available Wi-Fi networks. The project utilizes an SD card to store the Wi-Fi credentials and is designed for use with an ESP32 microcontroller.

## Project Structure

```
http-web-server
├── src
│   ├── main.cpp          # Entry point of the application
│   ├── handleNetwork.h   # Functions for managing Wi-Fi connections
│   ├── config.h          # Constants for Wi-Fi and SD card configurations
│   ├── web
│   │   ├── index.html    # HTML structure for the web interface
│   │   └── script.js      # JavaScript for handling user interactions
│   └── types
│       └── index.h       # Custom types and structures
├── platformio.ini        # PlatformIO configuration file
└── README.md             # Project documentation
```

## Setup Instructions

1. **Clone the Repository**: 
   Clone this repository to your local machine.

2. **Install PlatformIO**: 
   Ensure you have PlatformIO installed in your development environment.

3. **Configure Wi-Fi Credentials**: 
   Open `src/config.h` and update the `wifi_ssid` and `wifi_password` with your Wi-Fi credentials.

4. **Build the Project**: 
   Use PlatformIO to build the project. This will compile the code and prepare it for upload.

5. **Upload to ESP32**: 
   Connect your ESP32 board to your computer and upload the firmware using PlatformIO.

6. **Access the Web Interface**: 
   Once the ESP32 is connected to Wi-Fi, open a web browser and navigate to the IP address assigned to the ESP32 to access the web interface.

## Usage Guidelines

- Use the textboxes to input your Wi-Fi SSID and password.
- The list picker will display available Wi-Fi networks.
- Submit the form to save the credentials to the SD card.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.