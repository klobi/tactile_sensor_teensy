#include "ad7490.h"

int ad7490_read(ad7490* device, unsigned char channel,  ad7490_value* value)
{
	/* 1000 0011 0101 0000
	* WRITE = yes
	* SEQ = 0
	* ADD3-ADD0 = 0
	* PM1 = PM0 = 1 (normal mode)
	* SHADOW = 0
	* WEAK/TRI = 1 (weak)
	* RANGE = 0 (0-5V)
	* CODING = 1 (straight binary)
	* four zeros filling
	*/
	uint16_t control = 0x8350;

	uint16_t raw_value;

	/* Store the device id */
	value->device = device->chip_select;

	/* Add channel request to 'control' */
	control |= channel << 10;

	/* Data from wrong channel */
	spi_transaction(device->chip_select, (void*)&control, 1);

	control = 0x0350;
	control |= channel << 10;
	spi_transaction(device->chip_select, (void*)&control, 1);

	/* Get the raw data */
	raw_value = control;
	/* Four first bits in raw data are the address number */
	value->channel = (raw_value >> 12);
	/* Remove the address from the raw value to get the value */
	value->value = raw_value & 0xFFF;

	#ifdef DEBUG
	printf("ADC Raw: 0x%04x \n",raw_value);
	printf("ADC Channel: %i \n", value->channel);
	printf("ADC Value: 0x%03x \n", value->value);
	#endif

	return 0;
}

uint8_t ad7490_read_all(ad7490* device, uint16_t* values)
{
	return 0;
}

/**
 * Initialization of all 16 ADC ports
 * @param ad7490 pointer to the device
 * @return error code
 */
int ad7490_init(ad7490* device)
{
	uint16_t dummy = 0xFFFF;
	int i;
	ad7490_value ad7490_temp;

	spi_transaction(device->chip_select, (void*)&dummy, 1);
	spi_transaction(device->chip_select, (void*)&dummy, 1);

	for(i=0; i<16; i++)
	{
		ad7490_read(device, i, &ad7490_temp);

		if(ad7490_temp.channel != i)
		{
			return 1;
		}
	}
	return 0;
}

int ad7490_init_devices(ad7490 * devices,  unsigned char length)
{
	int i=0;
	for (i=0; i<length;i++)
	{
		if(ad7490_init((void*)&devices[i]))
		{
			#ifdef DEBUG
			printf("ADC %i initialization failed!\n", devices[i].chip_select);
			#endif
			return 1;
		}
		ad7490_init_read_all((void*)&devices[i]);
	}
	#ifdef DEBUG
	printf("ADC initialization successful!\n");
	#endif
	return 0;
}

int ad7490_init_read_all(ad7490* device)
{
	/* Control Register:
	*   11    10    9     8     7     6    5    4      3        2       1       0
	* WRITE  SEQ  ADD3  ADD2  ADD1  ADD0  PM1  PM0  SHADOW  WEAK/TRI  RANGE  CODING
	* 1111 1111 1101 0000
	* WRITE = yes
	* SEQ = 1
	* ADD3-ADD0 = 1111
	* PM1 = PM0 = 1 (normal mode)
	* SHADOW = 1
	* WEAK/TRI = 1 (weak)
	* RANGE = 0 (0-5V)
	* CODING = 1 (straight binary)
	* four zeros filling
	*/
	uint16_t control = 0xFFD0;
	return spi_transaction(device->chip_select, &control, 2);
}

void ad7490_print_ad7490_value(ad7490_value * value)
{
	int i = 0;
	double e = 5.0;
	e = e / 4096.0;
	int v;

	for(i=0; i<16; i++)
	{
		v = value[i].value;
		// Ignore values under 50
		if(v < 50)
			v = 0;
		printf("ADC%02i: Channel: %2i Value: %4i Volt: %1.2f\n",
		value[i].device, value[i].channel, v, e*v);
	}
}

void ad7490_print_raw_value(uint8_t devices, uint16_t* value)
{
	ad7490_value adc_value[16];
	int i;
	for(i=0; i<16; i++)
	{
		adc_value[i].channel = (value[i] >> 12);
		adc_value[i].value = (value[i] % 0xFFF);
		adc_value[i].device = devices;
	}
	ad7490_print_ad7490_value(adc_value);
}
