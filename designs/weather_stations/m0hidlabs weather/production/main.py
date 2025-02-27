import machine
from machine import Pin, SPI
import dht
import st7735
import time
# yeah i have no idea if this will work but hopefully it doesnt explode
dht11 = dht.DHT11(Pin(3))

spi = SPI(1, baudrate=20000000, polarity=0, phase=0)
display = st7735.ST7735(
    spi,
    dc=Pin(8),
    cs=Pin(10),
)

def read_weather():
    try:
        dht11.measure()
        temperature = dht11.temperature()
        humidity = dht11.humidity()
        return temperature, humidity
    except:
        return None, None

def update_display(temp, humidity):
    display.fill(st7735.BLACK)
    display.text("Temperature:", 10, 10, st7735.WHITE)
    display.text(f"{temp}°C", 10, 30, st7735.WHITE)
    display.text("Humidity:", 10, 50, st7735.WHITE)
    display.text(f"{humidity}%", 10, 70, st7735.WHITE)

while True:
    temp, humidity = read_weather()
    if temp is not None:
        update_display(temp, humidity)
    time.sleep(2)
