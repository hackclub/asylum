#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

const char* ssid = "Souptik";// your network SSID (name)
const char* password = "XXXXXXXXxx";// your password

const char* apiKey = "YourAPIKey";// your OpenWeatherMap API key
const char* city = "Kolkata";
const char* countryCode = "IN";
const char* units = "metric"; // "imperial" for Fahrenheit

String weatherURL = "http://api.openweathermap.org/data/2.5/weather?q=" + String(city) + "," + String(countryCode) + "&appid=" + String(apiKey) + "&units=" + String(units);

#define TFT_CS    10
#define TFT_RST   9
#define TFT_DC    8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  tft.println("WiFi Connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(weatherURL);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      String weather = parseJSON(payload, "weather", "main");
      String description = parseJSON(payload, "weather", "description");
      float temp = parseJSON(payload, "main", "temp").toFloat();

      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(10, 10);
      tft.print("Weather: ");
      tft.println(weather);
      tft.setCursor(10, 30);
      tft.print("Desc: ");
      tft.println(description);
      tft.setCursor(10, 50);
      tft.print("Temp: ");
      tft.print(temp);
      tft.println(" C");
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(6000); 
}

String parseJSON(String json, String object, String key) {
  int startIndex = json.indexOf(object) + object.length() + 3;
  int endIndex = json.indexOf(",", startIndex);
  return json.substring(startIndex, endIndex);
}
