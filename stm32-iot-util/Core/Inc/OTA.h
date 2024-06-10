/*
 * OTA.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_OTA_H_
#define INC_OTA_H_

#include "stm32f1xx_hal.h"

void OTA_CheckForUpdate(void);
void OTA_FlashWrite(uint32_t address, uint8_t *data, uint32_t length);


#endif /* INC_OTA_H_ */
