/*
 * LCD.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hidirektor
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_


#include "stm32f1xx_hal.h"

#define _CLEAR      0x01
#define _FIRST_ROW     0x80 // cursor 1. satıra hareket ettir
#define _SECOND_ROW     0xC0 // cursor 2. satıra hareket ettir

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_send_char(char ch);

void lcd_cursor(int state);

void lcd_clear(void);

void lcd_clear_line(int line);

void lcd_delete_char(unsigned char row, unsigned char column);

void lcd_line1(void);

void lcd_line2(void);

void lcd_print(unsigned char row, unsigned char column, char *str);

void lcd_print_char(unsigned char row, unsigned char column, char ch);

void lcd_gotoxy(unsigned char row, unsigned char column);

void lcd_backlight (char state);


#endif /* INC_LCD_H_ */
