#include <Arduino.h>
#include <SD.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include "config.h"

/*
struct WeatherData {
    float temperature;
    String weatherDescription;
    float precipitation;
    float windSpeed;
    String windDirection;
    int humidity;
    String localDateTime;
}
*/

void WiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Connected to WiFi!");
    Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
    Serial.println("IP address: " + String(WiFi.localIP()));

    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        tft.println("Failed to obtain time");
    } else {
        Serial.println(&timeinfo, "Current time: %A, %B %d %Y %H:%M:%S");
    }

    showWeatherData();
}

void WiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from WiFi, reason: " + String(info.wifi_sta_disconnected.reason));
}

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_EN, MOSI, SCK, TFT_EN);
unsigned lastRefreshTime = 0;

void setup() {
    Serial.begin(115200);

    pinMode(REFRESH_BUTTON, INPUT_PULLUP);

    // SD
    /*if (!SD.begin(SD_CS))
    {
        Serial.println("SD card initialization failed!");
    }*/

    // TFT display
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(0);
    tft.fillScreen(ST7735_BLACK);

    // WiFi
    WiFi.disconnect(true);
    WiFi.onEvent(WiFiConnected, WiFiEvent_t::SYSTEM_EVENT_STA_CONNECTED);
    WiFi.onEvent(WiFiDisconnected, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
    showWeatherData();
}

void loop() {
    // Bounce2
    bounce.update();
    if (bounce.changed())
    {
        int debouncedInput = bounce.read();
        if (debouncedInput == LOW)
        {
            Serial.println("Button pressed!");
            showWeatherData();
        }
    }
    if (millis() - lastRefreshTime > REFRESH_INTERVAL)
    {
        showWeatherData();
        lastRefreshTime = millis();
    }
}

void showWeatherData() {
    lastRefreshTime = millis();
    
    tft.fillScreen(ST7735_BLACK);
    tft.println("Dave's Weather Dashboard");
    tft.print("Connecting to Wi-Fi");

    WiFi.setHostname(WIFI_HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && attempts < RECONNECT_ATTEMPTS && millis() - startAttemptTime < RECONNECT_INTERVAL) {
        delay(1000);
        tft.print(".");
        if (startAttemptTime - millis() > 10000) {
            WiFi.reconnect();
            startAttemptTime = millis();
            attempts++;
        }
    }

    tft.println("Connected to Wi-Fi!");
    tft.println("Fetching weather data, please wait..");

    WiFiClientSecure client;
    HTTPClient https;
    client.setInsecure();

    if (https.begin(BMKG_API_BASE + "/publik/prakiraan-cuaca?adm4=" + BMKG_KODE_WILAYAH_TINGKAT_IV)) {
        int httpCode = https.GET();
        if (httpCode == HTTP_CODE_OK) {
            JsonDocument doc(10240);
            DeserializationError error = deserializeJson(doc, https.getString());

            if (error) {
                Serial.println("JSON parsing failed: " + error.c_str());
                tft.println("JSON parsing failed");
            } else {
                JsonArray weatherToday = doc["data"][0]["cuaca"];

                struct tm timeinfo;
                if (!getLocalTime(&timeinfo)) {
                    Serial.println("Failed to obtain time");
                    tft.println("Failed to obtain time");
                    return;
                }

                time_t currentTime = mktime(&timeinfo);
                time_t closestTime = 0;
                JsonObject closestWeather;

                for (JsonObject weather : weatherToday) {
                    String datetimeStr = weather["datetime"];
                    struct tm weatherTimeinfo;
                    strptime(datetimeStr.c_str(), "%Y-%m-%dT%H:%M:%SZ", &weatherTimeinfo);
                    time_t weatherTime = mktime(&weatherTimeinfo) + GMT_OFFSET_SEC + DAYLIGHT_OFFSET_SEC;

                    if (closestTime == 0 || difftime(currentTime, weatherTime) < difftime(currentTime, closestTime)) {
                        closestTime = weatherTime;
                        closestWeather = weather;
                    }
                }

                /*
                WeatherData weatherData;
                weatherData.temperature = closestWeather["t"]; // in °C
                weatherData.weatherDescription = closestWeather["weather_desc_en"].as<String>();
                weatherData.precipitation = closestWeather["tp"]; // in mm
                weatherData.windSpeed = closestWeather["ws"]; // in km/h
                weatherData.windDirection = closestWeather["wd"].as<String>();
                weatherData.humidity = closestWeather["hu"];
                weatherData.localDateTime = doc["local_datetime"].as<String>();
                */

                tft.fillScreen(ST7735_BLACK);
                tft.println("Dave's Weather Dashboard");
                tft.println("Temperature: " + String(closestWeather["t"]) + "°C");
                tft.println("Weather: " + String(weatherData.weatherDescription));
                tft.println("Precipitation: " + String(weatherData.precipitation) + "mm");
                tft.println("Wind: " + String(weatherData.windSpeed) + "km/h " + weatherData.windDirection);
                tft.println("Humidity: " + String(weatherData.humidity) + "%");
                tft.println("Last updated: " + String(weatherData.localDateTime));
                tft println("Last fetched: " + String(&timeinfo, "%A, %B %d %Y %H:%M:%S"));
            }
        } else {
            Serial.println("Error on HTTPS request");
            Serial.println(httpCode);
            https.end()
        }
        https.end();
    }
    else {
        Serial.println("Error on HTTPS begin");
    }
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}