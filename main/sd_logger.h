#ifndef __SD_LOGGER_H_
    #define __SD_LOGGER_H_
    
    #include "esp_err.h"
    #include "sd_types.h"

    void sd_generate_file_name(sd_t *sd, event_timestamp_t timestamp, char* file_name, uint8_t full_pathsize);
    void sd_generate_log_path(sd_t *sd, const char* mountpoint, const char* filename, char* fullpath, uint8_t fullpath_size);
    void sd_generate_log_data(sd_t *sd, event_timestamp_t timestamp, event_status_e status, event_modules_e module, event_event_e event);
    esp_err_t write_log(sd_t* sd);
    char *encode_event_module(event_modules_e type);
    char *encode_event_event(event_event_e type);
    char *encode_event_status(event_status_e type);
    void encode_timestamp(event_timestamp_t timestamp, char *full_timestamp);
#endif