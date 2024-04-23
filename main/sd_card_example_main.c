#include <string.h>
#include <stdio.h>
#include "sdmmc_cmd.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sd_logger.h"
#include "sd.h"
#include "sd_types.h"

static const char *TAG = "SD";

void app_main(void)
{
esp_err_t ret = ESP_OK;
sdmmc_card_t *card = {0};
char fullpath[200];  
const char *mountpoint = "/sdcard";
char data[200]; 
char filename[] = "/log_"; 

strcpy(fullpath, mountpoint);
strcat(fullpath, filename);

// Inicializar la estructura sd_t con las variables correctas
sd_t sd_handler = {
    .status = ret,
    .card = card,
    .fullpath = fullpath,
    .mountpoint = mountpoint,
    .data = data,
    .filename = filename
};

event_timestamp_t timestamp = {
    .Day = 12,
    .Month = 5,
    .Year = 2024,
    .Hour = 3,
    .Minutes = 45,
    .Seconds = 28
};

event_modules_e module = GPS;

event_event_e event = FIXED;

event_status_e status = ON;

sd_generate_file_name(&sd_handler, timestamp, sd_handler.filename, sizeof(fullpath));
sd_generate_log_path(&sd_handler, sd_handler.mountpoint, sd_handler.filename, sd_handler.fullpath, sizeof(fullpath));
sd_generate_log_data(&sd_handler, timestamp, status, module, event);

ret = sd_init(sd_handler);

ESP_LOGI(TAG, "%s", sd_handler.data);

//ESP_LOGI(TAG, "%s", sd_handler.fullpath);

ret = write_log(&sd_handler);

}
