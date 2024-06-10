/*
 * CANBus.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_CANBUS_H_
#define INC_CANBUS_H_

#include "stm32f1xx_hal.h"

typedef struct {
    CAN_HandleTypeDef *hcan;
} CANBus_HandleTypeDef;

HAL_StatusTypeDef CANBus_Init(CANBus_HandleTypeDef *canbus, CAN_HandleTypeDef *hcan);
HAL_StatusTypeDef CANBus_Transmit(CANBus_HandleTypeDef *canbus, uint32_t id, uint8_t *data, uint8_t size);
HAL_StatusTypeDef CANBus_Receive(CANBus_HandleTypeDef *canbus, uint32_t *id, uint8_t *data, uint8_t *size);


#endif /* INC_CANBUS_H_ */
