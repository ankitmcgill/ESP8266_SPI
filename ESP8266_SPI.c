/*************************************************
* ESP8266 HARDWARE SPI (HSPI) LIBRARY
* SUPPORTS ONLY SPI MASTER MODE
* (WRITING SPI DATA TO SLAVE)
* NO READING / MISO SUPPORT
*
* OCTOBER 26 2016
* ANKIT BHATNAGAR
* ANKIT.BHATNAGARINDIA@GMAIL.COM
* ***********************************************/


#include "ESP8266_SPI.h"

void ESP8266_SPI_init_pins(void)
{

	//INITIALIZE THE GPIO PINS USED FOR SPI
	//GPIO13 - MTCK - HSPI MOSI
	//GPIO14 - MTMS - HSPI CLK
	//GPIO15 - MTDO - HSPI CS

	WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105); //Set bit 9 if 80MHz sysclock required
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);
}

void ESP8266_SPI_set_params(uint8_t addr_len, uint8_t data_len)
{
	//SET SPI1 (HSPI) PARAMETERS
	//CPOL = CPHA = 0
	//MSB FIRST
	//CONFIGURABLE COMMAND , ADDRESS & DATA BIT LENGTH

	//disable MOSI, MISO, ADDR, COMMAND, DUMMY in case previously set.
	CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_MOSI | SPI_USR_MISO | SPI_USR_COMMAND | SPI_USR_ADDR | SPI_USR_DUMMY |SPI_FLASH_MODE);

	//SET GENERAL BEHAVIOR AND DATA FORMAT AND CS LINE BEHAVIOR
	SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_ADDR | SPI_USR_MOSI | SPI_CS_SETUP | SPI_CS_HOLD);


	//SET CPOL=0 & CPHA=0
	CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_IDLE_EDGE);
	CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_CK_OUT_EDGE);

	//SET SPI CLOCK
	uint16_t prediv = 9;
	uint8_t cntdiv = 3;
	WRITE_PERI_REG(SPI_CLOCK(HSPI), (((prediv-1)&SPI_CLKDIV_PRE)<<SPI_CLKDIV_PRE_S)|
									(((cntdiv-1)&SPI_CLKCNT_N)<<SPI_CLKCNT_N_S)|
									(((cntdiv>>1)&SPI_CLKCNT_H)<<SPI_CLKCNT_H_S)|
									((0&SPI_CLKCNT_L)<<SPI_CLKCNT_L_S));

	//SET DATA ORDER (MSB FIRST)
	SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_WR_BYTE_ORDER);

	//SET SPI DATA LENGTHS
	WRITE_PERI_REG(SPI_USER1(HSPI), (((data_len - 1) & SPI_USR_MOSI_BITLEN) << SPI_USR_MOSI_BITLEN_S) |
							   (((addr_len - 1) & SPI_USR_ADDR_BITLEN) << SPI_USR_ADDR_BITLEN_S));

}

void ESP8266_SPI_send(uint8_t addr_len, uint8_t data_len, uint32_t address, uint32_t data)
{
	//SEND SPI DATA OUT
	//DATA FORMAT : [ADDRESS] - [MOSI DATA]

	while(spi_busy(HSPI)); //wait for SPI to be ready

	//SETUP + ENABLE ADDRESS
	//IF ADDRESS LEN != 0
	if(addr_len)
	{
		SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_ADDR);
		WRITE_PERI_REG(SPI_ADDR(HSPI), address << (32 - addr_len));
	}

	//SETUP + ENABLE MOSI DATA
	//IF MOSI LEN != 0
	if(data_len)
	{
		SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_MOSI);
		//SINCE SPI DATA REGISTER IS 32 BIT AND DATA WILL GO MSB FIRST
		//WE NEED TO SHIFT OUR 8 BIT DATA TO MSB SIDE OF W0 REGISTER
		WRITE_PERI_REG(SPI_W0(HSPI), data << (32 - data_len));
	}

	//NOW FINALLY SEND DATA
	SET_PERI_REG_MASK(SPI_CMD(HSPI), SPI_USR);
	//WAIT FOR HSPI TO END BEFORE BRINGING CS HIGH
	while(spi_busy(HSPI));
}

void ESP8266_SPI_get(uint8_t* data)
{

}
