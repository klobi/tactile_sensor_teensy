extern "C" {
#include <ad7490.h>
#include <spi.h>
#include "common.h"
}

#include <stdio.h>
#include <stdarg.h>
#include "WProgram.h"
#include <Arduino.h>

#define HWSERIAL Serial1

extern "C" {
	#include <sys/stat.h>
	int _write(int fd, const char *ptr, int len) {
		int j;
		for (j = 0; j < len; j++) {
				if (*ptr == '\n')
					HWSERIAL.write('\r');
				HWSERIAL.write(*ptr++);
		}
		return len;
	}

	int _read(int fd, char *ptr, int len) {
			if (len > 0 && fd == 0) {
					while (!HWSERIAL.available());
					*ptr = HWSERIAL.read();
					return 1;
			}
			return 0;
	}

	int _fstat(int fd, struct stat *st) {
			memset(st, 0, sizeof (*st));
			st->st_mode = S_IFCHR;
			st->st_blksize = 1024;
			return 0;
	}

	int _isatty(int fd) {
			return (fd < 3) ? 1 : 0;
	}
}
#define CS_PIN1 10

void setup()
{
	HWSERIAL.begin(115200);
}

int main(void)
{
	ad7490 devices[1];
	devices[0].chip_select = CS_PIN1;
	pinMode(CS_PIN1, OUTPUT);

	setup();

	printf("Hello and Welcome!\n");
	spi_init_master(3, 0, 0);



	while(1)
	{
		//uint16_t values[16];
		int i;
		printf("\nSTART\n");
		if(ad7490_init_devices(devices, 1))
		{
			printf("AD7490 Fail\n");
		}


		//spi_read_all((void*)&devices, values);

		for (i = 0;i <16; i++)
		{
			//printf("Raw: %i Value %i: %d\n",values[i], (values[i]>> 12), (values[i] & 0xFFF));
		}

		for(i=0; i<10; i++)
		{
			//spi_read_all((void*)&devices, values);
		}

		getchar();
	}
}
