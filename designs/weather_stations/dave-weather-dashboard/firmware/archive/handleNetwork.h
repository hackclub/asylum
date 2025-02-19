#ifndef HANDLE_NETWORK_H
#define HANDLE_NETWORK_H

#include <Arduino.h>
#include  <WiFi.h>
#include "config.h"

bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void resetWifi() {
    WiFi.mode(WIFI_MODE_NULL)
}

/*void startHotspot() {
    WiFi.mode(WIFI_AP_STA); // For the sake of like a list or maybe picker on the SSID on the page that's going to be hosted maybee
    WiFi.softAP(hotspot_ssid, hotspot_password);
    Serial.println("Hotspot started");
    Serial.println("SSID: " + String(hotspot_ssid));
    Serial.println("Password: " + String(hotspot_password));
    Serial.println("IP Address: " + WiFi.softAPIP().toString());
}*/

void connectToWiFi() {
    WiFi.hostname(wifi_hostname);
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
}

void disconnectFromWiFi() {
    WiFi.disconnect(true);
    Serial.println("Disconnected from the WiFi network");
}

void reconnectToWiFi() {
    disconnectFromWiFi();
    connectToWiFi();
}

#endif