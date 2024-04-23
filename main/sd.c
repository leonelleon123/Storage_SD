#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "sd.h"
#include "sd_types.h"
#include "sdmmc_cmd.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/spi_master.h"
#include "../../../../esp/v5.2.1/esp-idf/components/driver/spi/include/driver/spi_common.h"
#include "../../../../esp/v5.2.1/esp-idf/components/driver/spi/include/driver/sdspi_host.h"

// Pin assignments 
#define PIN_NUM_MISO  12
#define PIN_NUM_MOSI  11
#define PIN_NUM_CLK   13
#define PIN_NUM_CS    10 

static const char *TAG = "SD";

esp_err_t sd_init(sd_t sd_handler)
{
    sdmmc_card_t *card = sd_handler.card;
    const char* mountpoint = sd_handler.mountpoint;
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    ESP_LOGI(TAG, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    ESP_LOGI(TAG, "Using SPI peripheral");

    // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
    // For setting a specific frequency, use host.max_freq_khz (range 400kHz - 20MHz for SDSPI)
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    esp_err_t ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mountpoint, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return ret;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    return ret;
}

/*esp_err_t sd_unmounted(sd_t sd_handler)
{
    sdmmc_card_t *card = sd_handler.card;
    const char* mountpoint = sd_handler.mountpoint;
    // Format FATFS
    #ifdef CONFIG_EXAMPLE_FORMAT_SD_CARD
        esp_err_t ret = esp_vfs_fat_sdcard_format("/sdcard", card);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to format FATFS (%s)", esp_err_to_name(ret));
            return ret;
        }
    #endif
        // All done, unmount partition and disable SPI peripheral
        esp_err_t ret = ESP_OK;
        esp_vfs_fat_sdcard_unmount(mountpoint, card);
        ESP_LOGI(TAG, "Card unmounted");
}*/