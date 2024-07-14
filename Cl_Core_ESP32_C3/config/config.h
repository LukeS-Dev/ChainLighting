/*******************************************************************************
 * Config 
 * 
 * @brief Configuration Parameters for the 
 * 
 ******************************************************************************/

#include <stdbool.h>

#ifndef CONFIG_H_
    #define CONFIG_H_
    /** 
     *  Configuration for the Board... 
     * 
     *  ESP32-C3-DevKitM-1 v1.6.  
     * 
     *  Offical development board www.espressif.com
     */
    #ifdef CONFIG_IDF_TARGET_ESP32C3
        
        #define LED_INDICATOR_PIN GPIO_NUM_8

    #endif // #ifdef CONFIG_IDF_TARGET_ESP32C3

#endif // #ifndef CONFIG_H_