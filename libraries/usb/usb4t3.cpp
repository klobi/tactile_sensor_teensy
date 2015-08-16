#include "usb4t3.h"


void usb4t3_init()
{
  Serial.begin(115200);
}

void usb4t3_send_data(uint8_t* data, size_t size)
{
	Serial.write(data, size);
}
