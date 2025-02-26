#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "config.h"

bool WiFiEventHandlerRegistered = false;

void WiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Connected to WiFi!");
    Serial.print("Signal strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}

void WiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.print("Disconnected from WiFi, reason: ");
    Serial.println(info.wifi_sta_disconnected.reason);
    Serial.println("Trying to reconnect...");
    WiFi.setHostname(hostname);
    WiFi.begin(ssid, password);
}

bool void connectToWiFi()
{
    WiFi.setHostname(hostname);
    if (!WiFiEventHandlerRegistered)
    {
        WiFi.onEvent(WiFiConnected, WiFiEvent_t::SYSTEM_EVENT_STA_CONNECTED);
        WiFi.onEvent(WiFiDisconnected, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
        WiFiEventHandlerRegistered = true;
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - startAttemptTime > reconnect_interval)
        {
            return false;
        }
    }

    return true;
}