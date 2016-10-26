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

void ESP8266_SPI_init_pins(void);
void ESP8266_SPI_set_params(void);
void ESP8266_SPI_send(uint32_t address, uint32_t data);
void ESP8266_SPI_get(uint8_t* data);

#endif
