/*
 * LCD.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */


#include "LCD.h"

extern I2C_HandleTypeDef hi2c1;

#define SLAVE_ADDRESS_LCD 0x4E
char LCD_BACKLIGHT = 0x00;

void lcd_send_cmd (char cmd) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0

	while(HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	if(LCD_BACKLIGHT == 0) {
		for(uint8_t i = 0; i <= 3; i++) {
			data_t[i] &= ~(1UL << 3);
		}
	} else {
		for(uint8_t i = 0; i <= 3; i++) {
			data_t[i] |= 1UL << 3;
		}
	}
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	//HAL_Delay(5);
}

void lcd_send_data (char data) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0

	while(HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	if(LCD_BACKLIGHT == 0) {
		for(uint8_t i = 0; i <= 3; i++) {
			data_t[i] &= ~(1UL << 3);
		}
	} else {
		for(uint8_t i = 0; i <= 3; i++) {
			data_t[i] |= 1UL << 3;
		}
	}

	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	//HAL_Delay(5);
}

void lcd_send_string (char *str) {
	while (*str) {
		lcd_send_data (*str++);
	}
}

void lcd_send_char(char ch) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (ch & 0xf0);
    data_l = ((ch << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  //en=1, rs=1
    data_t[1] = data_u | 0x09;  //en=0, rs=1
    data_t[2] = data_l | 0x0D;  //en=1, rs=1
    data_t[3] = data_l | 0x09;  //en=0, rs=1

    while(HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

    if(LCD_BACKLIGHT == 0) {
        for(uint8_t i = 0; i <= 3; i++) {
            data_t[i] &= ~(1UL << 3);
        }
    } else {
        for(uint8_t i = 0; i <= 3; i++) {
            data_t[i] |= 1UL << 3;
        }
    }

    HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x02);
	lcd_send_cmd (0x28);
	lcd_send_cmd (0x0c);
	lcd_send_cmd (0x80);
	lcd_backlight(1);
}

void lcd_gotoxy(unsigned char row, unsigned char column) {
	if(row == 1) {
		lcd_send_cmd(0x80 + (column - 1));
	} else if(row == 2) {
		lcd_send_cmd(0xC0 + (column - 1));
	}
}

void lcd_print(unsigned char row, unsigned char column, char *str) {
	lcd_gotoxy(row, column);
	lcd_send_string(str);
}

void lcd_print_char(unsigned char row, unsigned char column, char ch) {
    lcd_gotoxy(row, column);
    lcd_send_char(ch);
}

void lcd_clear(void) {
	lcd_send_cmd(_CLEAR);
    HAL_Delay(2);
}

void lcd_clear_line(int line) {
	if(line == 1) {
		lcd_line1();
		lcd_send_cmd(0x01);
	}  else {
		lcd_line2();
		lcd_send_cmd(0x01);
	}
}

void lcd_delete_char(unsigned char row, unsigned char column) {
    lcd_gotoxy(row, column);

    lcd_send_char(' ');
}

void lcd_line1(void) {
	lcd_send_cmd(0x80);
}

void lcd_line2(void) {
	lcd_send_cmd(0xC0);
}

void lcd_backlight(char state) {
	LCD_BACKLIGHT = state;
	lcd_send_cmd(0x00);
}

void lcd_cursor(int state) {
	if (state == 1) {
		lcd_send_cmd(0x0E);
		lcd_send_cmd(0x0F);
	} else {
		lcd_send_cmd(0x0C);
	}
}
