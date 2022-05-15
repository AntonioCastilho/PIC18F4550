/* ****************************************************************************
 * Project: Control Functions             File stepper_motor.h                Maio/2022
 * ****************************************************************************
 * File description:       
 * ****************************************************************************
 * Program environment for validation: MPLAB X IDE v6.0, XC8 v2.36, C std C90,
 * PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho <https://github.com/AntonioCastilho>
 * ****************************************************************************
 * Reference:
 * * Microchip PIC18F4550 Datasheet.
 * ****************************************************************************
 * Date          | Author                | Description
 * ****** ***|******* *******|***************************************************
 * 05/09/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/ 

#ifndef STEPPER_MOTOR_H
#define	STEPPER_MOTOR_H

#include <xc.h>

#define COIL_1A       LATBbits.LATB7
#define COIL_1B       LATBbits.LATB6

#define COIL_2A       LATBbits.LATB5
#define COIL_2B       LATBbits.LATB4

#endif	/* STEPPER_MOTOR_H */

