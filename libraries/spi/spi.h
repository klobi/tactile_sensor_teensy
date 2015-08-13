/*
 * spi.h
 *
 * Created: 11.03.2015 10:51:28
 * Author: Nicolas Baenisch
 */
#ifndef SPI_H_
#define SPI_H_

#include <stdio.h>
#include "common.h"

#ifdef __MK20DX256__
#include <spi4teensy3.h>
#endif

#define LOW 0
#define HIGH 1

int spi_init_master(uint8_t speed, uint8_t cpol, uint8_t cpha);

uint8_t spi_chip_select(uint8_t cs, uint8_t state);

uint8_t spi_read_byte(uint8_t byte);
uint16_t spi_read_word(uint16_t word);
int spi_transaction(uint8_t cs, uint16_t * data, size_t length);

#endif /* SPI_H_ */
