#ifndef WEATHER_H
#define WEATHER_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <WiFi.h>

volatile bool lpressed;
volatile bool rpressed;

void rbutton();
void lbutton();

class WeatherStation {
      public:
	WeatherStation();
	~WeatherStation();

	void loop();

      private:
	void connectWifi();
	String readResponse();

	Adafruit_ST7735 tft;
	NetworkClient client;
	time_t now;
};

#endif
