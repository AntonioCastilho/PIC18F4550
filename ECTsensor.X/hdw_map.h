/* Program: hardware mapping   File: hdw_map.h    
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 * Description:
 *      Hardware mapping considering the FATEC Board.
 * 
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/26/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

#ifndef HDW_MAP_H
#define	HDW_MAP_H

#include <xc.h>

#define _XTAL_FREQ     8000000 // see fuse_bits.h and OSCCON. pg 34. 

#define pinNTC   0  // thermistor connection

#define ON                1
#define OFF               0
#define TRUE            1
#define FALSE           0
#define HIGH             1
#define LOW              0
#define INPUT            1 
#define OUTPUT         0

#define LED               PORTB
#define LED_0            PORTBbits.RB0
#define LED_1            PORTBbits.RB1
#define LED_2            PORTBbits.RB2
#define LED_3            PORTBbits.RB3
#define LED_4            PORTBbits.RB4
#define LED_5            PORTBbits.RB5
#define LED_6            PORTBbits.RB6
#define LED_7            PORTBbits.RB7

#define BTN_1            PORTEbits.RE0
#define BTN_2            PORTEbits.RE1
#define BTN_3            PORTEbits.RE2

#endif	/* HDW_MAP_H */

