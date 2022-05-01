/* Program: ECT Sensor     File: ntc.h    
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 * Description:
 *      This program uses a Thermistor to measure the temperature and display it on the LCD Display.
 *      The Thermistor chosen is an Iguaçu 201.0805, for automotive application <www.iguacu.com.br>.
 *      Function definitions are in the ntc.c file.
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/25/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef NTC_H
#define	NTC_H
#include <xc.h>
#include <math.h>
#include "fuse_bits.h"
#include "adc.h"

#define beta      3600.0 // Beta coefficient 3600
#define r0         2048 //  is the reference resistance at temperature t0 in homs
#define t0         298   // reference temperature in Kelvin 1800
#define rx         (r0 * exp((-beta / t0))) // correction value, considering the reference values 
                                                          // (resistance and temperature) and the Beta value.

// Values of the suitability circuit for reading the NTC thermistor.
#define VCC      5 // Reference voltage.
#define r_ref     10000 // Reference resistor.
#define n_sample  10  // Number of sample readings.

uint16_t ntc_get(uint8_t ch);

#endif	/* NTC_H */

