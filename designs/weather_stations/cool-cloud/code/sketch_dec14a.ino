#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

const char* ssid = "SSID";
const char* password = "PASSWORD";

String api = "https://api.open-meteo.com/v1/forecast?latitude=43.8396194&longitude=-72.714202&current=temperature_2m,precipitation&hourly=is_day&daily=weather_code,temperature_2m_max,temperature_2m_min,precipitation_probability_max,wind_speed_10m_max&temperature_unit=fahrenheit&wind_speed_unit=mph&precipitation_unit=inch&timezone=America%2FNew_York&forecast_days=1";

#define TFT_CS     16
#define TFT_RST    15
#define TFT_DC     4

#define TFT_SCLK 13
#define TFT_MOSI 11  

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB); 
  tft.fillScreen(ST7735_BLACK);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(api.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    JSONVar wetherObj = JSON.parse(payload);
    if (JSON.typeof(wetherObj) == "undefined") {
      Serial.println("Parsing input failed!");
      
    }else{
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(0,0);
      tft.setTextColor(ST7735_WHITE);
      tft.setTextSize(1);
      
      tft.print("Temp: ");
      tft.println(wetherObj["current"]["temperature_2m"]);
      tft.print("Rain chance: ");
      tft.println(wetherObj["current"]["precipitation"]);
    }
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
      Serial.println("WiFi Disconnected");
    }
  delay(5000);
}
