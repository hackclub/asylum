import board, busio, digitalio, displayio, os, wifi
import adafruit_connection_manager, adafruit_requests
from adafruit_st7735 import ST7735

switch = digitalio.DigitalInOut (board.D5)
switch.switch_to_output (value = False, drive_mode = digitalio.DriveMode.PUSH_PULL)

displayio.release_displays ()
spi = busio.spi (clock = board.D6, MOSI = board.D7)
display_bus = displayio.FourWire (spi, command = board.D8, chip_select = board.D20, reset = board.D10)
display = ST7735 (display_bus, width = 160, height = 128)

pool = adafruit_connection_manager.get_radio_socketpool (wifi.radio)
ssl_context = adafruit_connection_manager.get_radio_ssl_context (wifi.radio)
requests = adafruit_requests.Session (pool, ssl_context)

ssid = os.getenv ("SSID")
password = os.getenv ("PASSWORD")
wifi.radio.connect (ssid, password)

def get_weather ():
    pass

def toggle_door ():
    global switch
    switch.value = True
    time.sleep (0.1)
    switch.value = False

def display ():
    pass