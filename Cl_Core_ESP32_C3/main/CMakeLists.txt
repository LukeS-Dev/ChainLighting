idf_component_register(SRCS "ChainedLighting.c"
                    INCLUDE_DIRS 
                        "."
                        "../config"
                    REQUIRES
                    # ESP32 Components
                        freertos
                        esp_common
                        nvs_flash
                        driver
                    # Project Components
                        ledIndicator
                    )

                    