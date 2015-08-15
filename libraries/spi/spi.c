/*
 * spi.c
 *
 *  Created on: Aug 13, 2015
 *      Author: Nicolas Bänsich
 */

#include <spi4teensy3.h>
#include "spi.h"

/**
 * Initialization with speed, cpol, and cpha configurable.
 *
 * @param SPI speed [0-7]
 * @param cpol SPI Polarity
 * @param cpha SPI Phase
 */
int spi_init_master(uint8_t speed, uint8_t cpol, uint8_t cpha)
{
	#ifdef __MK20DX256__
	//spi4teensy3_init_all(speed, cpol, cpha);
	spi4t3_init_master();
	#endif
	return 0;
}

uint8_t spi_chip_select(uint8_t cs, uint8_t state)
{
	if(state == LOW)
	{
		#ifdef __MK20DX256__
		digitalWrite(cs, state);
		#endif
	}
	else if(state == HIGH)
	{
		#ifdef __MK20DX256__
		digitalWrite(cs, state);
		#endif
	}
	return 0;
}

uint8_t spi_read_byte(uint8_t byte)
{
	uint8_t b = 0;
	#ifdef __MK20DX256__
	b = spi4teensy3_send(byte);
	#endif
	#ifdef DEBUG
	printf("Byte:\n\tsend: 0x%02x\n\tReceive: 0x%02x\n", byte, b);
	#endif
	return b;
}

uint16_t spi_read_word(uint16_t word)
{
	volatile uint16_t w = 0;
	#ifdef __MK20DX256__
	//w = spi4teensy3_send_word(word);
	spi4t3_txrx16(&word, &w, 1, 0, 10);
	#endif
	#ifdef DEBUG
	printf("Word:\n\tsend: 0x%04x\n\tReceive: 0x%04x\n", word, w);
	#endif
	return w;
}

int spi_transaction(uint8_t cs, uint16_t * data, size_t length)
{
	int i=0;
	/* pointer to the currently processed byte */
	uint16_t* current_data = NULL;

	/* No data space */
	if(length==0 || data==NULL)
	return 1;

	/* Select the peripheral device to be accessed */
	spi_chip_select(cs, LOW);
	/* Start transmission */
	for(i=0; i<length; i++)
	{
		/* next byte for processing */
		current_data = (data + i);
		/* do the actual transaction*/
		*current_data = spi_read_word(*current_data);
	}

	/* deselect the peripheral device to be accessed */
	spi_chip_select(cs, HIGH);

	return 0;
}
