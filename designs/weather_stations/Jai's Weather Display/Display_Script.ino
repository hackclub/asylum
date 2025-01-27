#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ArduinoJson.h>

#define TFT_RST 4
#define TFT_DC 2
#define TFT_CS 15

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Coordinates for Delhi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "https://api.open-meteo.com/v1/forecast?latitude=28.6139&longitude=77.2090&current_weather=true";

void parseWeatherData(String payload);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  tft.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  
  tft.fillScreen(ILI9341_BLACK);
  tft.println("Connected to WiFi");
  Serial.println("Connected to WiFi");
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 120);
  tft.setTextSize(2);
  tft.println("Weather App - Delhi");
  delay(3000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    
    int httpResponseCode = http.GET();
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Received Payload: ");
      Serial.println(payload);
      
      parseWeatherData(payload);
    } else {
      tft.fillScreen(ILI9341_BLACK);
      tft.println("Error fetching data");
      Serial.println("Error fetching data");
    }
    
    http.end();
  } else {
    tft.fillScreen(ILI9341_BLACK);
    tft.println("WiFi disconnected");
    Serial.println("WiFi disconnected");
  }
  
  delay(60000); // Wait for 1 minute before next update
}

void parseWeatherData(String payload) {
  tft.fillScreen(ILI9341_BLACK);
  
  Serial.println("Parsing weather data...");
  
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, payload);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
  JsonObject currentWeather = doc["current_weather"];
  
  float temperature = currentWeather["temperature"];
  float windSpeed = currentWeather["windspeed"];
  String time = currentWeather["time"];
  int windDirection = currentWeather["winddirection"];
  bool isDay = currentWeather["is_day"];
  int weatherCode = currentWeather["weathercode"];
  
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println("Delhi Weather");
  tft.setTextSize(1);
  tft.println("");
  
  tft.print("Time: ");
  tft.println(time);
  
  tft.print("Temperature: ");
  tft.print(temperature);
  tft.println(" C");
  
  tft.print("Wind Speed: ");
  tft.print(windSpeed);
  tft.println(" km/h");
  
  tft.print("Wind Direction: ");
  tft.print(windDirection);
  tft.println("°");
  
  tft.print("Day/Night: ");
  tft.println(isDay ? "Day" : "Night");
  
  tft.print("Weather Code: ");
  tft.println(weatherCode);
}