/*
 * ESP8266.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#include "ESP8266.h"

#include <string.h>

HAL_StatusTypeDef ESP8266_Init(ESP8266_HandleTypeDef *esp, UART_HandleTypeDef *huart, ESP8266_Mode mode) {
    esp->huart = huart;
    esp->mode = mode;

    char cmd[20];
    snprintf(cmd, sizeof(cmd), "AT+CWMODE=%d\r\n", mode);
    return ESP8266_SendCommand(esp, cmd);
}

HAL_StatusTypeDef ESP8266_SendCommand(ESP8266_HandleTypeDef *esp, const char *cmd) {
    return HAL_UART_Transmit(esp->huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
}

HAL_StatusTypeDef ESP8266_ReceiveResponse(ESP8266_HandleTypeDef *esp, char *response, uint16_t size) {
    return HAL_UART_Receive(esp->huart, (uint8_t *)response, size, HAL_MAX_DELAY);
}
