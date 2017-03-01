/*
 * i2c_driver.c
 *
 *  Created on: Feb 27, 2017
 *      Author: eric
 *      Home rolled I2C driver - mainly for fun/learning
 */

#include "i2c_driver.h"

void i2c_start(uint8_t address, WriteReadMode mode)
{
	//Write the start bit in I2C_CR1
	//NOTE CR1 should not be written when any of START, STOP OR PEC bits are set
	while(0 != (hi2c1.Instance->CR1&0x1300)) { }

	hi2c1.Instance->CR1 |= I2C_CR1_START;

	//The master waits for a read of SR1
	while(0 == (hi2c1.Instance->SR1&I2C_SR1_SB_Msk));

	//Write the address to DR
	hi2c1.Instance->DR = (address << ADDR_SHIFT) | mode;

	//The slave address is sent out in hardware, then the ADDR bit is set
	while(0 == (hi2c1.Instance->SR1&I2C_SR1_ADDR_Msk));

	//Followed by a read of SR2
	while(1 == (hi2c1.Instance->SR2&I2C_SR2_BUSY_Msk));
}

//Function for writing data on the I2C bus
void i2c_write(uint8_t address, CommandDataPkt pktType, uint8_t * data, uint8_t length)
{
	int i;

	i2c_start(address, WRITE_MODE);

	//Ensure that we are in transmission mode
	if(I2C_SR2_TRA == (hi2c1.Instance->SR2&I2C_SR2_TRA_Msk))
	{
		//The first byte sent out, should be the command or data packet
		hi2c1.Instance->DR = pktType;

		//Data is shifted out through DR
		for(i = 0; i < length; i++)
		{
			//Push data onto DR if TxE is set - AKA wait for previous data to be sent
			while(I2C_SR1_TXE != (hi2c1.Instance->SR1&I2C_SR1_TXE_Msk));

			hi2c1.Instance->DR = data[i];

			//Wait for data transmission to end
			//while(0 == (hi2c 1.Instance->SR1&I2C_SR1_TXE_Msk >> I2C_SR1_TXE_Pos));
		}

		i2c_stop();
	}
}

//Generate a stop condition on the bus
void i2c_stop()
{
	//TODO account for sending a stop bit in an error condition?
	//Wait for TxE == 1 and BTF == 1
	while((I2C_SR1_TXE != (hi2c1.Instance->SR1&I2C_SR1_TXE_Msk)) && (I2C_SR1_BTF != (hi2c1.Instance->SR1&I2C_SR1_BTF_Msk))) { }

	//Generate the stop condition
	while(0 != (hi2c1.Instance->CR1&0x1300)) { }

	hi2c1.Instance->CR1 = I2C_CR1_STOP;

	//Read the stop bit from CR1
	//while(I2C_SR1_STOPF != (hi2c1.Instance->SR1&I2C_SR1_STOPF))
}
