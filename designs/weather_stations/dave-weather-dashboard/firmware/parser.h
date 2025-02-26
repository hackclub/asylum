#include <ArduinoJson.h>

// Compute the required capacity based on your JSON
const size_t JSON_BUFFER_SIZE = 4096;  // Adjust based on actual JSON size

struct WeatherData {
    float temperature;
    String weatherDescription;
    float precipitation;
    float windSpeed;
    String windDirection;
    int humidity;
    String localDateTime;
};

WeatherData parseWeatherData(const String& jsonString) {
    WeatherData result;

    // Use static JsonDocument to avoid dynamic memory allocation
    StaticJsonDocument<JSON_BUFFER_SIZE> doc;
    
    // Parse the JSON
    DeserializationError error = deserializeJson(doc, jsonString);
    
    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        return result;
    }

    // Navigate through the complex JSON structure
    JsonArray dataArray = doc["data"][0]["cuaca"][0];
    
    // Take the first time slot as an example
    JsonObject firstTimeSlot = dataArray[0];

    // Extract relevant data
    result.temperature = firstTimeSlot["t"].as<float>();
    result.weatherDescription = firstTimeSlot["weather_desc"].as<String>();
    result.precipitation = firstTimeSlot["tp"].as<float>();
    result.windSpeed = firstTimeSlot["ws"].as<float>();
    result.windDirection = firstTimeSlot["wd"].as<String>();
    result.humidity = firstTimeSlot["hu"].as<int>();
    result.localDateTime = firstTimeSlot["local_datetime"].as<String>();

    return result;
}

void printWeatherData(const WeatherData& data) {
    Serial.println("Weather Information:");
    Serial.printf("Temperature: %.1f°C\n", data.temperature);
    Serial.printf("Weather: %s\n", data.weatherDescription.c_str());
    Serial.printf("Precipitation: %.1f mm\n", data.precipitation);
    Serial.printf("Wind Speed: %.1f km/h\n", data.windSpeed);
    Serial.printf("Wind Direction: %s\n", data.windDirection.c_str());
    Serial.printf("Humidity: %d%%\n", data.humidity);
    Serial.printf("Date/Time: %s\n", data.localDateTime.c_str());
}

// In your main code
void processWeatherData() {
    String jsonPayload = fetchWeatherData();
    
    if (jsonPayload.startsWith("Error")) {
        Serial.println(jsonPayload);
        return;
    }

    WeatherData weather = parseWeatherData(jsonPayload);
    printWeatherData(weather);
}