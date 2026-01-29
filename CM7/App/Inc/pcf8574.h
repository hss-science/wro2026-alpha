#ifndef USER_PCF8574_H // もし UNIQUE_NAME_H が定義されていなかったら
#define USER_PCF8574_H // UNIQUE_NAME_H を定義する

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "i2c.h"

HAL_StatusTypeDef PCF8574_Write(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif // UNIQUE_NAME_H の終わり
