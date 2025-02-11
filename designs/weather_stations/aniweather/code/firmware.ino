#include <WiFi.h>
#include <SPI.h>

#include "weather.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/api-reference/peripherals/spi_master.html
WeatherStation* station;

void setup() {
	Serial.begin(9600);
	Serial.println("Aniweather booting up...");
	
	station = new WeatherStation();
}

void loop() {
	station->loop();
}
