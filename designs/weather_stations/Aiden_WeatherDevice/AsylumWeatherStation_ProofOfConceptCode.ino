#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <DHT11.h>
#include <HTTPClient.h>
#include <WiFi.h>

#ifdef TFT_MOSI
    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#endif

DHT11 dht11(2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    int temperature = dht11.readTemperature();
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println("C");
        tft.print(temperature);
    } else {
        Serial.println(DHT11::getErrorString(temperature));
    }
}
