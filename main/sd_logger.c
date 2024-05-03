#include <string.h>
#include <stdio.h>
#include "sd_logger.h"
#include "sd_types.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "SD";

void sd_generate_file_name(sd_t *sd, event_timestamp_t timestamp, char* file_name, uint8_t full_pathsize)
{
    snprintf(sd->filename, full_pathsize, "%s%d-%d-%d", file_name, timestamp.Day, timestamp.Month, timestamp.Year);    
}

void sd_generate_log_path(sd_t *sd, const char* mountpoint, const char* filename, char* fullpath, uint8_t fullpath_size)
{
    snprintf(sd->fullpath, fullpath_size, "%s%s.txt", mountpoint, filename);
}

void sd_generate_log_data(sd_t *sd, event_timestamp_t timestamp, event_status_e status, event_modules_e module, event_event_e event)
{
    char final_timestamp[30];
    encode_timestamp(timestamp, final_timestamp);
    char final_module[20]; 
    strcpy(final_module, encode_event_module(module));
    char final_event[20];
    strcpy(final_event, encode_event_event(event));
    char final_status[20];
    strcpy(final_status, encode_event_status(status));
    sprintf(sd->data,"%s; MOD-%s; Evt-%s; Sta-%s;\n", final_timestamp, final_module, final_event, final_status);
}

// Function to write in a file the logger data
esp_err_t write_log(sd_t *sd)
{
    FILE *f = fopen(sd->fullpath, "w"); //Opening file in write mode
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    fprintf(f, sd->data);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return ESP_OK;
}

// Functions to encode events
void encode_timestamp(event_timestamp_t timestamp, char *full_timestamp)
{
    sprintf(full_timestamp,"[%d/%d/%d - %d:%d:%d]",timestamp.Day, timestamp.Month, timestamp.Year, timestamp.Hour, timestamp.Minutes, timestamp.Seconds);
}

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