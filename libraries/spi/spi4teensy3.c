/*
 * File:   spi4teensy3.cpp
 * Author: xxxajk
 *
 * Created on November 21, 2013, 10:54 AM
 */

#if defined(__MK20DX128__) || defined(__MK20DX256__)
#include "spi4teensy3.h"
/**
 * spi4teesny3 is a library for the freescale microcontroller
 * on a teensy 3.x from http://pjrc.com
 * <PRE>
 * Documentation for initialization of SPI.
 *
 * Speed:
 * Speed is the internal buss speed is _always_ divided at least by 2.
 * This table shows the speeds supported for a given value.
 *
 * speed | buss speed  | uC speed | uC speed
 * value |   divisor   | 96/48MHz |  24MHz
 * ------+-------------+----------+----------
 *   0   |      2      |  24MHz   | 12MHz
 * ------+-------------+----------+----------
 *   1   |      4      |  12MHz   | 6MHz
 * ------+-------------+----------+----------
 *   2   |      8      |  6MHz    | 3MHz
 * ------+-------------+----------+----------
 *   3   |      12     |  4MHz    | 2MHz
 * ------+-------------+----------+----------
 *   4   |      16     |  3MHz    | 1.5MHz
 * ------+-------------+----------+----------
 *   5   |      32     |  1.5MHz  | 750KHz
 * ------+-------------+----------+----------
 *   6   |      64     |  750KHz  | 375KHz
 * ------+-------------+----------+----------
 *   7   |      128    |  375KHz  | 187.5KHz
 * ------+-------------+----------+----------
 *
 * cpol is the SPI clock Polarity
 * cpha is the SPI clock capture Phase
 *
 * CPOL | CPHA | Description
 * -----+------+----------------------------------------------------------------
 *      |      | Idle clock state is low
 *  0   |  0   | data captured on clock low->high
 *      |      | data propagated on high->low
 * -----+------+----------------------------------------------------------------
 *      |      | Idle clock state is low
 *  0   |  1   | data captured on clock high->low
 *      |      | data propagated on low->high
 * -----+------+----------------------------------------------------------------
 *      |      | Idle clock state is high
 *  1   |  0   | data captured on clock high->low
 *      |      | data propagated on low->high
 * -----+------+----------------------------------------------------------------
 *      |      | Idle clock state is high
 *  1   |  1   | data captured on clock low->high
 *      |      | data propagated on high->low
 * -----+------+----------------------------------------------------------------
 *
 * cpol and cpha are specified separately instead of using mode numbers in order
 * to simplify the design, however, A set of handy macros are available for
 * initialization as follows:
 *
 * SPI4TEENSY3_MODE_0
 * SPI4TEENSY3_MODE_1
 * SPI4TEENSY3_MODE_2
 * SPI4TEENSY3_MODE_3
 * MODE_TO_SPI4TEENSY3_MODE(x) -- where 'x' is 0, 1, 2 or 3
 *
 * The following examples are all equal, but the first one is the best
 * to use for maximum speed and mode 0 as it produces the smallest amount of code.
 * This default was chosen since nearly all devices support mode 0, and all the
 * devices I use work at the maximum speed possible. Your devices might too.
 *
 * spi4teensy3::init()
 * spi4teensy3::init(0)
 * spi4teensy3::init(0, 0)
 * spi4teensy3::init(0, 0, 0)
 * spi4teensy3::init(SPI4TEENSY3_MODE_0)
 * spi4teensy3::init(MODE_TO_SPI4TEENSY3_MODE(0))
 * spi4teensy3::init(0, SPI4TEENSY3_MODE_0)
 * spi4teensy3::init(0, MODE_TO_SPI4TEENSY3_MODE(0))
 *
 * </PRE>
 */
		uint32_t ctar=0;

        void spi4t3_init_master(void) {
        		// enable clock to SPI.
        		SIM_SCGC6 |= SIM_SCGC6_SPI0;
                spi4t3_setMCR(MASTER);
                spi4t3_setCTAR(0 , 16, SPI_MODE2, MSB_FIRST, SPI_CLOCK_DIV8);
                spi4t3_enablePins(SCK, MOSI, MISO, CS4, CS4_ActiveLOW);
        }

        void spi4t3_enablePins(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs, int activeState)
        {
                if (sck == 0x0D){
                        CORE_PIN13_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);}    //Set Pin13 Output & SCK
                if (sck == 0x0E){
                        CORE_PIN13_CONFIG = PORT_PCR_MUX(1);
                        CORE_PIN14_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);}    //Set Pin14 Output & SCK
                if (mosi == 0x0B){
                        CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);}    //Set Pin11 Output & MOSI
                if (mosi ==  0x07){
                        CORE_PIN7_CONFIG  = PORT_PCR_DSE | PORT_PCR_MUX(2);}    //Set Pin7  Output & MOSI
                if (miso == 0x0C){
                        CORE_PIN12_CONFIG = PORT_PCR_MUX(2);}                                   //Set Pin12 Input & MISO
                if (miso ==  0x08){
                        CORE_PIN8_CONFIG  = PORT_PCR_MUX(2);}                                   //Set Pin8  Input & MISO
                spi4t3_enableCS(cs, activeState);
        }

        void spi4t3_enableCS(uint8_t cs, int activeState){
                if (cs   == 0x01){
                        CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin10 Output & CS0
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS0_ActiveLOW);}}
                if (cs   ==  0x02){
                        CORE_PIN9_CONFIG  = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin9  Output & CS1
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS1_ActiveLOW);}}
                if (cs   == 0x04){
                        CORE_PIN20_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin20 Output & CS2
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS2_ActiveLOW);}}
                if (cs   == 0x08){
                        CORE_PIN21_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin21 Output & CS3
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS3_ActiveLOW);}}
                if (cs   == 0x10){
                        CORE_PIN15_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin15 Output & CS4
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS4_ActiveLOW);}}
                if (cs   ==  0x81){
                        CORE_PIN2_CONFIG  = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin2  Output & (alt) CS0
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS0_ActiveLOW);}}
                if (cs   ==  0x82){
                        CORE_PIN6_CONFIG  = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin6  Output & (alt) CS1
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS1_ActiveLOW);}}
                if (cs   == 0x84){
                        CORE_PIN23_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin23 Output & (alt) CS2
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS2_ActiveLOW);}}
                if (cs   == 0x88){
                        CORE_PIN22_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);             //Set Pin22 Output & (alt) CS3
                        if (activeState == 1){
                                spi4t3_setCS_ActiveLOW(CS3_ActiveLOW);}}
        }

        void spi4t3_setCS_ActiveLOW(uint32_t pin){
                spi4t3_stop();
                SPI0_MCR |= (pin);
                spi4t3_start();
        }

        void spi4t3_stop()
        {
                SPI0_MCR |= SPI_MCR_HALT | SPI_MCR_MDIS;
        }

        void spi4t3_start()
        {
                SPI0_MCR &= ~SPI_MCR_HALT & ~SPI_MCR_MDIS;
        }

        void spi4t3_setMCR(int mode)
        {
        	spi4t3_stop();
			if (mode==1){
				SPI0_MCR = SPI_MCR_MSTR;}
			else{
				SPI0_MCR=0x00000000;}
			spi4t3_start();
        }

        void spi4t3_setCTAR(int CTARn, uint8_t size, uint8_t dataMode, uint8_t bo, uint8_t cdiv)
        {
                if (CTARn==0){
                        SPI0_CTAR0=0;}
                if(CTARn == 1){
                        SPI0_CTAR1=0;}
                spi4t3_setFrameSize(CTARn, (size - 1));
                spi4t3_setMode(CTARn, dataMode);
                spi4t3_setBitOrder(CTARn, bo);
                spi4t3_setClockDivider(CTARn, cdiv);
        }

        void spi4t3_setFrameSize(uint8_t CTARn, uint8_t size)
        {
                spi4t3_stop();
                if (CTARn==0){
                        SPI0_CTAR0 |= SPI_CTAR_FMSZ(size);}
                if (CTARn==1){
                        SPI0_CTAR1 |= SPI_CTAR_FMSZ(size);}
                if (CTARn==2){
                        SPI0_CTAR0_SLAVE |= SPI_CTAR_FMSZ(size);}
                spi4t3_start();
        }

        void spi4t3_setMode(uint8_t CTARn, uint8_t dataMode)
        {
                spi4t3_stop();
                if (CTARn==0){
                        SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}
                if (CTARn==1){
                        SPI0_CTAR1 = SPI0_CTAR1 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}
                if (CTARn==2){
                        SPI0_CTAR0_SLAVE = SPI0_CTAR0_SLAVE & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}
                spi4t3_start();
        }

        void spi4t3_setBitOrder(int CTARn, uint8_t bo)
        {
                spi4t3_stop();
                if (CTARn==0){
                        if (bo == LSBFIRST) {
                                SPI0_CTAR0 |= SPI_CTAR_LSBFE;}
                        if (bo == MSBFIRST) {
                                SPI0_CTAR0 &= ~SPI_CTAR_LSBFE;}}
                if (CTARn==1){
                        if (bo == LSBFIRST) {
                                SPI0_CTAR1 |= SPI_CTAR_LSBFE;}
                        if (bo == MSBFIRST) {
                                SPI0_CTAR1 &= ~SPI_CTAR_LSBFE;}}
                spi4t3_start();
        }

        void spi4t3_setClockDivider(int CTARn, uint8_t cdiv)
        {
        // PCS to SCK Delay Scaler
        // Baud Rate Scaler
        // SCK baud rate = (fSYS/PBR) x [(1+DBR)/BR]
                spi4t3_stop();
                if (CTARn==0){
                        SPI0_CTAR0 |= SPI_CTAR_DBR | SPI_CTAR_CSSCK(cdiv) | SPI_CTAR_BR(cdiv);}
                if (CTARn==1){
                        SPI0_CTAR1 |= SPI_CTAR_DBR | SPI_CTAR_CSSCK(cdiv) | SPI_CTAR_BR(cdiv);}
                spi4t3_start();
        }

        //TRANSMIT & RECEIVE PACKET OF 16 BIT DATA
        void spi4t3_txrx16(volatile uint16_t *dataOUT, volatile uint16_t *dataIN, int length, int CTARn, uint8_t PCS){
        	int i;
        	for (i=0; i < length; i++){
        		SPI0_MCR |= SPI_MCR_CLR_RXF;
        		SPI4T3_WRITE_16(dataOUT[i], CTARn, PCS);
        		SPI4T3_WAIT();
        		dataIN[i]=SPI0_POPR;
        		}
        	printf("OUT: 0x%04x IN: 0x%04x\n", dataOUT[0], dataIN[0]);
        }

        uint32_t ctar0;
        uint32_t ctar1;

        void spi4teensy3_updatectars() {
                // This function is only used internally.
                uint32_t mcr = SPI0_MCR;
                if(mcr & SPI_MCR_MDIS) {
                        SPI0_CTAR0 = ctar0;
                        SPI0_CTAR1 = ctar1;
                } else {
                        SPI0_MCR = mcr | SPI_MCR_MDIS | SPI_MCR_HALT;
                        SPI0_CTAR0 = ctar0;
                        SPI0_CTAR1 = ctar1;
                        SPI0_MCR = mcr;
                }
        }

        /**
         * Generic initialization. Maximum speed, cpol and cpha 0.
         */
        void spi4teensy3_init() {
                SIM_SCGC6 |= SIM_SCGC6_SPI0;
                CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
                CORE_PIN12_CONFIG = PORT_PCR_MUX(2);
                CORE_PIN13_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);

                // SPI_CTAR_DBR, SPI_CTAR_BR(0), SPI_CTAR_BR(1)
                ctar0 = SPI_CTAR_DBR;
                ctar1 = ctar0;
                ctar0 |= SPI_CTAR_FMSZ(15);
                ctar1 |= SPI_CTAR_FMSZ(15);
                SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_PCSIS(0x1F);
                SPI0_MCR |= SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF;
                spi4teensy3_updatectars();
        }

        /**
         * Initialization with max speed, cpol and cpha configurable.
         * @param cpol SPI Polarity
         * @param cpha SPI Phase
         */
        void spi4teensy3_init_c(uint8_t cpol, uint8_t cpha) {
                spi4teensy3_init();
                ctar0 |= (cpol == 0 ? 0 : SPI_CTAR_CPOL) | (cpha == 0 ? 0 : SPI_CTAR_CPHA);
                ctar1 |= (cpol == 0 ? 0 : SPI_CTAR_CPOL) | (cpha == 0 ? 0 : SPI_CTAR_CPHA);
                spi4teensy3_updatectars();
        }

        /**
         * Initialization with cpol and cpha 0, speed is configurable.
         *
         * @param SPI speed [0-7]
         */
        void spi4teensy3_init_speed(uint8_t speed) {
                spi4teensy3_init();
                // Default 1/2 speed
                uint32_t ctar = SPI_CTAR_DBR;
                switch(speed) {
                        case 1: // 1/4
                                ctar = 0;
                                break;
                        case 2: // 1/8
                                ctar = SPI_CTAR_BR(1);

                                break;
                        case 3: // 1/12
                                ctar = SPI_CTAR_BR(2);
                                break;

                        case 4: // 1/16
                                ctar = SPI_CTAR_BR(3);
                                break;

                        case 5: // 1/32
                                ctar = SPI_CTAR_PBR(1) | SPI_CTAR_BR(4);
                                break;

                        case 6: // 1/64
                                ctar = SPI_CTAR_PBR(1) | SPI_CTAR_BR(5);
                                break;

                        case 7: //1/128
                                ctar = SPI_CTAR_PBR(1) | SPI_CTAR_BR(6);
                                break;
                                // fall thru
                        default:
                                // default 1/2 speed, this is the maximum.
                                break;
                }
                ctar0 = ctar | SPI_CTAR_FMSZ(7);
                ctar1 = ctar | SPI_CTAR_FMSZ(15);
                spi4teensy3_updatectars();
        }

        /**
         * Initialization with speed, cpol, and cpha configurable.
         *
         * @param SPI speed [0-7]
         * @param cpol SPI Polarity
         * @param cpha SPI Phase
         */
        void spi4teensy3_init_all(uint8_t speed, uint8_t cpol, uint8_t cpha) {
                spi4teensy3_init_speed(speed);
                ctar0 |= (cpol == 0 ? 0 : SPI_CTAR_CPOL) | (cpha == 0 ? 0 : SPI_CTAR_CPHA);
                ctar1 |= (cpol == 0 ? 0 : SPI_CTAR_CPOL) | (cpha == 0 ? 0 : SPI_CTAR_CPHA);
                spi4teensy3_updatectars();
        }

        /**
         * Send 1 byte.
         *
         * @param b byte to send over SPI
         */
        uint8_t spi4teensy3_send(uint8_t b) {
                uint8_t byte_tmp;
                // clear any data in RX/TX FIFOs, and be certain we are in master mode.
                SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF | SPI_MCR_PCSIS(0x1F);
                SPI0_SR = SPI_SR_TCF;
                SPI0_PUSHR = SPI_PUSHR_CONT | b;
                while(!(SPI0_SR & SPI_SR_TCF));
                byte_tmp = SPI0_POPR;
                return byte_tmp;
        }

        uint16_t spi4teensy3_send_word(uint16_t word){
            uint16_t word_tmp;

            // clear any data in RX/TX FIFOs, and be certain we are in master mode.
            SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF | SPI_MCR_PCSIS(0x1F);
            SPI0_SR = SPI_SR_TCF;
            SPI0_PUSHR = SPI_PUSHR_CONT | word;
            while(!(SPI0_SR & SPI_SR_TCF));
            word_tmp = SPI0_POPR;
            return word_tmp;
        }

        /**
         * Send an array of bytes.
         *
         * @param bufr array of bytes to spi4teensy3_send
         * @param n number of bytes to spi4teensy3_send
         */
        void spi4teensy3_send_buf(void *bufr, size_t n) {
                int i;
                int nf;
                uint8_t *buf = (uint8_t *)bufr;

                if(n & 1) {
                        spi4teensy3_send(*buf++);
                        n--;
                }
                // clear any data in RX/TX FIFOs, and be certain we are in master mode.
                SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF | SPI_MCR_PCSIS(0x1F);
                // initial number of words to push into TX FIFO
                nf = n / 2 < 3 ? n / 2 : 3;
                // limit for pushing data into TX fifo
                uint8_t* limit = buf + n;
                for(i = 0; i < nf; i++) {
                        uint16_t w = (*buf++) << 8;
                        w |= *buf++;
                        SPI0_PUSHR = SPI_PUSHR_CONT | SPI_PUSHR_CTAS(1) | w;
                }
                // write data to TX FIFO
                while(buf < limit) {
                        uint16_t w = *buf++ << 8;
                        w |= *buf++;
                        while(!(SPI0_SR & SPI_SR_RXCTR));
                        SPI0_PUSHR = SPI_PUSHR_CONT | SPI_PUSHR_CTAS(1) | w;
                        SPI0_POPR;
                }
                // wait for data to be sent
                while(nf) {
                        while(!(SPI0_SR & SPI_SR_RXCTR));
                        SPI0_POPR;
                        nf--;
                }
        }

        /**
         * @return byte from SPI
         */
        uint8_t spi4teensy3_receive() {
                // clear any data in RX/TX FIFOs, and be certain we are in master mode.
                SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF | SPI_MCR_PCSIS(0x1F);
                SPI0_SR = SPI_SR_TCF;
                SPI0_PUSHR = SPI_PUSHR_CONT | 0xFF;
                while(!(SPI0_SR & SPI_SR_TCF));
                return SPI0_POPR;
        }

        /**
         * Receive multiple bytes from SPI.
         *
         * @param bufr array that stores bytes from SPI.
         * @param n number of bytes to receive.
         */
        void spi4teensy3_receive_buf(void *bufr, size_t n) {
                int i;
                uint8_t *buf = (uint8_t *)bufr;

                if(n & 1) {
                        *buf++ = spi4teensy3_receive();
                        n--;
                }

                // clear any data in RX/TX FIFOs, and be certain we are in master mode.
                SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_CLR_TXF | SPI_MCR_PCSIS(0x1F);
                // initial number of words to push into TX FIFO
                int nf = n / 2 < 3 ? n / 2 : 3;
                for(i = 0; i < nf; i++) {
                        SPI0_PUSHR = SPI_PUSHR_CONT | SPI_PUSHR_CTAS(1) | 0XFFFF;
                }
                uint8_t* limit = buf + n - 2 * nf;
                while(buf < limit) {
                        while(!(SPI0_SR & SPI_SR_RXCTR));
                        SPI0_PUSHR = SPI_PUSHR_CONT | SPI_PUSHR_CTAS(1) | 0XFFFF;
                        uint16_t w = SPI0_POPR;
                        *buf++ = w >> 8;
                        *buf++ = w & 0XFF;
                }
                // limit for rest of RX data
                limit += 2 * nf;
                while(buf < limit) {
                        while(!(SPI0_SR & SPI_SR_RXCTR));
                        uint16_t w = SPI0_POPR;
                        *buf++ = w >> 8;
                        *buf++ = w & 0XFF;
                }

        }
#endif
