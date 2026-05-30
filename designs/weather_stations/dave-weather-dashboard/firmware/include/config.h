#ifndef CONFIG_H
#define CONFIG_H

#define NTP_SERVER "time.windows.com" // NTP server
#define GMT_OFFSET_SEC 7 * 60 * 60 // Timezone offset in seconds
#define DAYLIGHT_OFFSET_SEC 0 // Daylight offset in seconds


/*
#define HOTSPOT_SSID "change-with-your-hotspot-ssid" // Hotspot SSID if it can't connect to Wi-Fi
#define HOTSPOT_PASSWORD "change-with-your-hotspot-password" // Hotspot password if it can't connect to Wi-Fi
*/
#define WIFI_SSID  "change-with-your-wifi-ssid" // Your Wi-Fi SSID
#define WIFI_PASSWORD "change-with-your-wifi-password" // Your Wi-Fi password
#define RECONNECT_ATTEMPTS 3 // Wi-Fi max reconnect attempts
#define RECONNECT_INTERVAL 10000 // Wi-Fi reconnect interval in milliseconds
#define WIFI_HOSTNAME "dave-weather-dashboard" // WiFi hostname for this device

// API config
#define BMKG_API_BASE "https://api.bmkg.go.id" // BMKG API base URL
#define BMKG_KODE_WILAYAH_TINGKAT_IV "32.01.02.2003" // BMKG Kode Wilayah Tingkat IV https://kodewilayah.id/

#define REFRESH_INTERVAL 30 * 60 * 1000 // Refresh interval in milliseconds
#define BOUNCE_INTERVAL 50 // Bounce interval in milliseconds

// Pins configuration
#define TFT_CS 20
#define TFT_DC 21
#define TFT_EN 28
#define MOSI 27
#define MISO 26
#define SCK 19
#define SD_CS 14
#define REFRESH_BUTTON 5

#endif // CONFIG_H