/*
 * i2c_driver.h
 *
 *  Created on: Feb 27, 2017
 *      Author: eric
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

/* Includes */
#include "i2c.h" //Contains the definition of the I2C bus
#include "stm32f103xb.h"

/* Defines */
#define ADDR_SHIFT	1U

/* Enumerations */
typedef enum
{
	WRITE_MODE = 0U,
	READ_MODE
} WriteReadMode;

typedef enum
{
	CMD = 0U,
	DATA
}CommandDataPkt;

/* Function prototypes */
void i2c_start(uint8_t address, WriteReadMode mode);
void i2c_write(uint8_t address, CommandDataPkt pktType, uint8_t * data, uint8_t length);
void i2c_stop(void);

#endif /* I2C_DRIVER_H_ */
