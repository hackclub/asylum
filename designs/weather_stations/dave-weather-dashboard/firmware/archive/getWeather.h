#ifndef GET_WEATHER_H
#define GET_WEATHER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "handleNetwork.h"
#include "config.h"

/*struct weatherData
{
    char* local_datetime; // Timestamp dalam waktu lokal
    int temperature; // Suhu udara (°C)
    //int tcc; // Tutupan awan (%) -> total cloud cover
    int humidity; // Kelembaban udara (%)
    char* weather_desc; // Deskripsi cuaca dalam Inggris
    char* analysis_date; // Tanggal analisis
    char* vs_text; // Jarak pandang (km)
    char* wd; // Arah angin dari
    char* wd_to // Arah angin ke
    char* wd_deg; // Derajat arah angin
    int ws; // Kecepatan angin (km/jam)
    char* image; // URL gambar cuaca
};*/

struct WeatherData
{
    float temperature;
    String weatherDescription;
    float precipitation;
    float windSpeed;
    String windDirection;
    int humidity;
    String localDateTime;
};

String fetchWeatherData()
{
    if (!isWiFiConnected())
    {
        reconnectToWiFi();
    }
    WiFiClientSecure client;
    HTTPClient https;
    client.setInsecure();

    if (https.begin(client, bmkg_base_url + "/publik/prakiraan-cuaca?adm4=" + bmkg_kode_wilayah_tingkat_iv))
    {
        int httpCode = https.GET();
        if (httpCode > 0)
        {
            String payload = https.getString();
            https.end(); // Important: Close connection
            return payload;
        }
        else
        {
            Serial.println("Error on HTTP request");
            Serial.println(https.getString());
            Serial.println(httpCode);
            https.end();
            return "Error on HTTPS request";
        }
    }
    else
    {
        Serial.println("Error on HTTPS request");
        Serial.println(https.getString());
        Serial.println(httpCode);
        return "Error on HTTPS request";
    }

    disconnectFromWiFi();
}

WeatherData getParsedWeatherData()
{
    JsonDocument doc(10240); // Using 10 KB as BMKG API returns around 8 KB of data, annoying tbf
    DeserializationError error = deserializeJson(doc, fetchWeatherData());

    if (error)
    {
        Serial.println("JSON parsing failed: " + error.c_str());
        return "Error occured while parsing JSON";
    }
    elif (!error)
    {
        JsonArray weatherToday = doc["data"][0]["cuaca"][0];
        JsonObject currentWeather = weatherToday[0];

        result.temperature = currentWeather["t"].as<float>();
        result.weatherDescription = currentWeather["weather_desc_en"].as<String>();
        result.precipitation = currentWeather["tp"].as<float>();
        result.windSpeed = currentWeather["ws"].as<float>();
        result.windDirection = currentWeather["wd"].as<String>();
        result.humidity = currentWeather["hu"].as<int>();
        result.localDateTime = currentWeather["local_datetime"].as<String>();

        return result;
    }
}

#endif