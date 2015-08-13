#include "WProgram.h"

#define HWSERIAL Serial1

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
