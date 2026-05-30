#ifndef CONFIG_H
#define CONFIG_H

#define hotspot_ssid "change-with-your-hotspot-ssid"
#define hotspot_password "change-with-your-hotspot-password"
#define wifi_ssid  "change-with-your-wifi-ssid"
#define wifi_password "change-with-your-wifi-password"
#define reconnect_attempts 3
#define reconnect_interval 5000
#define hostname "weather-station"
#define BMKG_API_BASE "https://api.bmkg.go.id"
#define BMKG_KODE_WILAYAH_TINGKAT_IV "change-with-kode-wilayah"
#define REFRESH_INTERVAL 30 * 60 * 1000
#define BOUNCE_INTERVAL 50

// Pins configuration
#define TFT_CS 20
#define TFT_DC 21
#define TFT_EN 28
#define MOSI 27
#define MISO 15
#define SCK 19
#define SD_CS 14
#define REFRESH_BUTTON 5

#endif