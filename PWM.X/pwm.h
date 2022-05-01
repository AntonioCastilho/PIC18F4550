/* ****************************************************************************
 * Project: Basic control functions       File pwm.h                 March/2022
 * ****************************************************************************
 * Description: PIC 18F4550 CCP module configuration to obtain PWM signal. 
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
 
#ifndef PWM_H
#define	PWM_H

#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#define TMR2PRESCALE            16
#define PWM1_FREQUENCY       10000 // 1000,0 Hz
#define DUTY_CYCLE             500 // 50,0 %

#ifndef _XTAL_FREQ
    #define	_XTAL_FREQ   8000000  // Standard, Internal Oscillator 8 MHz,
    // OSCCON Oscillator control register Pg. 34.
#endif
#ifndef TMR2PRESCALE
        #define	TMR2PRESCALE    16
#endif
#ifndef DUTY_CYCLE
    #define	DUTY_CYCLE    500  // Default for Duty Cycle PWM1 = 50.0%.
#endif
#ifndef PWM1_FREQUENCY
    #define	PWM1_FREQUENCY  10000 // Default for PWM1 Frequency = 1000.0 Hz.
#endif

// Function prototypes
void pwm1_ini(void);
void pwm1_setDutyPot(uint16_t ccpr1_aux);

#endif	/* PWM_H */

