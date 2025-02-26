import board
import busio
import digitalio
import displayio
import time
import adafruit_dht
from adafruit_st7735 import ST7735
from rotaryio import IncrementalEncoder
from digitalio import DigitalInOut, Direction, Pull

displayio.release_displays()

spi = busio.SPI(clock=board.GP14, MOSI=board.GP13)  

tft_cs = digitalio.DigitalInOut(board.GP15)  
tft_dc = digitalio.DigitalInOut(board.GP3)   

try:
    display_bus = displayio.FourWire(spi, command=tft_dc, chip_select=tft_cs, reset=board.GP16)  
    display = ST7735(display_bus, width=128, height=160, rotation=180)
except Exception as e:
    print("Error initializing display:", e)
    display = None

dht_pin = board.GP5  
dht_sensor = adafruit_dht.DHT11(dht_pin)

encoder_a = digitalio.DigitalInOut(board.GP4)  
encoder_b = digitalio.DigitalInOut(board.GP0)  
encoder_button = digitalio.DigitalInOut(board.GP2)  

encoder_a.direction = Direction.INPUT
encoder_a.pull = Pull.UP
encoder_b.direction = Direction.INPUT
encoder_b.pull = Pull.UP
encoder_button.direction = Direction.INPUT
encoder_button.pull = Pull.UP

encoder = IncrementalEncoder(board.GP4, board.GP0)

switch = digitalio.DigitalInOut(board.GP15)  
switch.direction = Direction.INPUT
switch.pull = Pull.UP

led = digitalio.DigitalInOut(board.GP16)  
led.direction = Direction.OUTPUT
led.value = False  

if display:
    splash = displayio.Group()
    display.show(splash)

    from adafruit_display_text import label
    import terminalio

    text = "Weather Station"
    text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF, x=10, y=10)
    splash.append(text_area)

    temp_label = label.Label(terminalio.FONT, text="Temp: -- C", color=0xFFFF00, x=10, y=30)
    splash.append(temp_label)

    hum_label = label.Label(terminalio.FONT, text="Humidity: -- %", color=0x00FFFF, x=10, y=50)
    splash.append(hum_label)

    status_label = label.Label(terminalio.FONT, text="Status: OK", color=0x00FF00, x=10, y=70)
    splash.append(status_label)

def read_dht11():
    try:
        temperature = dht_sensor.temperature
        humidity = dht_sensor.humidity
        return temperature, humidity
    except RuntimeError as error:

        print("DHT11 Read Error:", error.args[0])
        return None, None
    except Exception as error:
        dht_sensor.exit()
        raise error

def update_display(temp, hum):
    if display:
        if temp is not None and hum is not None:
            temp_label.text = f"Temp: {temp} C"
            hum_label.text = f"Humidity: {hum} %"
            status_label.color = 0x00FF00  
            status_label.text = "Status: OK"
        else:
            temp_label.text = "Temp: -- C"
            hum_label.text = "Humidity: -- %"
            status_label.color = 0xFF0000  
            status_label.text = "Status: Error"

def toggle_led(state):
    led.value = state

encoder_prev = encoder.position
led_state = False

while True:

    temperature, humidity = read_dht11()
    update_display(temperature, humidity)

    encoder_pos = encoder.position
    if encoder_pos != encoder_prev:
        delta = encoder_pos - encoder_prev
        encoder_prev = encoder_pos
        print(f"Encoder moved by {delta} steps")

        if delta > 0:
            led_state = not led_state
            toggle_led(led_state)
        elif delta < 0:
            led_state = not led_state
            toggle_led(led_state)

    if not encoder_button.value:  
        print("Encoder button pressed")

        led_state = not led_state
        toggle_led(led_state)
        time.sleep(0.2)  

    if not switch.value:  
        print("Switch activated")

        led_state = not led_state
        toggle_led(led_state)
        time.sleep(0.2)  

    if temperature is None or humidity is None:
        status_label.text = "Status: Error"
        toggle_led(True)
        time.sleep(0.5)
        toggle_led(False)
        time.sleep(0.5)
    else:
        toggle_led(led_state)
        time.sleep(1)

    time.sleep(0.1)