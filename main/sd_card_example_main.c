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
    #include <string.h>

// Suponiendo que sd_t y sdmmc_card_t están definidos en algún lugar

esp_err_t ret = ESP_OK;
sdmmc_card_t *card = {0};
char fullpath[200];  // Corregido: Ahora es un array de caracteres
const char *mountpoint = "/sdcard";
char data[200];  // Corregido: Ahora es un array de caracteres
char filename[] = "/log_";  // Corregido: Ahora es una cadena de caracteres

strcpy(fullpath, mountpoint);  // Corregido: Usar strcpy para copiar cadenas

strcat(fullpath, filename);  // Concatenar el nombre del archivo a la ruta

printf("%s", fullpath);
// Inicializar la estructura sd_t con las variables correctas
sd_t sd_handler = {
    .status = ret,
    .card = card,
    .fullpath = fullpath,
    .mountpoint = mountpoint,
    .data = data
};


    //sd_generate_log_path(sd_handler.mountpoint, filename, sd_handler.fullpath, sizeof(sd_handler.fullpath));

    //ESP_LOGI(TAG, "Path: %s", path);
    /*ret = sd_init(card, mountpoint);

    //ret = write_log(file_logger, data);
    if (ret != ESP_OK) 
    {
        return;
    }*/
}
