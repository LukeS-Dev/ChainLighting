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

typedef struct {
    uint8_t red; 
    uint8_t green; 
    uint8_t blue;
} led_colour_t;






#endif // LED_INDICATOR_H_