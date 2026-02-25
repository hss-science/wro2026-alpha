#include "vl53l5cx_platform.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1; // CubeMXで設定したI2Cハンドル名に合わせてください

/* 指定したアドレスへデータを書き込む関数 */
uint8_t WrMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddr, uint8_t *p_values, uint32_t size) {
    // VL53L5CXは16bitレジスタアドレスを使用します
    if (HAL_I2C_Mem_Write(&hi2c1, p_platform->address, RegisterAddr, I2C_MEMADD_SIZE_16BIT, p_values, size, 1000) != HAL_OK) {
        return 1; // エラー
    }
    return 0; // 成功
}

/* 指定したアドレスからデータを読み出す関数 */
uint8_t RdMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddr, uint8_t *p_values, uint32_t size) {
    if (HAL_I2C_Mem_Read(&hi2c1, p_platform->address, RegisterAddr, I2C_MEMADD_SIZE_16BIT, p_values, size, 1000) != HAL_OK) {
        return 1; // エラー
    }
    return 0; // 成功
}

/* ミリ秒単位のウェイト関数 */
uint8_t WaitMs(VL53L5CX_Platform *p_platform, uint32_t TimeMs) {
    HAL_Delay(TimeMs);
    return 0;
}
