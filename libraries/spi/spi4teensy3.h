/*
 * File:   spi4teensy3.h
 * Author: xxxajk
 *
 * Created on November 21, 2013, 10:54 AM
 */

#ifndef SPI4TEENSY3_H
#define	SPI4TEENSY3_H
#if defined(__MK20DX128__) || defined(__MK20DX256__)
#include <mk20dx128.h> // same header for Teensy 3.0 & 3.1
#include <core_pins.h>
#include <sys/types.h>

#ifndef SPI_SR_RXCTR
#define SPI_SR_RXCTR 0XF0
#endif
#ifndef SPI_PUSHR_CONT
#define SPI_PUSHR_CONT 0X80000000
#endif
#ifndef SPI_PUSHR_CTAS
#define SPI_PUSHR_CTAS(n) (((n) & 7) << 28)
#endif

#define SPI4TEENSY3_MODE_0 0, 0
#define SPI4TEENSY3_MODE_1 0, 1
#define SPI4TEENSY3_MODE_2 1, 0
#define SPI4TEENSY3_MODE_3 1, 1
#define MODE_TO_SPI4TEENSY3_MODE(x) (x & 1), (x&2)

#define maxDataLength           256

#define MASTER                          1
#define SLAVE                           0

#define SPI_CLOCK_DIV2		0b0000	//24.0	MHz
#define SPI_CLOCK_DIV4		0b0001	//12.0	MHz
#define SPI_CLOCK_DIV6		0b0010	//08.0	MHz
#define SPI_CLOCK_DIV8		0b0011	//05.3	MHz
#define SPI_CLOCK_DIV16		0b0100	//03.0	MHz
#define SPI_CLOCK_DIV32		0b0101	//01.5	MHz
#define SPI_CLOCK_DIV64		0b0110	//750	KHz
#define SPI_CLOCK_DIV128	0b0111	//375	Khz

#define SPI_MODE0                       0x00
#define SPI_MODE1                       0x01
#define SPI_MODE2                       0x02
#define SPI_MODE3                       0x03

#define MSB_FIRST                       0
#define LSB_FIRST                       1

//#define CTAR0                           0
//#define CTAR1                           1

#define SCK                                     0x0D
#define MOSI                            0x0B
#define MISO                            0x0C
#define ALT_SCK                         0x0E
#define ALT_MOSI                        0x07
#define ALT_MISO                        0x08

#define CS0                                     0x01
#define CS1                                     0x02
#define CS2                                     0x04
#define CS3                                     0x08
#define CS4                                     0x10
#define ALT_CS0                         0x81
#define ALT_CS1                         0x82
#define ALT_CS2                         0x84
#define ALT_CS3                         0x88

#define CS_ActiveLOW            1
#define CS_ActiveHIGH           0
#define CS0_ActiveLOW           0x00010000
#define CS1_ActiveLOW           0x00020000
#define CS2_ActiveLOW           0x00040000
#define CS3_ActiveLOW           0x00080000
#define CS4_ActiveLOW           0x00100000

#define SPI_SR_TXCTR            0x0000f000 //Mask isolating the TXCTR


        void spi4teensy3_init();
        void spi4teensy3_init_speed(uint8_t speed);
        void spi4teensy3_init_c(uint8_t cpol, uint8_t cpha);
        void spi4teensy3_init_all(uint8_t speed, uint8_t cpol, uint8_t cpha);
        uint8_t spi4teensy3_send(uint8_t b);
        uint16_t spi4teensy3_send_word(uint16_t word);
        void spi4teensy3_send_buf(void *bufr, size_t n);
        uint8_t spi4teensy3_receive();
        void spi4teensy3_receive_buf(void *bufr, size_t n);
        void spi4teensy3_updatectars();


        void spi4t3_init_master();
        void spi4t3_enablePins(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs, int activeState);
        void spi4t3_enableCS(uint8_t cs, int activeState);
        void spi4t3_setCS_ActiveLOW(uint32_t pin);
        void spi4t3_stop();
        void spi4t3_start();
        void spi4t3_setMCR(int mode);
        void spi4t3_setCTAR(int CTARn, uint8_t size, uint8_t dataMode, uint8_t bo, uint8_t cdiv);
        void spi4t3_setFrameSize(uint8_t CTARn, uint8_t size);
        void spi4t3_setMode(uint8_t CTARn, uint8_t dataMode);
        void spi4t3_setBitOrder(int CTARn, uint8_t bo);
        void spi4t3_setClockDivider(int CTARn, uint8_t cdiv);
        void spi4t3_txrx16(volatile uint16_t *dataOUT, volatile uint16_t *dataIN, int length, int CTARn, uint8_t PCS);

#define SPI4T3_WRITE_16(w,CTARn, PCS) \
    	do { \
    		while ((SPI0_SR & SPI_SR_TXCTR) >= 0x00004000); \
    		SPI0_PUSHR = ((w)&0xffff) | SPI_PUSHR_CTAS(CTARn) | SPI_PUSHR_PCS(0x1f & PCS); \
    	} while(0)

#define SPI4T3_WAIT() \
	while ((SPI0_SR & SPI_SR_TXCTR) != 0); \
	while (!(SPI0_SR & SPI_SR_TCF)); \
	SPI0_SR |= SPI_SR_TCF;


#endif /* __MK20DX128__ || __MK20DX256__ */
#endif	/* SPI4TEENSY3_H */

