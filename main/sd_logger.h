#ifndef __SD_LOGGER_H_
    #define __SD_LOGGER_H_
    
    #include "esp_err.h"
    #include "sd_types.h"

    esp_err_t generate_log_string(sd_t* sd, event_t* evt);
    esp_err_t write_log(sd_t sd, event_t evt);
    char *encode_event_module(event_modules_e type);
    char *encode_event_event(event_event_e type);
    char *encode_event_status(event_status_e type);
#endif