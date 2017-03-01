/*
 * LCD_driver.h
 *
 *  Created on: Feb 27, 2017
 *      Author: eric
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

/* Includes */
#include "i2c_driver.h"

/* Defines */
#define LCD_ADDRESS 0x3C

/* Globals */
static uint8_t data[8];

/* Prototypes */
void LCD_Init(void);

#endif /* LCD_DRIVER_H_ */
