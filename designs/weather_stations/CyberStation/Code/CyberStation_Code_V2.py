import time
import network
import urequests
from machine import Pin, SPI
import st7735

# Wi-Fi credentials
WIFI_SSID = 'YourWiFiSSID'
WIFI_PASSWORD = 'YourWiFiPassword'

# OpenWeatherMap API setup
API_KEY = 'YOUR_API_KEY_HERE'
CITY = 'YOUR_CITY_HERE'
URL = f'YOUR_API_URL_HERE'

# SPI and display setup
spi = SPI(1, baudrate=20000000, sck=Pin(6), mosi=Pin(7), miso=None)
display = st7735.ST7735(spi, cs=Pin(10), dc=Pin(4), rst=Pin(2))

# Button setup
button1 = Pin(1, Pin.IN, Pin.PULL_UP)
button2 = Pin(8, Pin.IN, Pin.PULL_UP)
button3 = Pin(9, Pin.IN, Pin.PULL_UP)

def connect_to_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(WIFI_SSID, WIFI_PASSWORD)

    for _ in range(10):
        if wlan.isconnected():
            return True
        time.sleep(1)

    return False

def draw_cloud_and_sun():
    # Sun (yellow circle)
    display.fill_circle(100, 40, 20, st7735.color565(255, 255, 0))  # Sun in Yellow
    # Cloud (White circles)
    display.fill_circle(80, 40, 15, st7735.color565(255, 255, 255))  # Cloud part 1
    display.fill_circle(120, 40, 15, st7735.color565(255, 255, 255))  # Cloud part 2
    display.fill_circle(90, 30, 15, st7735.color565(255, 255, 255))  # Cloud part 3
    display.fill_circle(110, 30, 15, st7735.color565(255, 255, 255))  # Cloud part 4

def show_welcome_screen():
    display.fill(st7735.color565(0, 0, 0))  # Clear screen
    draw_cloud_and_sun()
    display.text('Hello World!', 10, 10, st7735.color565(255, 255, 255))
    time.sleep(5)

def show_error_screen(message):
    display.fill(st7735.color565(0, 0, 0))
    display.text(message, 10, 30, st7735.color565(255, 0, 0))
    display.text('Go Touch Grass', 10, 50, st7735.color565(255, 255, 255))

def fetch_weather():
    try:
        response = urequests.get(URL)
        data = response.json()
        response.close()

        temperature = data['main']['temp']
        description = data['weather'][0]['description']

        return temperature, description
    except Exception as e:
        return None, None

def show_weather_screen(temperature, description):
    display.fill(st7735.color565(0, 0, 0))  # Clear the screen
    display.text('CyberStation Weather', 10, 10, st7735.color565(255, 255, 255))
    display.text(f'Temperature: {temperature}F', 10, 30, st7735.color565(255, 255, 255))
    display.text(f'Condition: {description}', 10, 50, st7735.color565(255, 255, 255))

def periodic_weather_update():
    last_update = time.time()
    while True:
        current_time = time.time()
        if current_time - last_update >= 600:  # 10 minutes
            temperature, description = fetch_weather()
            if temperature is not None:
                show_weather_screen(temperature, description)
            else:
                show_error_screen('Error Fetching Weather Data')
            last_update = current_time
        time.sleep(1)

def main():
    if not connect_to_wifi():
        show_error_screen('Error Connecting to Network')
        return

    show_welcome_screen()

    last_weather_update = time.time()

    while True:
        if not button1.value():
            temperature, description = fetch_weather()
            if temperature is not None:
                show_weather_screen(temperature, description)
            else:
                show_error_screen('Error Fetching Weather Data')

        if not button2.value():
            if not connect_to_wifi():
                show_error_screen('Error Connecting to Network')

        # Periodic update
        current_time = time.time()
        if current_time - last_weather_update >= 600:  # 10 minutes
            temperature, description = fetch_weather()
            if temperature is not None:
                show_weather_screen(temperature, description)
            else:
                show_error_screen('Error Fetching Weather Data')
            last_weather_update = current_time

        time.sleep(0.1)

if __name__ == '__main__':
    main()
