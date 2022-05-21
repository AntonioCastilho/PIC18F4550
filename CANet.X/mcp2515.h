/* ****************************************************************************
 * Project: Control Functions                         File mcp2515.h                                  March/2022
 * ****************************************************************************
 * File description: Function definitions, macros and configuration instructions, for use with the 
 *                        MCP2515 CAN network interface.
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
#ifndef MCP2515_H
#define	MCP2515_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "project_constants.h"
#include "spi.h"

typedef struct 
{
    uint16_t id;
    uint8_t rtr : 1;
    uint8_t dlc : 4;
    uint8_t data[8];
}data_frame;

data_frame can_message;

// Function prototypes

void mcp2515_reset(void);
void mcp2515_write(uint8_t addr, uint8_t value);
uint8_t mcp2515_read(uint8_t addr);
void mcp2515_initialize(void);

uint8_t message_from_can(unsigned char addr);

#endif	/* MCP2515_H */

