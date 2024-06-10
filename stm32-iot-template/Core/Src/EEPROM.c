/*
 * EEPROM.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */


#include "EEPROM.h"

HAL_StatusTypeDef EEPROM_Init(EEPROM_HandleTypeDef *eeprom, I2C_HandleTypeDef *hi2c, uint16_t devAddress) {
    eeprom->hi2c = hi2c;
    eeprom->devAddress = devAddress;
    return HAL_OK;
}

HAL_StatusTypeDef EEPROM_Write(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size) {
    return HAL_I2C_Mem_Write(eeprom->hi2c, eeprom->devAddress, memAddress, I2C_MEMADD_SIZE_16BIT, data, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef EEPROM_Read(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size) {
    return HAL_I2C_Mem_Read(eeprom->hi2c, eeprom->devAddress, memAddress, I2C_MEMADD_SIZE_16BIT, data, size, HAL_MAX_DELAY);
}
