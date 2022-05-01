/* ****************************************************************************
 * Project: Basic control functions       File pwm.c                 March/2022
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

#include <xc.h>
#include "pwm.h"

/******************************************************************************
 * Function: void pwm1_ini(void)
 * Description: Initializes the CCP module's pwm after setting the desired 
 * PWM frequency and TIMER 2 Prescaler. The PIC oscillator must be chosen 
 * according to the frequency and period and set in the bits of the 
 * OSCCON register.
 * Input: void
 * Output: void
 * ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 03/23/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/
void pwm1_ini(void)
{
    // Oscillator frequency setting.
    // OSCCON Oscillator control register Pg 34.
    OSCCONbits.IDLEN = 0; // Sleep mode
    OSCCONbits.IRCF2 = 1; // |Internal oscillator frequency, 3 bits.
    OSCCONbits.IRCF1 = 1; // |Change the _XTAL_FREQ
    OSCCONbits.IRCF0 = 1; // |8 MHz 
    OSCCONbits.OSTS  = 0; // Status bit for timer time-out.
    OSCCONbits.IOFS  = 0; // Frequency Stable bit.
    OSCCONbits.SCS1 =  1; // |System Clock select bit 2 bits
    OSCCONbits.SCS0 =  0; // |00 = Internal oscillator
    TRISCbits.RC2 = 0;// Configure pin RC2 as output for PWM 1.
    // Starts the TIMER 2 module. Pg 137.
    #if TMR2PRESCALE == 1
           T2CON = 0X00; // Prescale 1. Postscale 1:1.
    #elif TMR2PRESCALE == 4
           T2CON = 0X01; // Prescale 1. Postscale 1:4.
    #elif TMR2PRESCALE == 16
           T2CON = 0X03; // Prescale 1. Postscale 1:16.
    #endif
    T2CONbits.TMR2ON = ON;  // Turn on Timer 2.     
    TMR2 = 0; // Initializes TMR2.
    // Initializes module CCP1. page 151.
    CCP1CON = 0X0C; // PWM mode: P1A, P1C active-high; P1B, P1D active-high.
    // Configure the PS2 of PWM1, to control the frequency and period of PWM1.
    uint8_t pr_var = (uint8_t)(round(((float)(_XTAL_FREQ)/
            ((float)(PWM1_FREQUENCY/10.0)*4.0*(float)TMR2PRESCALE))-1.0));
    PR2 = pr_var;
    // Configures Registers to control the PWM1's Duty Cycle.
    uint16_t cycle = (uint16_t)(round(((((float)DUTY_CYCLE)/
            1000.0)*4.0*((float)(pr_var)+1.0)))); // Calculates value for CCPRL.
    CCP1CONbits.DC1B0 = cycle; // Bit Lsb
    CCP1CONbits.DC1B1 = cycle >> 1; // Bit LSb
    CCPR1L = cycle >> 2; // Bit Msb.
}
// end of function void pwm1_ini(void)
/******************************************************************************/
/******************************************************************************
 * Function: void pwm1_setDutyPot(uint16_t ccpr1_aux)
 * Description: This function configures the Duty Cycle from a variable 
 * that can be dynamically modified by a potentiometer, for example.
 * Input: uint16_t ccpr1_aux (value 0 - 1023)
 * Output: void
 * ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 03/23/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/

void pwm1_setDutyPot(uint16_t ccpr1_aux)
{
    CCP1CONbits.DC1B0 = ccpr1_aux; // Bit 0 - Lsb
    CCP1CONbits.DC1B1 = ccpr1_aux >> 1; // Bit 1 - Lsb
    CCPR1L = ccpr1_aux >> 2; // Bit 8 - Msb.
}
/******************************************************************************/

