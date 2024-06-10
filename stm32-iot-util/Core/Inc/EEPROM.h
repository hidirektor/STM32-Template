/*
 * EEPROM.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stm32f1xx_hal.h"

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint16_t devAddress;
} EEPROM_HandleTypeDef;

HAL_StatusTypeDef EEPROM_Init(EEPROM_HandleTypeDef *eeprom, I2C_HandleTypeDef *hi2c, uint16_t devAddress);
HAL_StatusTypeDef EEPROM_Write(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size);
HAL_StatusTypeDef EEPROM_Read(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size);
HAL_StatusTypeDef EEPROM_SaveData(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size);
HAL_StatusTypeDef EEPROM_FillData(EEPROM_HandleTypeDef *eeprom, uint16_t memAddress, uint8_t *data, uint16_t size);

#endif /* INC_EEPROM_H_ */
