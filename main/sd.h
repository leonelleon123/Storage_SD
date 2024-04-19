#ifndef __SD_H_
    #define __SD_H_

    #include "sdmmc_cmd.h"
    #include "esp_err.h"

    esp_err_t sd_init(sdmmc_card_t *card, const char* mountpoint);
    void sd_unmounted(sdmmc_card_t *card, const char* mountpoint);
    void sd_generate_log_path(const char* mountpoint, const char* filename, char* fullpath, uint8_t fullpath_size);
#endif