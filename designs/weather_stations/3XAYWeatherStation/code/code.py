#settings.toml config:
#CIRCUITPY_WIFI_SSID = "insert ssid here"
#CIRCUITPY_WIFI_PASSWORD = "insert passsord here"
#WEATHER_URL = "insert URL here"

#Libs to import:
# - adafruit_display_text
# - adafruit_connection_manager
# - adafruit_requests
# - adafruit_st7735r (MAKE SURE TO CHANGE THIS TO NON-R VERSION FOR FINAL BUILD)
# - adafruit_imageload

#Imports
import board
import terminalio #font
import displayio
from adafruit_display_text import label #Allows for text
from adafruit_st7735r import ST7735R #Need to change to ST7735 for acutal firmware, this is for testing on the Sprig
from fourwire import FourWire #For SPI connection
import busio #For SPI connection
from digitalio import DigitalInOut, Direction, Pull #For buttons (encoder will be added later)
import adafruit_requests #For webscraping
import wifi
import os #For wifi passwords, etc
import socketpool
import ssl
import time
import adafruit_imageload #For graphics

# Release any resources currently in use for the displays
displayio.release_displays()

#Setup pins
spi = busio.SPI(clock=board.GP18, MOSI=board.GP19, MISO=board.GP16) #Need to change pins for ESP32
tft_cs = board.GP20 #Need to change pins for ESP32
tft_dc = board.GP22 #Need to change pins for ESP32
display_bus = FourWire(spi, command=tft_dc, chip_select=tft_cs, reset=board.GP26) #Need to change pins for ESP32
display = ST7735R(display_bus, width=160, height=128, rotation=270, bgr=True) #Remove R from library name for final version

# Make the display context
splash = displayio.Group()
display.root_group = splash
color_bitmap = displayio.Bitmap(160, 128, 1)
color_palette = displayio.Palette(1)
color_palette[0] = 0x000000  #Black bg

#Black background
bg_sprite = displayio.TileGrid(color_bitmap, pixel_shader=color_palette, x=0, y=0)
splash.append(bg_sprite)

#Setup button
btn = DigitalInOut(board.GP5) #Change this for the ESP32
btn.direction = Direction.INPUT #Sets the button to be an input
btn.pull = Pull.UP

# Draw a label
text_group = displayio.Group(scale=1, x=4, y=7)
text = label.Label(terminalio.FONT, text="Connecting to wifi...", color=0xFFFFFF)
text_group.append(text)  # Subgroup for text scaling
splash.append(text_group)

#Add images
image, palette = adafruit_imageload.load(
    "imgs/rain.bmp", bitmap=displayio.Bitmap, palette=displayio.Palette)
tile_grid = displayio.TileGrid(image, pixel_shader=palette)
images = displayio.Group(scale=1, x=4, y=75)
images.append(tile_grid)
splash.append(images)

#Weather URL (contains long/lat)
weatherURL = os.getenv('WEATHER_URL')

#Connect to WiFi
wifi.radio.connect(ssid=os.getenv('CIRCUITPY_WIFI_SSID'), password=os.getenv('CIRCUITPY_WIFI_PASSWORD'))

pool = socketpool.SocketPool(wifi.radio)
requests = adafruit_requests.Session(pool, ssl.create_default_context())

text.text = "Wifi connected"
time.sleep(1)
text.text = "Fetching weather data..."


while True: #Keep refreshing
    response = requests.get(weatherURL)
    responseJSON = response.json()
    def getData(inputStr, appendDegree=False):
        if appendDegree:
            return str(responseJSON['current'][inputStr]) + str(responseJSON['current_units']['temperature_2m'])
        else:
            return str(responseJSON['current'][inputStr])
    if(getData("rain") == "0.0"):
        #Add images
        image, palette = adafruit_imageload.load(
            "imgs/sun.bmp", bitmap=displayio.Bitmap, palette=displayio.Palette)
        tile_grid = displayio.TileGrid(image, pixel_shader=palette)
        images = displayio.Group(scale=1, x=4, y=75)
        images.append(tile_grid)
        splash.append(images)
    #MUST BE IN ONE LINE, OTHERWISE IT'LL GET MAD AND THROW AN ERROR IDK WHY
    text.text = getData("temperature_2m", appendDegree=True) +"\nFeels like: " + getData("apparent_temperature", appendDegree=True) + "\nWind Speed: " + getData('wind_speed_10m') + "Mph"
    response.close()
    time.sleep(300)

#Future updates:
# - Add icons
# - Make a dashboard with basic info (temp and precipitation)
# - Make a menu system, "scroll" to see other info (feels like, wind speed, notifications, etc)
# - Add server connection
# - Add menu to show mmWave info
# - Connect to Google Home for auto lights turn on/off
# - CHANGE CASE TO MOUNT HORIZONTALLY, THE USB PORT SHOULD BE FACING UPWARDS
