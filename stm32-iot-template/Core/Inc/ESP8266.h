/*
 * ESP8266.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include "stm32f1xx_hal.h"

typedef struct {
    UART_HandleTypeDef *huart;
} ESP8266_HandleTypeDef;

HAL_StatusTypeDef ESP8266_Init(ESP8266_HandleTypeDef *esp, UART_HandleTypeDef *huart);
HAL_StatusTypeDef ESP8266_SendCommand(ESP8266_HandleTypeDef *esp, const char *cmd);
HAL_StatusTypeDef ESP8266_ReceiveResponse(ESP8266_HandleTypeDef *esp, char *response, uint16_t size);

#endif /* INC_ESP8266_H_ */
