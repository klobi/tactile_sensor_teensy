/*
 * ad7490.h
 *
 *  Created on: Aug 13, 2015
 *      Author: klobi
 */

#ifndef LIBRARIES_AD7490_AD7490_H_
#define LIBRARIES_AD7490_AD7490_H_

#include <spi.h>
#include <stdio.h>
#include "common.h"

typedef struct {
	unsigned char chip_select;
} ad7490;

typedef struct {
	unsigned char device;
	unsigned char channel;
	uint16_t value;
} ad7490_value;


int ad7490_read(ad7490* device, unsigned char channel,  ad7490_value* value);
uint8_t ad7490_read_all(ad7490* device, uint16_t* values);

int ad7490_init(ad7490* device);
int ad7490_init_devices(ad7490 * devices,  unsigned char length);
int ad7490_init_read_all(ad7490* device);

void ad7490_print_ad7490_value(ad7490_value * value);
void ad7490_print_raw_value(uint8_t devices, uint16_t* value);

#endif /* LIBRARIES_AD7490_AD7490_H_ */
