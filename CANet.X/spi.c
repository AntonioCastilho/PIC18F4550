/* ****************************************************************************
 * Project: Control Functions                                File spi.c                                      March/2022
 * ****************************************************************************
 * File description: Functions for configuring the SPI module.
 *                         The pages (pg) indicated are references to the pages of the PIC18F4550 
 *                         datasheet (in pdf file).
 *      
 * ****************************************************************************
 * Program environment for validation:
 *   MPLAB X IDE v6.0, XC8 v2.36, C std C90;
 *   PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal;
 *   Can Bus Module MCP2515 x TJA1050.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 *   Copyright (c) 2022 Antonio Aparecido Ariza Castilho <https://github.com/AntonioCastilho>
 * ****************************************************************************
 * Reference:
 *   Microchip PIC18F4550 Datasheet;
 *   Microchip MCP2515 Datasheet;
 *   MCP2515 Code examples: <https://microchipdeveloper.com/faq:2720>.
 * ****************************************************************************
 * Date           | Author                | Description
 * **********|************* *|***************************************************
 * 03/12/2022 | Antonio Castilho  | Function has been created
 ******************************************************************************/ 

#include <xc.h>
#include "spi.h"

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Function: void initialize_SPI(void)
 * Description: Configures the SPI for communication with the MCP2515 module
 * Input: void
 * Output: void
 * Created in: 13/03/2022 by Antonio Aparecido Ariza Castilho
 */

void spi_initialize(void)
{
    // I/O pins definition for SPI 
    TRISBbits.TRISB1 = OUTPUT; // SCK
    TRISCbits.TRISC7 = OUTPUT; // SDO
    TRISAbits.TRISA5 = OUTPUT; // SS
    TRISBbits.TRISB0 = INPUT;  // SDI
    TRISBbits.TRISB2 = INPUT;  // MCP_INT: INT2
    
    // Master mode.
    // Sample at midle. Transmit on active-to-idle clock transition
    SSPSTAT = 0x40; // 0b01000000 MSSP status register (SPI mode) pg. 196
    // Enables serial port and configures SCK SDO SDI SS. SPI clock FOSC/16
    SSPCON1 = 0x21; // 0b00100001 MSSP status register (SPI mode) pg. 197
    
    PIR1bits.SSPIF = 0; // SSPBUF flag. Pg. 104

    ADCON0 = 0;    // No analog channel selected. Pg. 261
    ADCON1 = 0x0E; // Analog ports will be limited to AN:AN0 (4 ports). Pg 262
    
    // PORTB pull-ups are enabled by individual port latch values. Pg. 102
    INTCON2bits.RBPU = 0; 
    
    // INTCON3: INTERRUPT CONTROL REGISTER 3. Pg. 103
    INTCON3bits.INT2IP = HIGH;   // INT2 External Interrupt Priority bit
    INTCON3bits.INT2IE = ENABLE; // INT2 External Interrupt Enable bit.
    INTCON3bits.INT2IF = NO;     // INT2 External Interrupt Flag bit
    
} // end  initialize_spi(void)

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Function: void close_spi(void)
 * Description: Disable SPI communication.
 * Input: void
 * Output: void
 * Created in: 13/03/2022 by Antonio Aparecido Ariza Castilho
 */

void spi_close(void)
{
    // Disable SCK, SDO, SDI and SS pins as serial ports and enable
    // them as I/O ports. Pg 197
    SSPCON1bits.SSPEN = 0;
    
} // end void close_spi(void).

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Function: void write_spi(uint8_t data_to_send)
 * Description: Send 1 byte via SPI to connected slave.
 * Input: uint8_t data_to_send, that is the date to send
 * Output: void
 * Created in: 13/03/2022 by Antonio Aparecido Ariza Castilho
 */

void spi_write(uint8_t data_to_send)
{
    uint8_t buffer_flush;
    SSPBUF = data_to_send;  // transmit.
    while(!PIR1bits.SSPIF); // wait for complete transmission.
    PIR1bits.SSPIF = 0;     // clear flag.
    buffer_flush = SSPBUF;  // flush the buffer.
    
} // end void write_spi(uint8_t data_to_send)

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Function: uint8_t read_spi(void);
 * Description: Read 1 byte via SPI to connected slave.
 * Input: void
 * Output: (uint8_t) data read; this is the data that was read.
 * Created in: 14/03/2022 by Antonio Aparecido Ariza Castilho
 */

uint8_t spi_read(void)
{
    SSPBUF = 0xff; // Copy flush byte in SSBUF.
    while(!PIR1bits.SSPIF); // Wait for complete 1 byte transmission.
    PIR1bits.SSPIF = 0;
    return(SSPBUF);
    
} // end  uint8_t read_spi(void)
