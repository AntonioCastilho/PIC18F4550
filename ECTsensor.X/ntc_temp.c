/* Program: ECT Sensor Tester     File: ntc_temp.c     
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 * Description:
 *      This program tests the functions for temperature reading with an automotive type ntc sensor.
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/26/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

#include <xc.h>
#include <math.h>
#include "fuse_bits.h"
#include "hdw_map.h" // Hardware mapping considering the FATEC Board.
#include "lcd.h"
#include "adc.h"
#include "ntc.h"

void main(void)
{
    TRISBbits.TRISB7 = OUTPUT;
    LED_7 = 1; // Led off.
    
    uint16_t temp = 0;
    uint16_t value_readCH = 0;
    uint16_t temp_previous = 0;
    uint8_t temp_int = 0;
    uint8_t temp_dec = 0;
    uint8_t col = 7;
    adc_ini(); // Initializes the ADC module.
    __delay_ms(50);
    lcd_wellcome(); // Initializes the LCD display and writes the welcome message.
    __delay_ms(5000); // Wait for the message to be read.
    
    lcd_prtStr(1,0,"Temp.:       'C   ");
    
    while(1)
    {
        temp = ntc_get(pinNTC);
        
        if(temp != temp_previous)
        {
            LED_7 = (uint8_t)(~LED_7); // Notice of reread on the ADC channel
            
            temp_previous =  temp;
            
            // Gets the integer part of the temperature value.
            temp_int = (uint8_t)((float)temp/100);
            // Get the fractional part.
            temp_dec = (uint8_t)((((float)temp/100)  - (float)temp_int)*100);
        
            lcd_prtInt(1,col,temp_int); // show integer part on lcd display.
            // correct the position.
            col = (uint8_t)(col + digit_counter(temp_int)+1); 
            lcd_prtStr(1,col,","); // Place the comma or decimal point.
            col += 1;
            lcd_prtInt(1,col,temp_dec); // show fractional part on lcd display.
            col = 7;
        }
        __delay_ms(500); //Take a new reading every 0.5 s.
        LED_7 = 1; // Led off.
        
        // TODO Do this function on an RTOS system.
     }
}
