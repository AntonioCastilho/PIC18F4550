/* Program: Timer Setups     File: timer.h    
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 *                      Internal oscillator 8 MHx;
 * Description:
 *      This file contains function definitions and declarations for configuring TIMER0, TIMER1, TIMER2 and 
 *      TIMER3 of the PIC18F4550.
 *      Formulas para o cálculo dos parâmetros:
 *              T = 4/_XTAL_FREQ) * Prescale * (Resolution - TMR0)
 *              TMRx = Resolution - (( T * Fosc ) / (4 * Prescale))
 *              Tmax = (4/_XTAL_FREQ)*max_prescale*(resolution - 0)
 *      Onde:
 *              T - is the desired time in seconds
 *               _XTAL_FREQ - is the oscillator frequency 
 *              Prescale - is the maximum prescale value ( T0CON<2:0> )
 *              Resolution - is the maximum value of the TMRx ( for 8-bit = 255, for 16-bit 65355)
 *              TMRx - is the timer preload value ( TMRxH, TMRxL )
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/22/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */
#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>
#include "lcd.h"

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 8000000 // Assume an internal 8 MHz oscillator, 
#endif                                        // see fuse_bits.h and config.h


void timer0_ini();
void timer0_write(uint16_t timer_value);

void timer1_ini();
void timer1_write(uint16_t timer_value);

void timer2_ini();
void timer2_write(uint16_t timer_value);

void timer3_ini();
void timer3_write(uint16_t timer_value);

#endif	/* TIMER_H */

