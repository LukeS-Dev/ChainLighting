/*******************************************************************************
 * ChainedLighting
 * 
 ******************************************************************************/

/*******************************************************************************
 * Modules 
 ******************************************************************************/
// Standard Modules 
#include <stdio.h>
#include <stdbool.h>

// Espressif Modules 
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/freeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_timer.h"

// Project Modules
#include "config.h"
#include "ledIndicator.h"

/*******************************************************************************
 * Private Properties  
 ******************************************************************************/
static const char *TAG = "Main"; 

extern QueueHandle_t LedIndicator_QueueHandle;


/*******************************************************************************
 * Private Methods 
 ******************************************************************************/
static void app_init(void);
static void nvs_init(void);
static void app_start_tasks(void); 

/*******************************************************************************
 * app_main
 * 
 * @brief Entry Point to the ESP32_IDF
 * 
 * @note ESP-IDF standard modules often use the nvs_flash - this should be one of
 * the first modules to be called in initialization.
 * 
 * @returns none
 ******************************************************************************/
void app_main(void)
{
    /* ESP-IDF components require non-volatile storage - nvs
    init must be called first before application starts.*/
    nvs_init();

    // Initialize application code
    app_init();

    // Start FreeRTOS Tasks.
    app_start_tasks();
}

/*******************************************************************************
 * app_init
 * 
 * @brief initialization code for components.
 * 
 * @returns none
 ******************************************************************************/
static void app_init(void)
{
    ESP_LOGI(TAG, "Application Initialized");

    LedIndicator_Init();
}

/*******************************************************************************
 * app_start_tasks
 * 
 * @brief Starts the task for the 
 * 
 * @returns none
 ******************************************************************************/
static void app_start_tasks(void)
{
    xTaskCreate(&LedIndicator_Task, "LedIndicator_Task", 2048, NULL, 5, NULL);

    uint8_t colourSent = false;
    led_indicator_queue_t colour_test = {
        .command = LED_INDICATOR_CMD_SET_COLOUR,
        .colour = {20,10,20}
    };

    while (true)
    {
        /** 
         * NOTE: This is test code - Demo to set LED indicator Colour From a different Module.
         */
        if (esp_timer_get_time() > 5000 * 1000 && colourSent == false)
        {
            ESP_LOGI(TAG,"Sending Data...");
            xQueueSend(LedIndicator_QueueHandle, &colour_test, 0);
            colourSent = true;
        }
    }
}


/*******************************************************************************
 * nvs_init
 * 
 * @brief initializes non-volatile memory for the ESP_32. 
 * 
 * @note ESP-IDF standard modules often use the nvs_flash - this should be one of
 * the first modules to be called in initialization.
 * 
 * @returns none
 ******************************************************************************/
static void nvs_init(void)
{
    // Initialize Non-volatile flash
    esp_err_t ret = nvs_flash_init();

    // Flash erase - If NVS module is updated or if NVS section is full.
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK( ret );
}