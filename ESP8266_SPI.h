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

#ifndef _ESP8266_SPI_H_
#define _ESP8266_SPI_H_


#include "ESP8266_SPI.h"
#include "spi_register.h"
#include "user_interface.h"
#include <ets_sys.h>
#include "gpio.h"
#include "spi.h"


#define spi_busy(spi_no) READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR

void ESP8266_SPI_init_pins(void);
void ESP8266_SPI_set_params(uint8_t addr_len, uint8_t data_len, uint16_t clk_pre, uint16_t clk_cnt, uint16_t clk_h, uint16_t clk_l);
void ESP8266_SPI_send(uint8_t addr_len, uint8_t data_len, uint32_t address, uint32_t data);
void ESP8266_SPI_get(uint8_t* data);

#endif
