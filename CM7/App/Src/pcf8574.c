#include "pcf8574.h"

#define PCF8574_ADDR (0x20 << 1)

HAL_StatusTypeDef PCF8574_Write(uint8_t data) {
    extern I2C_HandleTypeDef hi2c4;
    uint8_t inverted = ~data;
    return HAL_I2C_Master_Transmit(&hi2c4, PCF8574_ADDR, &inverted, 1, 100);
}
