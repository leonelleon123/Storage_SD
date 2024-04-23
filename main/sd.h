#ifndef __SD_H_
    #define __SD_H_

    #include "esp_err.h"
    #include "sd_types.h"

    esp_err_t sd_init(sd_t sd_handler);
    //esp_err_t sd_unmounted(sd_t sd_handler);
#endif