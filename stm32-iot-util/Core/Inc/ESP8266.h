/*
 * ESP8266.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include "stm32f1xx_hal.h"

typedef enum {
    ESP8266_MODE_STATION = 0,
    ESP8266_MODE_SOFTAP,
    ESP8266_MODE_SOFTAP_STATION
} ESP8266_Mode;

typedef struct {
    UART_HandleTypeDef *huart;
    ESP8266_Mode mode;
} ESP8266_HandleTypeDef;

HAL_StatusTypeDef ESP8266_Init(ESP8266_HandleTypeDef *esp, UART_HandleTypeDef *huart, ESP8266_Mode mode);
HAL_StatusTypeDef ESP8266_SendCommand(ESP8266_HandleTypeDef *esp, const char *cmd);
HAL_StatusTypeDef ESP8266_ReceiveResponse(ESP8266_HandleTypeDef *esp, char *response, uint16_t size);

#endif /* INC_ESP8266_H_ */
