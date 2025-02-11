import network
import urequests
import time
from machine import Pin, SPI
import dht
from st7789 import ST7789

# Wi-Fi Configuration
SSID = "shuush"
PASSWORD = "shuush"

# OpenWeatherMap API Configuration
API_KEY = "shuush"
CITY = "shuush"
API_URL = f"http://api.openweathermap.org/data/2.5/weather?q={CITY}&appid={API_KEY}&units=metric"

# Initialize SPI and ST7789 screen
spi = SPI(1, baudrate=40000000, polarity=1, phase=1, sck=Pin(10), mosi=Pin(11))
display = ST7789(spi, 240, 135, reset=Pin(3), cs=Pin(9), dc=Pin(8), backlight=Pin(7), rotation=0)

# Clear screen and set font/color
display.init()
display.fill(0)  # Clear screen

# Initialize temperature sensor (DHT11/DHT22)
dht_sensor = dht.DHT11(Pin(5))  # Replace Pin(5) with the correct pin for your sensor

# Function to connect to Wi-Fi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(SSID, PASSWORD)
    print("Connecting to Wi-Fi...")
    
    while not wlan.isconnected():
        time.sleep(1)
        print("Connecting...")
    print("Connected!")
    print("IP Address:", wlan.ifconfig()[0])

# Function to fetch weather data
def get_weather():
    try:
        response = urequests.get(API_URL)
        data = response.json()
        weather = data['weather'][0]['description']
        temperature = data['main']['temp']
        humidity = data['main']['humidity']
        return weather, temperature, humidity
    except Exception as e:
        print("Error fetching weather data:", e)
        return None, None, None

# Display Function
def display_data(room_temp, room_humidity, weather, api_temp, api_humidity):
    display.fill(0)  # Clear screen
    display.text("Room Temp:", 10, 10, color=0xFFFF)  # White text
    display.text(f"{room_temp} C", 10, 30, color=0x07E0)  # Green text
    display.text("Room Humidity:", 10, 50, color=0xFFFF)
    display.text(f"{room_humidity} %", 10, 70, color=0x07E0)

    display.text("Weather:", 10, 90, color=0xFFFF)
    display.text(weather if weather else "N/A", 10, 110, color=0x07E0)
    display.text(f"Outside Temp: {api_temp} C", 10, 130, color=0x07E0)
    display.text(f"Outside Hum: {api_humidity} %", 10, 150, color=0x07E0)

# Main Function
def main():
    connect_wifi()
    while True:
        try:
            # Read room temperature and humidity
            dht_sensor.measure()
            room_temp = dht_sensor.temperature()
            room_humidity = dht_sensor.humidity()

            # Fetch weather data from API
            weather, api_temp, api_humidity = get_weather()

            # Display data
            display_data(room_temp, room_humidity, weather, api_temp, api_humidity)

            # Wait 10 seconds before updating
            time.sleep(10)
        except Exception as e:
            print("Error:", e)
            display.fill(0)
            display.text("Error!", 10, 10, color=0xF800)
            display.text(str(e), 10, 30, color=0xF800)
            time.sleep(5)

# Run the program
if __name__ == "__main__":
    main()
