/* ****************************************************************************
 * Project: Control Functions                         File mcp2515.c                                   March/2022
 * ****************************************************************************
 * File description: Function definitions, macros and configuration instructions, for use with the 
 *                        MCP2515 CAN network interface.
 *                        The pages (pg) indicated are references to the pages of the 
 *                        MCP2515 datasheet (in pdf file).
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
 * 03/13/2022 | Antonio Castilho  | Function has been created
 ******************************************************************************/ 

#include <xc.h>
#include "mcp2515.h"
#include "REGS2515.h"

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 * Function: void mcp2515_reset(void);
 * Description: Configures for MCP2515 module
 * Input: void
 * Output: void
 * Created in: 03/13/2022 by Antonio Aparecido Ariza Castilho
 */

void mcp2515_reset(void)
{
    CS = LOW;
    spi_write(CAN_RESET);
    CS = HIGH;
    
} // end  void reset_mcp2515(void)

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 * Function: void mcp2515_write(uint8_f addr, uint8_t value);
 * Description: Writes a value to an mcp2515 register.
 * Input: register address and a new value.
 * Output: void
 * Created in: 03/13/2022 by Antonio Aparecido Ariza Castilho
 */

void mcp2515_write(uint8_t addr, uint8_t value)
{
    CS = LOW;
    spi_write(CAN_WRITE);
    spi_write(addr);
    spi_write(value);
    CS = HIGH;
    
} // end  void message_to_can(data_frame *message)

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- 
 * Function: uint8_t mcp2515_read(uint8_t addr);
 * Description: Reads a value from an mcp2515 register.
 * Input: register address.
 * Output: data read.
 * Created in: 03/20/2022 by Antonio Aparecido Ariza Castilho
 */

uint8_t mcp2515_read(uint8_t addr)
{
    CS = LOW;
    spi_write(CAN_READ);
    spi_write(addr);
    uint8_t temp_data = spi_read();
    CS = HIGH;
    return temp_data;
    
} // end void message_to_can(data_frame *message)

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 * Function: void mcp2515_initialize(void);
 * Description: Configures for MCP2515 module
 * Input: void
 * Output: void
 * Created in: 03/13/2022 by Antonio Aparecido Ariza Castilho
 */
 
void mcp2515_initialize(void)
{
    mcp2515_reset();
    delay_rms(1);
    
    // Clears the masks to allow all messages arriving from the CAN bus 
    // to be received.
    mcp2515_write(RXM0SIDH, 0x00); // Clear mask RX buffer 0. Pg 37.
    mcp2515_write(RXM1SIDH, 0x00); // Clear mask RX buffer 1. Pg 37.
    
    // Ensures to only use filters for standard frames, when clearing EXIDE bit.
    mcp2515_write(RXF0SIDL,0x00);  // Clear filter. Pg 35.
    
    mcp2515_write(CNF1, SJW_1TQ | CAN_500kbps); // Pg 44.
    mcp2515_write(CNF2, BTLMODE_CNF3 | SMPL_1X | PHSEG1_3TQ | PRSEG_2TQ);
    mcp2515_write(CNF3, PHSEG2_2TQ); //Pg 45.
    
    mcp2515_write(CANINTE, RX0IE | RX1IE | TX0IE | TX1IE | TX2IE | ERRIE
            | WAKIE | MERRE); // CAN interrupt enable register. Pg 53.
   
    mcp2515_write(CANCTRL, REQOP_NORMAL); // CAN control register. Pg 60.
    
} // end  void initialie_mcp2515(void))

