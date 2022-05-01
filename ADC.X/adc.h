/* ****************************************************************************
 * Project: Control Functions             File adc.h                 March/2022
 * ****************************************************************************
 * File description:       
 * ****************************************************************************
 * Program environment for validation: MPLAB X IDE v6.0, XC8 v2.36, C std C90,
 * PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 *   Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 *   <https://github.com/AntonioCastilho>
 * ****************************************************************************
 * Reference:
 * * Microchip PIC18F4550 Datasheet.
 * * Program Archive for the Advanced Topics Course in Microcontroller 
 *   Programming, Technology Colleges In Automotive Electronics, 
 *   FATEC Santo André. Professor Wesley Medeiros Torres.
 *   <http://www.fatecsantoandre.edu.br/>.
 * * MicroChip Developer Help sample program files. 
 *   <https://microchipdeveloper.com/>.
 * ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 04/16/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/ 

#ifndef ADC_H
#define	ADC_H

/******************************************************************************/
// Include header files.
/******************************************************************************/
#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

/******************************************************************************/
// Function prototypes
/******************************************************************************/
void adc_ini(void);
uint16_t adc_read(uint8_t ch);
/******************************************************************************/
#endif	/* ADC_H */

