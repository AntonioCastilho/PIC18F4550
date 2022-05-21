/* ****************************************************************************
 * Project: Control Functions             File stepper_motor.c                Maio/2022
 * ****************************************************************************
 * File description: Initial study for the use in controls of stepper motors and DC motors. 
 *                         (MOSFET DRIVER).      
 * ****************************************************************************
 * Program environment for validation: MPLAB X IDE v6.0, XC8 v2.36, C std C90,
 * PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal.
 * IRFZ44N N-channel MOSFET transistor.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho <https://github.com/AntonioCastilho>
 * ****************************************************************************
 * Reference:
 * * Microchip PIC18F4550 Datasheet.
 * ****************************************************************************
 * Date           | Author                | Description
 * **********|************* *|***************************************************
 * 05/13/2022 | Antonio Castilho  | Function has been created
 ******************************************************************************/ 

/* In development. Initial studies of the elementary functions that will be used.*/

#include <xc.h>
#include "fuse_bits.h"
#include "hdw_map.h"
#include "stepper_motor.h"
#include "adc.h"
#include "lcd.h"

void main(void)
{
    adc_ini(); // Configure ADC module (Releasing PORTB).
    lcd_wellcome();
    
    uint8_t btn1_flag = OFF; // this variable indicates that the button 1 was pressed.
    uint8_t btn2_flag = OFF; // this variable indicates that the button 2 was pressed.
    uint8_t btn3_flag = OFF; // this variable indicates that the button 3 was pressed.
    uint8_t mode_full = TRUE;
    
    // I/O sets
    TRISE = INPUT; // Button 1, 2 and 3 - I/O.
    TRISB = OUTPUT; // Configure PORTB for digital output.
    LATB = 0xFF;
    TRISE = 0xFF; // See page: 126 of PIC18f450 datasheet.
    
    COIL_1A = 0; // Lilas
    COIL_1B = 0; // Marrom
    COIL_2A = 0; // Cinza
    COIL_2B = 0; // Azul
    
    // Backward step: {COIL_1A, COIL_2B, COIL_1B, COIL_2A}
    // Forward {COIL_1A, COIL_2A, COIL_1B, COIL_2B]
   
    while(1)
    {
        // Backward - Nissan CVT stepper motor
        if(BTN_1 == PRESSED)  btn1_flag = ON; // Button pressed set flag
        if(BTN_1 == UNPRESSED && btn1_flag == ON && mode_full == TRUE) // when release button execute commands
        {
            COIL_1A = ON; // Lilas
            __delay_ms(500);
            COIL_1A = OFF; // Lilas
             __delay_ms(500);
            COIL_2B = ON; // Azul
             __delay_ms(500);
            COIL_2B = OFF; // Azul
             __delay_ms(500);
            COIL_1B = ON; // Marrom
             __delay_ms(500);
            COIL_1B = OFF; // Marrom
             __delay_ms(500);
            COIL_2A = ON; // Cinza
             __delay_ms(500);
            COIL_2A = OFF; // Cinza
             __delay_ms(500);
            btn1_flag = OFF; // return to initial condition for acquisition of other presses.
        }
        
        // Forward - Nissan CVT stepper motor
        if(BTN_2 == PRESSED)  btn2_flag = ON; // Button pressed set flag
        if(BTN_2 == UNPRESSED && btn2_flag == ON) // when release button execute commands
        {
            COIL_1A = ON; // Lilas
            __delay_ms(500);
            COIL_1A = OFF; // Lilas
             __delay_ms(500);
            COIL_2A = ON; // Cinza
             __delay_ms(500);
            COIL_2A = OFF; // Cinza
             __delay_ms(500);
            COIL_1B = ON; // Marrom
             __delay_ms(500);
            COIL_1B = OFF; // Marrom
             __delay_ms(500);
            COIL_2B = ON; // Azul
             __delay_ms(500);
            COIL_2B = OFF; // Azul
             __delay_ms(500);
            btn2_flag = OFF; // return to initial condition for acquisition of other presses.
        }
        
        if(BTN_3 == PRESSED)  btn3_flag = ON; // Button pressed set flag
        if(BTN_3 == UNPRESSED && btn3_flag == ON) // when release button execute commands
        {
            mode_full = (uint8_t)~mode_full;
            LATBbits.LATB0 = ~PORTBbits.RB0; // Forward (clockwise disable.)
            btn3_flag = OFF; // return to initial condition for acquisition of other presses.
            btn1_flag = OFF; // return to initial condition for acquisition of other presses.
        }
        // TODO PID stepper motor control.
        
    } // end while
} // end main