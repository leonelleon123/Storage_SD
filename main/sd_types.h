#ifndef __SD_TYPES_H_
    #define __SD_TYPES_H_

    #include "esp_err.h"
    #include <driver/sdmmc_types.h>

    typedef struct
    {
        esp_err_t status;
        sdmmc_card_t *card;
        char *fullpath[200];
        char *mountpoint[10];
        char *data[200];
    }sd_t;

    typedef struct 
    {
        uint8_t Year;
        uint8_t Month;
        uint8_t Day;
        uint8_t Hour;
        uint8_t Minutes;
        uint8_t Seconds;
    } event_timestamp_t;

    typedef enum 
    {
        GPS,
        SENSORS,
        POWER_MANAGEMENT,
        IRRIGATION_MANAGEMENT,
        BLE_PROVISIONER,
        EVENT_LOGGER,
        USER_INTERFACE
    } event_modules_e;

    typedef enum 
    {
        NO_FIX,
        FIXED
    } event_event_e;

    typedef enum
    {
        OK,
        ON,
        OFF
    } event_status_e;

    typedef struct 
    {
        event_timestamp_t timestamo;
        event_modules_e module;
        event_event_e event;
        event_status_e status;
    }event_t;

#endif