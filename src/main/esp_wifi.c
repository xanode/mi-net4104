#include "esp_wifi.h"
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"


#define ESP_MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#define ESP_MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]

void setup_wifi_ap() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "Benoiïît mdp = strapontin",
            .ssid_len = strlen("Benoiïît mdp = strapontin"),
            .password = "strapontin",
            .threshold.authmode = WIFI_AUTH_WPA2_ENTERPRISE,

        },
    };

    if (strlen("Your Password") == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("AP started with SSID:%s password:%s\n",
           "Benoiïît mdp = strapontin", "strapontin");
}


static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
      char macStr[18];
    sprintf(macStr, ESP_MACSTR, ESP_MAC2STR(event->mac));
        printf("Station %s join, AID=%d\n", macStr, event->aid);    
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        char macStr[18];
        sprintf(macStr, ESP_MACSTR, ESP_MAC2STR(event->mac));
        printf("Station %s join, AID=%d\n", macStr, event->aid);    }
}

void app_main() {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      // NVS partition was truncated and needs to be erased
      // Retry nvs_flash_init
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    vTaskDelay(10000 / portTICK_PERIOD_MS); // Delay for 10000ms (10 seconds)

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_ap();

    setup_wifi_ap();

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID,&event_handler, NULL));
}