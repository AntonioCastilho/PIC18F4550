/* Program: Timer Setup     File: timer_tester.c     
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 * Description:
 *      This program tests the TIMER settings.
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/22/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

#include <xc.h>
#include "timer.h"
#include "fuse_bits.h"
#include "lcd.h"

void main(void) 
{
    uint8_t tmer0_l = 0;
    uint8_t tmer0_h = 0;

    lcd_wellcome();
    
    OSCCON = 0xFF; // Set to Internal Oscillator 8 MHz. 
                             // See also the fuse_bits.h (#pragma config FOSC = INTOSC_HS)
    ADCON1bits.PCFG = 0b0111; // Disables analog ports (AN8:AN12) from PORT B pins (RB0:RB4). Pg 262.
                                                // To use port B pins, along with TIMER3 which is associated with CCP
    TRISBbits.TRISB7 = 0; // Set as digital output. To check the operation of TIMER0.
    LATBbits.LATB7 = 1; // Turn the LED7 of FATEC board as off.
    TRISBbits.TRISB6 = 0; // Set as digital output. To check the operation of TIMER1.
    LATBbits.LATB6 = 1; // Turn the LED6 of FATEC board as off.
    TRISBbits.TRISB5 = 0; // Set as digital output. To check the operation of TIMER2.
    LATBbits.LATB5 = 1; // Turn the LED6 of FATEC board as off.
    TRISBbits.TRISB4 = 0; // Set as digital output. To check the operation of TIMER3.
    LATBbits.LATB4 = 1; // Turn the LED6 of FATEC board as off.    
    
    timer0_ini(); // Set TIMER0 
    timer1_ini(); // Set Timer1
    timer2_ini(); // Set Timer2
    timer3_ini();
    
    while(1)
    {
        if(INTCONbits.TMR0IF == 1)
        {
            LATBbits.LATB7 = (uint8_t)(~PORTBbits.RB7);
            INTCONbits.TMR0IF = 0; // the TMR0IF bit must be cleared in software; pg 129.
            timer0_write(3035);  // 0x; Loads the Timer preload value to 500 ms.
            
            /* An overflow (TMR0IF = 1) will be generated every 500 ms. As the LED will change 
             * state every TMR0IF, it will be 500 ms on and 500 ms off. Therefore, a frequency 
             * of 1 Hz with a period of 1 s.
             */
        }
        
        if(PIR1bits.TMR1IF == 1)
        {
            LATBbits.LATB6 = (uint8_t)(~PORTBbits.RB6);
            PIR1bits.TMR1IF = 0;
            timer1_write(3035);  // 0x0BDB; Loads the Timer preload value to 125 ms.            
            /* The LED will change state every 125 ms. Frequency 4 Hz. Period 250 ms. */
        }
        
        if(PIR1bits.TMR2IF == 1)
        {
            LATBbits.LATB5 = (uint8_t)(~PORTBbits.RB5);
            PIR1bits.TMR2IF = 0; 
            timer2_write(130);  // 0x0BDB; Loads the Timer preload value to 1 ms.
            /* Frequency 500 Hz, Period 2 ms*/
        }
        
         if(PIR2bits.TMR3IF == 1)
        {
            LATBbits.LATB4 = (uint8_t)(~PORTBbits.RB4);
            PIR2bits.TMR3IF = 0; // the TMR0IF bit must be cleared in software; pg 129.
            timer3_write(3035);  // 0x; Loads the Timer preload value to 250 ms.
            /* Frequency 2 Hz, Period 500 ms*/
        }
        
        // TODO Implement interrupts to verify TIMER operation
    }
}
