/* Program: Timer Setups     File: timer.c     
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 *                      Internal oscillator 8 MHz;
 * Description:
 *    This file contains functions for setting TIMER0, TIMER1, TIMER2 and TIMER3 of PIC18F4550, as a counter
 *    The TIMER increment occurs at each machine clock period (_XTAL_FREQ/4), on the rise or fall (selectable).
 *    The PIC18F4550 Microcontrollers execute an instruction cycle (period) every 4 clock cycles.
 * 
 *     Formulas for calculating the starting count needed to obtain the desired time:
 *              Timer frequency:
 *                          Fcy = Ftimer = ( _XTAL_FREQ / 4 );                Ex.: 8000000/4 = 2000000 Hz.
 * 
 *              If Prescaler enable: (Prescaler Value  != 1)
 *                  The Prescaler value must be chosen to allow a counter value less than the maximum resolution
 *                  of the TIMER. (Resolution >= Counter).
 *                  To not use the Prescaler, or Postscaler (only TIMER2), just select value 1. For TIMER0 it is 
 *                  possible to turn the Prescaler on and off in the bit: (T0CONbits.PSA = 0).
 *                          Ftimer = (( _XTAL_FREQ / 4 ) / Prescale);       Ex.: 8000000 / 4 * 32= 62500 Hz;
 * 
 *              Else: 
 *                          Ftimer = ( _XTAL_FREQ / 4 ) / 1;                   Ex.: 8000000 / 4 * 1= 2000000 Hz;
 * 
 *              Period:
 *                  Ttimer = ( 1 / Ftimer ); Ex.: (1/62500) = 1.6 E-5; 16 us; The TIMER will take 16 us to increment;
 *                  Tcy = 4 * (1/_XTAL_FREQ) = Ttimer;  TCY ? Time of Instruction Cycle)
 * 
 *              For a desired period (T) of 1 s (1000 ms):
 *                  Count = ( T / Ttimer ); Ex.: 1 / 16 us = 62500; (0xF424); 
 * 
 *              Value to be filled in the 16-bit Timer register:
 *                  TMRx = ( 65535 - Count ); Ex.: 65535 - 62500 = 3035; 0xFFFF - 0xF424 = 0x0BDB;
 * 
 *              TMRx = ResolutionMax - ((_XTAL_FREQ * T ) / ( 4 * Prescale ));
 * 
 *              Where:
 *                          Fcy or Ftimer - Instruction Cycle Frequency
 *                          Tcy or Ttimer - Instruction Cycle Time
 *                          Count - Count to start TIMER
 *                          TMRx - Value that must be ignored before starting the count in TIMER
 *                          _XTAL_FREQ - Oscillator frequency
 * 
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/22/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

#include <xc.h>
#include "timer.h"

/****************************************************************************************
 * void timer0_ini(void); 
 * Configure registers to start TIMER 0. There are no inputs or outputs.
 * 8-bit; resolution 2^8 - 1 = 255; T08BIT = 0
 * 16-bit; resolution 2^16 - 1 = 65535; T08BIT = 1
 * Overflow flag: INTCONbits.TMR0IF = 1.
 * Timer0 Interrupt: INTCONbits.TMR0IE = 1.
 * To use interrupt you must also set other bits in INTCON and INTCON2.
 ****************************************************************************************/
void timer0_ini(void)
{
    // T0CON = 0xC2; // Configuration TIMER0, pg. 127.
    T0CONbits.TMR0ON = 0; // turn off timer0 to start setup; 1 = Enables Timer0; 
                                         //                                             0 = Stops Timer0;
    T0CONbits.T08BIT = 0;  // 1 = Timer0 is configured as an 8-bit timer/counter
                                         // 0 = Timer0 is configured as a 16-bit timer/counter
    T0CONbits.T0CS = 0;     // 1 = Transition on T0CKI pin
                                        // 0 = Internal instruction cycle clock (CLKO)
    T0CONbits.T0SE = 0;     // 1 = Increment on high-to-low transition on T0CKI pin
                                        // 0 = Increment on low-to-high transition on T0CKI pin
    T0CONbits.PSA = 0;       // 1 = TImer0 prescaler IS NOT ASSIGNED. Timer0 clock input bypasses prescaler
                                        // 0 = Timer0 prescaler IS ASSIGNED. Timer0 clock input comes from prescaler output
    T0CONbits.T0PS2 = 0;   // |  1   |  1    | 1   |  1  |  0 | 0 | 0 | 0 |
    T0CONbits.T0PS1 = 1;   // |  1   |  1    | 0   |  0  |  1 | 1 | 0 | 0 |
    T0CONbits.T0PS0 = 1;   // |  1   |  0    | 1   |  0  |  1 | 0 | 1 | 0 |
                  // Prescale value: | 256 | 128 | 64 | 32 | 16 | 8 | 4 | 2 |   
    
     T0CONbits.TMR0ON = 1; // turn on timer0.
    
    TMR0L = 0;
    TMR0H = 0;
    
     // uint16_t timer_value = ResolutionMax - ((_XTAL_FREQ * T ) / ( 4 * Prescale ));
     timer0_write(3035);  // 0x; Loads the Timer preload value to 500 ms.
   
}
// end of void timer0_ini(void)

/****************************************************************************************
 * void timer0_write(uint16_t timer_value);
 * This function writes the value of registers to get the TIMER0 overflow.
 * Receives the value to be written.
 ****************************************************************************************/
void timer0_write(uint16_t timer_value)
{
    TMR0L = (timer_value & 0x00FF);
    TMR0H = (timer_value >> 8) & 0x00FF;
}
// end of void timer0_write(uint16_t timer_value)

/****************************************************************************************
 * void timer1_ini(void)
 * Configure registers to start TIMER 1. There are no inputs or outputs.
 * 8-bit; resolution 2^8 = 256; RD16 = 0;
 * 16-bit; resolution 2^16 = 65536; RD16 = 1;
****************************************************************************************/
void timer1_ini(void)
{
     T1CONbits.TMR1ON = 0; // turn off timer1 to start setup.
    //T1CON = 0x91; // Configuration TIMER1, Pg 131.
    T1CONbits.RD16 = 1; // 1 = Enables register read/write of Timer1 in one 16-bit operations
                                    // 0 = Enables register read/write of Timer1 in two 8-bit operations
    T1CONbits.T1RUN = 1; // 1 = Device clock is derived from Timer1 oscillator
                                      // 0 = Device clock is derived from another source
    
    T1CONbits.T1CKPS1 = 1; // | 1 | 1 | 0 | 0 |
    T1CONbits.T1CKPS0 = 0; // | 1 | 0 | 1 | 0 |
                     // Prescale value: | 8 | 4 | 2 | 1 |
    
    T1CONbits.T1OSCEN = 1; // 1 = Timer1 oscillator is enabled
                                           // 0 = Timer1 oscillator is shut off
    T1CONbits.T1SYNC = 1; // 1 = Do not synchronize external clock input
                                        // 0 = Synchronize external clock input
    T1CONbits.TMR1CS = 0; // 1 = External clock from RC0/T1OSO/T13CKI pin (on the rising edge)
                                         // 0 = Internal clock (FOSC/4)
    T1CONbits.TMR1ON = 1; // 1 = Enables Timer1
                                         // 0 = Stops Timer1
    TMR1L = 0;
    TMR1H = 0;
    
    // uint16_t timer_value = ResolutionMax - ((_XTAL_FREQ * T ) / ( 4 * Prescale ));
    timer1_write(3035); // 0xF060- Loads the Timer preload value to 250 ms.
}
// end of void timer1_ini(void)

/****************************************************************************************
 * void timer1_write(uint16_t timer_value);
 * This function writes the value of registers to get the TIMER1 overflow.
 * Receives the value to be written.
 ****************************************************************************************/
void timer1_write(uint16_t timer_value)
{
    TMR1L = (timer_value & 0x00FF);
    TMR1H = (timer_value >> 8) & 0x00FF;
} 
// end of void timer1_write(uint16_t timer_value)

/******************************************************************************
 * void timer2_ini(void);
 * Configure registers to start TIMER 2. There are no inputs or outputs.
 * 8-bit; resolution 2^8 -1 = 255;
*****************************************************************************/
void timer2_ini()
{
    T2CONbits.TMR2ON = 0; // turn off timer2 to start setup.
    // T2CON = 0x06; // Configuration TIMER2, pg 137.
    T2CONbits.T2OUTPS3 = 0; // |  1  | 1  | 1   | 1   | 1   | 1  | 1   | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    T2CONbits.T2OUTPS2 = 0; // |  1  | 1  | 1   | 1   | 0   | 0  | 0   | 0 | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
    T2CONbits.T2OUTPS1 = 1; // |  1  | 1  | 0   | 0   | 1   | 1  | 0   | 0 | 1 | 1 | 0 | 0 | 1 | 1 | 0 | 0 |
    T2CONbits.T2OUTPS0 = 1; // |  1  | 0  | 1   | 0   | 1   | 0  | 1   | 0 | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |
                     // Postscale value: | 16 | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |

    T2CONbits.T2CKPS1 = 0; //  | 0 | 0 |  1  |
    T2CONbits.T2CKPS0 = 1; //  | 0 | 1 |  x  |
                      // Prescale value: | 1 | 4 | 16 |
    
    T2CONbits.TMR2ON = 1; // 1 = Timer2 is on
                                         // 0 = Timer2 is off
    
    TMR2 = 0; 
    // uint16_t timer_value = ResolutionMax - ((_XTAL_FREQ * T ) / ( 4 * Prescale * Postscale));
    timer2_write(130); // 0x83 - Loads the Timer preload value to 1 ms.
}
// end of void timer2_ini().

/****************************************************************************************
 * void timer2_write(uint16_t timer_value);
 * This function writes the value of registers to get the TIMER2 overflow.
 * Receives the value to be written.
 ****************************************************************************************/
void timer2_write(uint16_t timer_value)
{
    PR2 = timer_value;
}
// end of void timer2_write(uint16_t timer_value)

/****************************************************************************************
 * void timer3_ini(void)
 * Configure registers to start TIMER3. There are no inputs or outputs.
 * 8-bit; resolution 2^8 = 256; RD16 = 0;
 * 16-bit; resolution 2^16 = 65536; RD16 = 1;
****************************************************************************************/
void timer3_ini()
{
    T3CONbits.TMR3ON = 0; // turn off timer3 to start setup.
    // Timer 3 configuration. Pg 139.
    T3CONbits.RD16 = 1; // 1 = Enables register read/write of Timer3 in one 16-bit operation
                                    // 0 = Enables register read/write of Timer3 in two 8-bit operations
    
    T3CONbits.T3CCP2 = 0; // 1x = Timer3 is the capture/compare clock source for both CCP modules
    T3CONbits.T3CCP1 = 0; // 01 = Timer3 is the capture/compare clock source for CCP2;
                                        //         Timer1 is the capture/compare clock source for CCP1
                                        // 00 = Timer1 is the capture/compare clock source for both CCP modules
    
    T3CONbits.T3CKPS1 = 1; // | 1 | 1 | 0 | 0 |
    T3CONbits.T3CKPS0 = 1; // | 1 | 0 | 1 | 0 |
                   // Prescale value: | 8 | 4 | 2 | 1 |
    
    T3CONbits.T3NSYNC = 1; // 1 = Do not synchronize external clock input
                                           // 0 = Synchronize external clock input
    T3CONbits.TMR3CS = 0;  // 1 = External clock input from Timer1 oscillator or T13CKI (pin 15 RC0); counter mode.
                                          // 0 = Internal clock (FOSC/4); timer mode.
    T3CONbits.TMR3ON = 1; // 1 = Enables Timer3
                                         // 0 = Stops Timer3
    
    TMR3L = 0;
    TMR3H = 0;
     // uint16_t timer_value = ResolutionMax - ((_XTAL_FREQ * T ) / ( 4 * Prescale ));
    timer3_write(3035); // 0xFF82 - Loads the Timer preload value to 250 ms.
}
// end of void timer3_ini().

/****************************************************************************************
 * void timer3_write(uint16_t timer_value);
 * This function writes the value of registers to get the TIMER3 overflow.
 * Receives the value to be written.
 ****************************************************************************************/
void timer3_write(uint16_t timer_value)
{
    TMR3L = (timer_value & 0x00FF);
    TMR3H = (timer_value >> 8) & 0x00FF;
}
// end of void timer3_write(uint16_t timer_value)
