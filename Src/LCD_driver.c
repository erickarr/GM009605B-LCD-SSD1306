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
	//Set multiplex ratio 0xA8 - default 0x3F
	data[0] = 0x00;
	data[1] = 0xA8;
	data[2] = 0x3F;

	//i2c_write(LCD_ADDRESS, CMD, data, 2);
	HAL_I2C_Master_Transmit(&hi2c1, 0x78, data, 3, 100);

	//Set display offset 0xD3 - 0x00
	data[0] = 0x00;
	data[1] = 0xD3;
	data[2] = 0x00;

	//i2c_write(LCD_ADDRESS, CMD, data, 2);
	HAL_I2C_Master_Transmit(&hi2c1, 0x78, data, 3, 100);

	//Set display start line 0x40
	data[0] = 0x00;
	data[1] = 0x40;
	data[2] = 0x00;

	//i2c_write(LCD_ADDRESS, CMD, data, 2);
	HAL_I2C_Master_Transmit(&hi2c1, 0x78, data, 3, 100);


	//Set segment re-map 0xA0/0xA1

	//Set COM output scan direction 0xC0/0xC8

	//Set COM pins hardware configuration 0xDA - 0x02

	//Set constrast control 0x81h - 0x7F

	//Disable entire display on 0xA4

	//Set normal display 0xA6

	//Set OSC frequency 0xD5 - 0x80

	//Enable charge pump regulator 0x8D - 0x14
	//Turn display on 0xAF
	data[0] = 0x00;
	data[1] = 0x8D;
	data[2] = 0x14;
	data[3] = 0xAF;

	HAL_I2C_Master_Transmit(&hi2c1, 0x78, data, 4, 100);

	//Write some garbage to the GDDRAM
	data[0] = 0x70;
	data[1] = 0xFF;
	data[2] = 0xFF;
	data[3] = 0xFF;
	data[4] = 0xFF;
	data[5] = 0xFF;
	data[6] = 0xFF;
	data[7] = 0xFF;

	HAL_I2C_Master_Transmit(&hi2c1, 0x78, data, 2, 100);

}
