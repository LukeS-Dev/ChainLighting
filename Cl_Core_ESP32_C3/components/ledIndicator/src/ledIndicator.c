/*************************************************************************
 * ledIndicator.c
 * 
 * @author  Luke 
 * @date    
 * 
 * @details 
 * 
 * 
 ************************************************************************/

//========================================================================
// Interfaces 
//------------------------------------------------------------------------
#include "ledIndicator.h"

// Standard modules 
#include <string.h>

// Espressif Modules 
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/freeRTOS.h"
#include "freertos/task.h"

// Project Modules 
#include "config.h"

//========================================================================
// Private Properties
//------------------------------------------------------------------------
static const char *TAG = "Led Indicator";

//========================================================================
// Private functions
//------------------------------------------------------------------------

/*******************************************************************************
 * ledIndicator_init
 * 
 * @brief Initialization code for the new component. 
 * 
 * @returns none
 ******************************************************************************/
void LedIndicator_Init(void)
{
    ESP_LOGI(TAG, "Led Indicator Initialized");
    // This is where initialization code goes.
}

/*******************************************************************************
 * ledController_task
 * 
 * @brief Executes LED tasks.
 * 
 * @returns none
 ******************************************************************************/
void LedIndicator_Task(void *pvParameter)
{
    while (true)
    {
        ESP_LOGI(TAG,"Testing...");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
