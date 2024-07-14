/*************************************************************************
 * LedIndicator.h 
 * 
 * @author  Luke 
 * @date    
 * 
 * @details 
 * 
 ************************************************************************/

#ifndef LED_INDICATOR_H_
#define LED_INDICATOR_H_

#include <stdint.h>

//========================================================================
// Public Methods
//------------------------------------------------------------------------

void LedIndicator_Init(void);
void LedIndicator_Task(void *pvParameter);

//========================================================================
// Public Types 
//------------------------------------------------------------------------

typedef enum {
    LED_INDICATOR_CMD_CLEAR,
    LED_INDICATOR_CMD_SET_COLOUR,
} led_indicator_cmd; 

typedef struct {
    uint8_t red;    /*!< Red Colour (Hue & Saturation) */
    uint8_t green;  /*!< Green Colour (Hue & Saturation) */
    uint8_t blue;   /*!< Blue Colour (Hue & Saturation) */
} led_colour_t;

typedef struct {
    led_indicator_cmd command;  /*!< Command to send to the LED indicator task*/
    led_colour_t colour;        /*!< RGB Colour variable (optional) */
} led_indicator_queue_t; 


#endif // LED_INDICATOR_H_