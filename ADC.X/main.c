/* ****************************************************************************
 * Project: Basic control functions       File main.c                March/2022
 * ****************************************************************************
 * Description: Example of validation in a simple system, of the codes for the 
 * LCD Display interface and ADC module. The objective is to show on the LCD 
 * the voltage between 0 and 5V, obtained in a voltage divider with a 
 * potentiometer and read on channel 0 of the ADC module.
 * Voltage is obtained with precision of 2 digits after the decimal point, 
 * without using float variables.
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
 * 04/17/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/

#include <xc.h>
#include "main.h"

void main(void) 
{
    // variables
    uint16_t value_an0 = 0;
    uint16_t voltage = 0;
    uint16_t volt_prev = 0;
    uint8_t volt_int = 0;
    uint8_t volt_dec = 0;
    uint8_t col = 0;
    lcd_ini(); // Configure and Start LCD Display.
    adc_ini(); // Configure and start ADC module.
    // Initial message on display.
    lcd_prtStr(1,0,"Bem vindo!      "); lcd_prtStr(2,0,"Exemplo LCD-ADC ");
    __delay_ms(3000); 
    lcd_prtStr(1,0,"Wellcome!       "); lcd_prtStr(2,0,"LCD-ADC example ");
    __delay_ms(3000);     
    lcd_clear(); // Clear Display
    lcd_cursorOff(); // turn off the cursor.
    lcd_prtStr(0,0,"Tensao: Voltage:");
    while(1)
    {
        value_an0 = adc_read(0); // Reads channel 0, connected to a voltage divider.
        // Gets the voltage value, in 10-bit resolution. Observing precision 
        // of 2 places after the decimal point.
        voltage = (uint16_t)((((float)value_an0 * 5)/1023)*100);
        if(voltage != volt_prev)
        {
            lcd_prtStr(2,0,"                ");
            volt_prev = voltage;
            // Gets the integer part of the value.
            volt_int = (uint8_t)((float)voltage/100);
            // Get the fractional part.
            volt_dec = (uint8_t)((((float)voltage/100)-volt_int)*100); 
            lcd_prtInt(2,col,volt_int); // show integer part on lcd display.
            // correct the position.
            col = (uint8_t)(col + digit_counter(volt_int) + 1); 
            lcd_prtStr(2,col,","); // Place the comma or decimal point.
            col += 1;
            lcd_prtInt(2,col,volt_dec); // show fractional part on lcd display.
            col = 0;
        }
        __delay_ms(1000);
        // TODO: Implement the routine in a function and call it by a task, 
        // at predetermined times.
        
    }
}
// TODO: Get an average of a number of readings to show voltage.