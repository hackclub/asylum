#include <Arduino.h>
#include <WiFi.h>
#include <SD.h>
#include "config.h"

bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void startHotspot() {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(hotspot_ssid, hotspot_password);
    Serial.println("Hotspot started");
    Serial.println("SSID: " + String(hotspot_ssid));
    Serial.println("Password: " + String(hotspot_password));
}

void connectToWiFi(const char* ssid, const char* password) {
    WiFi.hostname(hostname);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < reconnect_attempts) {
        delay(reconnect_interval);
        Serial.println("Attempting to reconnect to WiFi...");
        attempts++;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect to the WiFi network");
        startHotspot();
    } else {
        Serial.println("Connected to the WiFi network");
    }
}

void disconnectFromWiFi() {
    WiFi.disconnect(true);
    Serial.println("Disconnected from the WiFi network");
}

void reconnectToWiFi() {
    disconnectFromWiFi();
    connectToWiFi(wifi_ssid, wifi_password);
}

void saveCredentialsToSD(const char* ssid, const char* password) {
    File file = SD.open("/wifi_credentials.txt", FILE_WRITE);
    if (file) {
        file.println(ssid);
        file.println(password);
        file.close();
        Serial.println("Wi-Fi credentials saved to SD card");
    } else {
        Serial.println("Failed to open file for writing");
    }
}

void loadCredentialsFromSD(char* ssid, char* password) {
    File file = SD.open("/wifi_credentials.txt");
    if (file) {
        if (file.available()) {
            file.readBytesUntil('\n', ssid, 32);
            file.readBytesUntil('\n', password, 32);
        }
        file.close();
        Serial.println("Wi-Fi credentials loaded from SD card");
    } else {
        Serial.println("Failed to open file for reading");
    }
}