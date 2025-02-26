# Weather Dashboard Firmware

This weather dashboard is using data provided from [BMKG](https://data.bmkg.go.id/prakiraan-cuaca/). Please set [config.h](./include/config.h) up before uploading the sketch to your board.

## TODO
<ol type="1">
    <li>Run a Wi-Fi hotspot if Wi-Fi retry limit has reached</li>
    <li>Store saved Wi-Fi credentials on SD card</li>
    <li>Show weather fetched to the TFT display</li>
    <li>Add FS handler for WiFi credential handler through external storage plugged through the TFT display using FS or use SPIFFS (not recommended)</li>
    <li>Make an app to communicate with the board, may not be needed if thing above is made</li>
</ol>