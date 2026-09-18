# This forces the ESPHome generator to append the dependency to the main src requirements list
if(NOT "libjpeg-turbo-esp32" IN_LIST ESPHOME_REGISTER_REQUIRES)
    list(APPEND ESPHOME_REGISTER_REQUIRES "libjpeg-turbo-esp32")
endif()
