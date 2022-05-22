/* ****************************************************************************
 * Project: Control Functions                                File spi.ch                                    March/2022
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
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SPI_H
#define	SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "project_constants.h"

// function prototypes used to configure the PIC
void spi_initialize(void);
void spi_close(void);
void spi_write(uint8_t data_to_send);
uint8_t spi_read(void);

#endif	/* SPI_H */

