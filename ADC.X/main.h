/* ****************************************************************************
 * Project: Basic control functions       File main.h                March/2022
 * ****************************************************************************
 * Description: Definitions and declarations for the project. 
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
 * * HD44780U dot-matrix liquid crystal display controller Datasheet
 *   <https://www.digchip.com/datasheets/parts/datasheet/740/HD44780U-pdf.php>
 * ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 03/23/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <string.h>
#include "fuse_bits.h"
#include "lcd.h"
#include "adc.h"

#define _XTAL_FREQ     20000000 // see fuse_bits.h and OSCCON. pg 34. 

#define ON             1
#define OFF            0
#define TRUE           1
#define FALSE          0
#define HIGH           1
#define LOW            0
#define INPUT          1 
#define OUTPUT         0


#endif	/* MAIN */

