#include "esp_wifi.h"
#include <string.h>

void setup_wifi_ap() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "Your SSID",
            .ssid_len = strlen("Your SSID"),
            .password = "Your Password",
            .max_connection = 10,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    if (strlen("Your Password") == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("AP started with SSID:%s password:%s\n",
           "Strapontin", "test");
}