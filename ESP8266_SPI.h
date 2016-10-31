/*************************************************
* ESP8266 HARDWARE SPI (HSPI) LIBRARY
*
* OCTOBER 26 2016
* ANKIT BHATNAGAR
* ANKIT.BHATNAGARINDIA@GMAIL.COM
* ***********************************************/

#ifndef _ESP8266_SPI_H_
#define _ESP8266_SPI_H_


#include "ESP8266_SPI.h"
#include "spi_register.h"
#include "user_interface.h"
#include <ets_sys.h>
#include "gpio.h"
#include "spi.h"


#define spi_busy(spi_no) READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR
#define ESP8266_SPI_CS_LOW GPIO_OUTPUT_SET(4, 0)
#define ESP8266_SPI_CS_HIGH GPIO_OUTPUT_SET(4, 1)

void ESP8266_SPI_init_pins(void);
void ESP8266_SPI_set_params(uint8_t addr_len, uint8_t data_len);
void ESP8266_SPI_send(uint8_t addr_len, uint8_t data_len, uint32_t address, uint32_t data);
void ESP8266_SPI_get(uint8_t* data);

#endif
