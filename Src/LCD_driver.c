/*
 * LCD_driver.c
 *
 *  Created on: Feb 27, 2017
 *      Author: eric
 *      Driver for SSD1306
 */

#include "LCD_driver.h"

/* Notes
 * All data must be prefixed with a control byte 0x80 - data for GDDRAM, 0x00 command
 */

void LCD_Init()
{
	uint8_t data[] = { 0x00, 0xA5 , 0xAE};

	//Set multiplex ratio 0xA8 - leave as default 0x3F
	i2c_write(data, 2);
}
