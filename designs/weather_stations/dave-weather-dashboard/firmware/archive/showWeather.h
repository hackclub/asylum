#ifndef SHOW_WEATHER_H
#define SHOW_WEATHER_H

#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
//#include <WiFi.h>
#include "getWeather.h"
#include "handleNetwork.h"
#include "config.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, MOSI, SCK, TFT_EN);
tft.initR(INITR_BLACKTAB);
tft.fillscreen(ST7735_BLACK);

int showHeader() {
    int16_t x1, y1;
    uint16_t w, h;
    int totalHeight = 0;

    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);

    tft.getTextBounds("Weather Dashboard", 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((tft.width() - w) / 2, 0);
    tft.println("Weather Dashboard");
    totalHeight =+ h + 5;

    tft.getTextBounds("Made by dave9123", 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((tft.width() - w) / 2, totalHeight);
    tft.println("Made by dave9123");
    totalHeight =+ h + 5;

    return totalHeight;
}

void displaySetup() {
    tft.begin();
    tft.setRotation(0);
    showHeader();
}

void connectToWifi() {
    int headerHeight = showHeader()
    tft.setTextSize(1);
    tft.setCursor(0, headerHeight + 5);
    tft.println("Connecting to Wi-Fi...");
    if (!isWiFiConnected()) {
        connectToWiFi();
    }
}

void fetchingWeather() {
    int headerHeight = showHeader();
    tft.setTextSize(1);
    tft.setCursor(0, headerHeight + 5);
    tft.println("Fetching weather data...");
}

void showWeather() {
    int headerHeight = showHeader();
    String weatherData = fetchWeatherData();
    WeatherData weather = parseWeatherData(weatherData);

    int16_t x1, y1;
    uint16_t w, h;

    tft.setTextSize(3)
    tft.getTextBounds(String(weather.temperature) + "°C", 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((tft.width() - w) / 2, 20);
    tft.println(String(weather.temperature) + "°C");

    tft.setTextSize(2);
    tft.getTextBounds(weather.weatherDescription, 0, 0, &x1, &y1, &w, &h);
    tft.setCursor


    tft.setCursor(0, 20);
    tft.setTextSize(3);
    tft.println(String(weather.temperature) + "°C"); //middle text size 3
    //set cursor to middle
    tft.setTextSize(2);
    tft.println("Weather: " + weather.weatherDescription); //middle text size 2
    // text size 1 on left
    tft.println("Precipitation: " + String(weather.precipitation) + "mm");
    tft.println("Wind Speed: " + String(weather.windSpeed) + "km/h");
    tft.println("Wind Direction: " + weather.windDirection);
    tft.println("Humidity: " + String(weather.humidity) + "%");
    tft.println("Local Date Time: " + weather.localDateTime);
}

void showNoWifi() {
    showHeader();
    tft.setTextSize(1);
    tft.setCursor(0, 20);
    tft.println("No Wi-Fi connection.");
    /*tft.println("Please connect to Wi-Fi hotspot and set the SSID and password with the following credentials:");
    tft.println("SSID: " + String(wifi_ssid));
    tft.println("Password: " + String(wifi_password));*/
}