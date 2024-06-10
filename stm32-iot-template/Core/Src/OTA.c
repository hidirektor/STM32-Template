/*
 * OTA.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#include "OTA.h"
#include "EEPROM.h"
#include "ESP8266.h"
#include "globals.h"
#include "LCD.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern EEPROM_HandleTypeDef heeprom;
extern ESP8266_HandleTypeDef hesp8266;

#define UPDATE_START_ADDRESS 0x08008000
#define FLASH_SECTOR_SIZE    2048

void OTA_FlashWrite(uint32_t address, uint8_t *data, uint32_t length) {
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < length; i += 4) {
        uint32_t word = *((uint32_t *)(data + i));
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address + i, word);
    }

    HAL_FLASH_Lock();
}

void OTA_CheckForUpdate(void) {
    char response[256];
    char firmwareData[FLASH_SECTOR_SIZE];
    uint32_t address = UPDATE_START_ADDRESS;
    char url[256];
    char command[256];

    // Construct URL with currentVersion parameter
    snprintf(url, sizeof(url), "%s?currentVersion=%s", checkVersionURL, currentVersion);

    // Construct the HTTP GET command
    snprintf(command, sizeof(command), "AT+HTTPGET=\"%s\"\r\n", url);

    // Send request to check for new version
    ESP8266_SendCommand(&hesp8266, command);
    ESP8266_ReceiveResponse(&hesp8266, response, sizeof(response));

    if (strstr(response, "200 OK")) {
        // Parse new version from response
        // For example, parse actual version from response
        strcpy(newVersion, "1.1.0");
        EEPROM_SaveData(&heeprom, 0x0000, (uint8_t *)newVersion, strlen(newVersion) + 1);

        // Display update message on LCD
        lcd_clear();
        lcd_print(1, 1, "GUNCELLEME BULUNDU");
        lcd_print(2, 1, "INDIRILIYOR...");

        // Construct the command to download new version
        snprintf(command, sizeof(command), "AT+HTTPGET=\"%s\"\r\n", downloadNewVersionURL);

        // Download new version
        ESP8266_SendCommand(&hesp8266, command);

        while (1) {
            int received = ESP8266_ReceiveResponse(&hesp8266, firmwareData, sizeof(firmwareData));
            if (received <= 0) break;

            // Write to flash
            OTA_FlashWrite(address, (uint8_t *)firmwareData, received);
            address += received;

            // Update progress on LCD
            lcd_clear_line(2);
            lcd_print(2, 1, "YUKLENIYOR...");
        }

        // Verify and finalize the update
        EEPROM_SaveData(&heeprom, 0x0000, (uint8_t *)newVersion, strlen(newVersion) + 1);

        // Display completion message on LCD
        lcd_clear_line(2);
        lcd_print(2, 1, "GUNCELLEME TAMAMLANDI");
    }
}
