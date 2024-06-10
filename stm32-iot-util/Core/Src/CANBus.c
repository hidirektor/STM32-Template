/*
 * CANBus.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */


#include "CANBus.h"

HAL_StatusTypeDef CANBus_Init(CANBus_HandleTypeDef *canbus, CAN_HandleTypeDef *hcan) {
    canbus->hcan = hcan;
    return HAL_CAN_Start(canbus->hcan);
}

HAL_StatusTypeDef CANBus_Transmit(CANBus_HandleTypeDef *canbus, uint32_t id, uint8_t *data, uint8_t size) {
    CAN_TxHeaderTypeDef txHeader;
    txHeader.StdId = id;
    txHeader.DLC = size;
    uint32_t txMailbox;
    return HAL_CAN_AddTxMessage(canbus->hcan, &txHeader, data, &txMailbox);
}

HAL_StatusTypeDef CANBus_Receive(CANBus_HandleTypeDef *canbus, uint32_t *id, uint8_t *data, uint8_t *size) {
    CAN_RxHeaderTypeDef rxHeader;
    if (HAL_CAN_GetRxMessage(canbus->hcan, CAN_RX_FIFO0, &rxHeader, data) == HAL_OK) {
        *id = rxHeader.StdId;
        *size = rxHeader.DLC;
        return HAL_OK;
    }
    return HAL_ERROR;
}
