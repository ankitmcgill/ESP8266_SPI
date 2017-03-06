/*************************************************************************
* ESP8266 HARDWARE SPI (HSPI) LIBRARY
* SUPPORTS ONLY SPI MASTER MODE
* (WRITING SPI DATA TO SLAVE)
* NO READING / MISO SUPPORT
*
* DOES NOT SUPPORT ESP8266 SPI COMMAND BITS. ONLY SENDS DATA AND ADDRESS
* THROUGH SPI BITS
*
* OCTOBER 26 2016
* ANKIT BHATNAGAR
* ANKIT.BHATNAGARINDIA@GMAIL.COM
*
* REFERENCES
* 	- SPI REGISTERS EXPLAINED : http://www.esp8266.com/viewtopic.php?f=13&t=2367
* 	- http://www.esp8266.com/viewtopic.php?f=13&t=2413
* 	- NEIL KOLBAN ESP8266 BOOK : SPI CHAPTER : PAGE 135
* 	- https://github.com/MetalPhreak/ESP8266_SPI_Driver
* ***********************************************************************/

#ifndef _ESP8266_SPI_H_
#define _ESP8266_SPI_H_

#include <ets_sys.h>
#include <gpio.h>
#include "spi_register.h"
#include "gpio.h"
#include "spi.h"
#include "user_interface.h"

#define ESP8266_SPI_ORDER_MSB_FIRST 0
#define ESP8266_SPI_ORDER_LSB_FIRST 1
#define spi_busy(spi_no) READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR

void ESP8266_SPI_init_pins(void);
void ESP8266_SPI_set_params(uint8_t data_packet_len, uint16_t addr_packet_len, uint16_t clk_pre, uint16_t clk_cnt, uint16_t clk_h, uint16_t clk_l, uint8_t data_order);
void ESP8266_SPI_send(uint8_t addr_len, uint8_t data_len, uint32_t address, uint32_t data);
void ESP8266_SPI_get(uint8_t* data);

#endif
