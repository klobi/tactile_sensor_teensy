#include "WProgram.h"
#include <spi4teensy3.h>

#define HWSERIAL Serial1
#define printf HWSERIAL.printf

void setup()
{
        HWSERIAL.begin(115200);
}

int main(void)
{
        int incomingByte;
	setup();
	while(true)
	{
		if (HWSERIAL.available() > 0) {
			incomingByte = HWSERIAL.read();
	                printf("UART received: %i\n", incomingByte);
		}
	}
}
