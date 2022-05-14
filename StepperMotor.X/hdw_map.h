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
#define TRUE             1
#define FALSE            0
#define HIGH             1
#define LOW              0
#define INPUT            1 
#define OUTPUT         0
#define YES               1
#define NO                0
#define UNPRESSED   1
#define PRESSED       0


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

#define USB_NEG        PORTCbits.RC5
#define USB_POS        PORTCbits.RC4


#define LCD_E            PORTDbits.RD0 
#define LCD_RS          PORTDbits.RD1
#define LCD_RW         PORTDbits.RD2

#define LCD_D4          PORTDbits.RD4
#define LCD_D5          PORTDbits.RD5
#define LCD_D6          PORTDbits.RD6
#define LCD_D7          PORTDbits.RD4
         

#endif	/* HDW_MAP_H */

