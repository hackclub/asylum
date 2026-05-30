#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ArduinoJson.h>

#define TFT_RST 4
#define TFT_DC 2
#define TFT_CS 15

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

const char* ssid = "Wokwi-GUEST";
const char* password = "";
// Charlotte weather
const char* serverName = "https://api.open-meteo.com/v1/forecast?latitude=35.2271&longitude=-80.8431&current=temperature_2m,relative_humidity_2m&forecast_days=1";

void parseWeatherData(String payload);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.println("wifi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }

  tft.fillScreen(ILI9341_BLACK);
  tft.println("wifi connected");
  Serial.println("wifi connected");

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 120);
  tft.setTextSize(2);
  tft.println("Today's Weather!");
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

  delay(30000); 
}

void parseWeatherData(String payload) {
  tft.fillScreen(ILI9341_BLACK);

  Serial.println("Weather Parse");

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject currentWeather = doc["current"];

  float temperature = currentWeather["temperature_2m"];
  int humidity = currentWeather["relative_humidity_2m"];
  String time = currentWeather["time"];

  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println("Charlotte Weather");
  tft.setTextSize(1);
  tft.println("");

  tft.print("Time: ");
  tft.println(time);

  tft.print("Temperature: ");
  tft.print(temperature);
  tft.println(" °C");

  tft.print("Humidity: ");
  tft.print(humidity);
  tft.println(" %");
}
