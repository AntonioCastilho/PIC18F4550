/* ****************************************************************************
 * Project: Control Functions             File stepper_motor.c                Maio/2022
 * ****************************************************************************
 * File description: Initial study for the use of buttons with attenuation of the switch-bouncing 
 *                         effect in software, for use in controls of stepper motors and DC motors. 
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
#include "adc.h"
#include "lcd.h"

void main(void)
{
    adc_ini(); // Configure ADC module (Releasing PORTB).
    lcd_wellcome();
    uint8_t btn1_flag = OFF; // this variable indicates that the button was pressed.
    TRISE = INPUT; // Button 1, 2 and 3 - I/O.
    TRISBbits.TRISB7 = OUTPUT; // LED 7 of FATEC board. 
    LATBbits.LATB7 = OFF; // FATEC board LEDs are in pull-up. So to turn on send 0, to turn off send 1.
    
    while(1)
    {
        if(BTN_1 == PRESSED)  btn1_flag = ON; // Button pressed set flag

        if(BTN_1 == UNPRESSED && btn1_flag == ON) // when release button execute commands
        {
            LED_7 = (uint8_t)(~LED_7);   //Changes the state of the FATEC board LED and can apply voltage 
                                                       // to the transistor gate (MOSFET DRIVER).
            btn1_flag = OFF; // return to initial condition for acquisition of other presses.
        }
        
    } // end while
} // end main