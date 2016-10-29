/*************************************************
* ESP8266 HARDWARE SPI (HSPI) LIBRARY
* NOT USING HARDWARE HSPI
* BIT BANGING
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

#define SPI_MOSI_PIN 13
#define SPI_MISO_PIN 15
#define SPI_SCLK_PIN 14
#define SPI_CS_PIN   4

#define ESP8266_SPI_MOSI_HIGH GPIO_OUTPUT_SET(SPI_MOSI_PIN, 1)
#define ESP8266_SPI_MOSI_LOW GPIO_OUTPUT_SET(SPI_MOSI_PIN, 0)
#define ESP8266_SPI_SCLK_HIGH GPIO_OUTPUT_SET(SPI_SCLK_PIN, 1)
#define ESP8266_SPI_SCLK_LOW GPIO_OUTPUT_SET(SPI_SCLK_PIN, 0)
#define ESP8266_SPI_CS_HIGH GPIO_OUTPUT_SET(SPI_CS_PIN, 1)
#define ESP8266_SPI_CS_LOW GPIO_OUTPUT_SET(SPI_CS_PIN, 0)

void ESP8266_SPI_init_pins(void);
void ESP8266_SPI_set_params(void);
void ESP8266_SPI_send(uint8_t address, uint8_t data);
void ESP8266_SPI_get(uint8_t* data);

#endif
