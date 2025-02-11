#include <stdio.h>
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_netif_types.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi_default.h"
#include "esp_lcd_panel_io.h"

#include "esp_lcd_io_spi.h"
#include "nvs_flash.h"

#define WIFI_SSID ""
#define WIFI_PASS ""

esp_ip4_addr_t ip_addr;
static TaskHandle_t main_task = NULL;
const unsigned int wifi_connect_idx = 1;

static void on_wifi_event(void *arg, esp_event_base_t base, int32_t id,
                          void *data) {
  if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
    // station online, try to connect
    esp_wifi_connect();
  } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *evt = data;
    ip_addr = evt->ip_info.ip;

    // notify main task
    xTaskNotifyGiveIndexed(main_task, wifi_connect_idx);
  }
}

void app_main(void)
{
  // init flash
  ESP_ERROR_CHECK(nvs_flash_init());

  main_task = xTaskGetCurrentTaskHandle();
  
  // init netifs and wifi
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  esp_netif_create_default_wifi_sta();
  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&config);

  esp_event_handler_instance_t instance_any_id;
  esp_event_handler_instance_t instance_got_ip;
  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                      ESP_EVENT_ANY_ID,
                                                      &on_wifi_event,
                                                      NULL,
                                                      &instance_any_id));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                      IP_EVENT_STA_GOT_IP,
                                                      &on_wifi_event,
                                                      NULL,
                                                      &instance_got_ip));
  wifi_config_t wifi_config = {
    .sta = {
      .ssid = WIFI_SSID,
      .password = WIFI_PASS,
      .threshold.authmode = WIFI_AUTH_WPA2_PSK,
    },
  };
  // start wifi
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());
  // wait for connect
  ulTaskNotifyTakeIndexed(wifi_connect_idx, pdTRUE, portMAX_DELAY);

  // initialize LCD
  esp_lcd_
}
