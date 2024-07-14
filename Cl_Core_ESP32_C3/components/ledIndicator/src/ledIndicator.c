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
#include "led_strip.h"
#include "freertos/queue.h"

// Project Modules 
#include "config.h"
#include "ledColours.h"

//========================================================================
// Public Properties
//------------------------------------------------------------------------
QueueHandle_t LedIndicator_QueueHandle;

//========================================================================
// Private Properties
//------------------------------------------------------------------------
static const char *TAG = "Led Indicator";
static led_strip_handle_t led_indicator;
#define LED_INDICATOR_QUEUE_LENGTH 12

//========================================================================
// Private functions
//------------------------------------------------------------------------
static void ledIndicator_setup(void);
static void ledIndicator_startup(void);
static void ledIndicator_setColour(led_colour_t colour);
static void ledIndicator_ProcessCmd(led_indicator_queue_t command);

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
    ledIndicator_setup();

    LedIndicator_QueueHandle = xQueueCreate(LED_INDICATOR_QUEUE_LENGTH, 
                                            sizeof(led_indicator_queue_t));
}

/*******************************************************************************
 * ledIndicator_startup
 * 
 * @brief Flashes the Onboard LED 3 times to indicate Module has been reset.
 * 
 * @returns none
 ******************************************************************************/
void ledIndicator_startup(void)
{
    for (uint8_t count = 0; count < 3; count++)
    {
        ledIndicator_setColour(LED_COLOUR_STARTUP_COLOUR);
        vTaskDelay(120/portTICK_PERIOD_MS);
        ledIndicator_setColour(LED_COLOUR_NO_COLOUR);
        vTaskDelay(120/portTICK_PERIOD_MS);
    }
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
    led_indicator_queue_t ledIndicator_buffer;

    ledIndicator_startup();

    while (true)
    {
        if (LedIndicator_QueueHandle != NULL)
        {
            if (xQueueReceive(LedIndicator_QueueHandle, &ledIndicator_buffer, 0) == pdPASS)
            {
                // If Valid message in the Queue, we process
                ledIndicator_ProcessCmd(ledIndicator_buffer);
            }
        } 
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

/*******************************************************************************
 * ledIndicator_ProcessCmd
 * 
 * @brief Executes Tasks in the LED indicator command Handler. 
 * 
 * @returns none
 ******************************************************************************/
static void ledIndicator_ProcessCmd(led_indicator_queue_t buffer)
{
    ESP_LOGI(TAG, "Recieved Command : %d", buffer.command);

    switch (buffer.command)
    {
    case LED_INDICATOR_CMD_CLEAR:
        ledIndicator_setColour(LED_COLOUR_NO_COLOUR);
        break;
    case LED_INDICATOR_CMD_SET_COLOUR:
        ledIndicator_setColour(buffer.colour);
        break;
    default:
        break;
    }
}


/*******************************************************************************
 * ledIndicator_setColour
 * 
 * @brief Executes LED tasks.
 * 
 * @returns none
 ******************************************************************************/
static void ledIndicator_setColour(led_colour_t colour)
{
    led_strip_set_pixel(led_indicator, 0, colour.red, colour.green, colour.blue);
    led_strip_refresh(led_indicator);
}

/*******************************************************************************
 * ledController_task
 * 
 * @brief Executes LED tasks.
 * 
 * @returns none
 ******************************************************************************/
static void ledIndicator_setup(void)
{ 
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_INDICATOR_PIN,        // The GPIO that connected to the LED strip's data line
        .max_leds = 1,                              // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,   // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,              // LED strip model
        .flags.invert_out = false,                  // whether to invert the output signal (useful when your hardware has a level inverter)
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,             // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000,          // 10MHz
        .flags.with_dma = false,                    // whether to` enable the DMA feature
    }; 

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_indicator));
}