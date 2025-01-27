// Settings file
// #include "settings.h"

// Libs
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include <HTTPClient.h>
#include <WiFi.h>

// Pin mappings for my board. DOUBLE CHECK CAUSE IT MIGHT BE SCUFFED

#define SPI_SCK  7  // Clock Pin (SCK)
#define SPI_MOSI  11  // MOSI Pin (SDI)
#define SPI_MISO -1 // Ignore MISO for now
#define SPI_CS   12  // Chip Select Pin
#define SPI_RST  9  // Reset Pin
#define SPI_DC   16  // Data/Command Pin

#define TFT_LED  5 // control the display on/off

#define NEOPIXEL 18
#define NUM_PIXELS 8

#define SSID "Your SSID"
#define WIFI_PSK "Your Password"

#define CELSIUS_URL                                                                                                    \
    "https://api.open-meteo.com/v1/"                                                                                   \
    "forecast?latitude=43.7001&longitude=-79.4163&current=temperature_2m,relative_humidity_2m,apparent_temperature,"   \
    "is_day,precipitation,rain,showers,snowfall,weather_code,cloud_cover,pressure_msl,surface_pressure,wind_speed_"    \
    "10m,wind_direction_10m,wind_gusts_10ma"
#define FAHRENHEIT_URL                                                                                                 \
    "https://api.open-meteo.com/v1/"                                                                                   \
    "forecast?latitude=43.7001&longitude=-79.4163&current=temperature_2m,relative_humidity_2m,apparent_temperature,"   \
    "is_day,precipitation,rain,showers,snowfall,weather_code,cloud_cover,pressure_msl,surface_pressure,wind_speed_"    \
    "10m,wind_direction_10m,wind_gusts_10m&temperature_unit=fahrenheit&wind_speed_unit=mph&precipitation_unit=inch"

int weatherCode = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
    Serial.begin(115200);

    pinMode(unitSwitch, INPUT);
    pinMode(TFT_LED, OUTPUT);

    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS); // use IOMUX to enable hardware SPI on any pins
    pixels.begin();
    tft.initR(INITR_BLACKTAB);

    // Wifi
    WiFi.begin(SSID, WIFI_PSK);
    Serial.println(F("\nConnecting"));
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(F("."));
        delay(100);
    }
    Serial.println(F("\nConnected to the WiFi network"));

    // initially load, then log the time
    drawWeatherData();
    int prevTime = millis();
    drawWeatherData();
}

void loop()
{
    // loop to update data every minute
    if (millis() - prevTime > 60000)
    {
        drawWeatherData();
        prevTime = millis();
    }
}

void drawWeatherData() // lol might have to use several different libraries for this
{

    JsonDocument doc;

    String data = getWeatherData();

    deserializeJson(doc, data);

    JsonObject jsonData = doc["current"];

    float temperature = jsonData["temperature_2m"];

    //15 minute data
    int uvIndex;
    int humidity;
    int windSpeed;

    // hourly data
    bool isDay; // setting background graphics on/off


    Serial.print("temp: ");
    Serial.println(temperature);
}

String getWeatherData()
{
    HTTPClient http;

    if (unitSwitch)
    {
        http.begin(CELSIUS_URL);
    }
    else
    {
        http.begin(FAHRENHEIT_URL);
    }

    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        Serial.println(payload);
        return payload;
    }
    else
    {
        Serial.println(F("Error on HTTP request"));
    }

    http.end();
}

void weatherLighting(int weatherCode) {
    switch (weatherCode) {
        case 0:
            // clear sky

            break;
    }
}
