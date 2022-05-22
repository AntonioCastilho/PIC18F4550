/* ***************************************************************************************
 * Project: Control Functions                                File can_net.c                                      March/2022
 * ***************************************************************************************
 * File description:
 *                                     Communication via CAN network - CAN bus implementation
 *         This project is used to validate the software developed to study the Microchip PIC18F4550 MCU
 *         and the CAN BUS module MCP2515. For this, a CAN network was implemented where two 
 *         development boards that contain the PICs, make the activation of several peripherals, using 
 *         information that is available in the CAN network.
 * 
 *         The pages (pg) indicated are references to the pages of the PIC18F4550 datasheet (in pdf file).
 * 
 * ***************************************************************************************
 * Program environment for validation:
 *   MPLAB X IDE v6.0, XC8 v2.36, C std C90;
 *   PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal;
 *   Can Bus Module MCP2515 x TJA1050.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 *   Copyright (c) 2022 Antonio Aparecido Ariza Castilho <https://github.com/AntonioCastilho>
 * ***************************************************************************************
 * Reference:
 *   Microchip PIC18F4550 Datasheet;
 *   Microchip MCP2515 Datasheet;
 *   MCP2515 Code examples: <https://microchipdeveloper.com/faq:2720>.
 * ***************************************************************************************
 * Date           | Author                | Description
 * **********|************* *|*************************************************************
 * 05/21/2022 | Antonio Castilho  | created
 ****************************************************************************************/ 

#include <xc.h>
#include "fuse_bits.h"
#include "project_constants.h"
#include "REGS2515.h"
#include "mcp2515.h"
#include "spi.h"


/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Function: void main(void);
 * Description:  Main function of communication via CAN network
 * Input: void
 * Output: void
 * Created in: 05/21/2022 by Antonio Aparecido Ariza Castilho
 */

void main(void)
{
    
} // end main


