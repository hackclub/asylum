#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SD.h>
#include "handleNetwork.h"
#include "config.h"

WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", "<form action=\"/save\" method=\"POST\">SSID: <input type=\"text\" name=\"ssid\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Save\"></form>");
}

void handleSave() {
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    saveCredentialsToSD(ssid.c_str(), password.c_str());
    server.send(200, "text/html", "Credentials saved. Rebooting...");
    delay(2000);
    ESP.restart();
}

void setup() {
    Serial.begin(115200);
    if (!SD.begin(SD_CS)) {
        Serial.println("Card Mount Failed");
        return;
    }

    loadCredentialsFromSD(wifi_ssid, wifi_password);
    connectToWiFi();

    server.on("/", handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.begin();
}

void loop() {
    server.handleClient();
}