idf_component_register(
    SRCS "src/ledIndicator.c"
    INCLUDE_DIRS 
        "inc" 
        "src"
        "../../config"
    PRIV_REQUIRES
        driver)