#include <string.h>
#include <stdio.h>
#include "sd_logger.h"
#include "sd_types.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "SD";

esp_err_t generate_log_string(sd_t* sd, event_t* evt)
{
    //guardar string generada en sd.data
    return ESP_OK;
}
// Function to write in a file the logger data
esp_err_t write_log(sd_t sd, event_t evt)
{
    if (sd.fullpath != NULL) {
    ESP_LOGI(TAG, "Opening file %.s", sd.fullpath);
    } else {
        ESP_LOGE(TAG, "Error: sd.fullpath is NULL");
    }
    FILE *f = fopen(sd.fullpath, "w"); //Opening file in write mode
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    fgets(sd.data, sizeof(sd.data), f);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return ESP_OK;
}

// Functions to encode events
char *encode_event_module(event_modules_e type)
{
    switch(type)
    {
        case GPS:
            return "GPS";
        case SENSORS:
            return "SENSORS";
        case POWER_MANAGEMENT:
            return "POWER MANAGEMENT";
        case IRRIGATION_MANAGEMENT:
            return "IRRIGATION MANAGEMENT";
        case BLE_PROVISIONER:
            return "BLE PROVISIONER";
        case EVENT_LOGGER:
            return "EVENT LOGGER";
        case USER_INTERFACE:
            return "USER INTERFACE";
        default:
            return "Undefined type";

    }
}

char *encode_event_event(event_event_e type)
{
    switch(type)
    {
        case NO_FIX:
            return "NO FIX";
        case FIXED:
            return "FIXED";
        default:
            return "Undefined type";
    }
}

char *encode_event_status(event_status_e type)
{
    switch(type)
    {
        case OK:
            return "OK";
        case ON:
            return "ON";
        case OFF:
            return "OFF";
        default:
            return "Undefined type";
    }
}