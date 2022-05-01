/* Program: ECT Sensor     File: ntc.c     
 * Environment: MPLAB X IDE v6.00; XC8 v2.36; Std C C90; PIC18F4550 on FATEC board;
 * Description:
 *          Functions related to obtaining temperature through NTC thermistors.
 *          Iguaçu NTC Thermistor 201.0805 <www.iguacu.com.br>.
 * 
 *  MIT License  (see: LICENSE em github)   <https://github.com/AntonioCastilho>
 * Copyright (c) 2022 Antonio Aparecido Ariza Castilho
 * _______________________________________________________________________________________
 * Date:          | Author:               | Description:                                                             | Version:
 * 04/25/2022 | Antonio Castilho  | Created                                                                    | 00.00.01
 *________________________________________________________________________________________
 */

/****************************************************************************************
 * Function: uint16_t ntc_get(uint8_t ch)
 * ***************************************************************************************
 * The ntc_get() function reads the specified channel where the NTC thermistor is connected with the 
 * adc_read() function and converts the value into temperature in degrees Celsius. Range from 0 to 100.00 'C . 
 * To convert the value, the Beta Formula is applied, which uses a material coefficient, which can be obtained 
 * through measurements. In a table, kindly provided by the sensor manufacturer, it is possible to obtain the 
 * values of temperature x resistance, and thus define values of the constants of the formula.
 *
 *                       resistor_ntc = r0 * e^(beta*(1/temperature-1/r0))
 * Where:
 *              temperature - temperature being read.
 *              resistor_ntc - is the resistance at the temperature (in Kelvin) being read.
 *              r0 - is the reference resistance at temperature t0.
 *              beta - single material constant.
 * 
 * The beta value was obtained by analyzing various information in the NTC thermistor data sheets and 
 * running experiments directly with the component.
 * In this version of the program the values were declared as constants in the ntc.h file.
 * ***************************************************************************************
 * Input: Channel where the NTC Thermistor sensor is connected.
 * Output: Void. 
 ****************************************************************************************/

#include <xc.h>
#include "ntc.h"

uint16_t ntc_get(uint8_t ch)
{
    uint16_t average = 0; // Measurement average.
    uint16_t temperature = 0; // Temperature being read.
    uint16_t resistor_ntc = 0; // Is the resistance at the temperature being read.
    uint16_t voltage = 0; // Voltage obtained on the ADC channel.
    
    for(uint8_t i = 0; i < n_sample; i++)
    {
        average += adc_read(ch); // Makes an amount of ADC channel measurements specified in ntc.h.
        __delay_ms(10);
    }
    // Calculate the voltage.
    voltage = (uint16_t)round( ( ( (float)VCC *  ((float)average/(float)n_sample) ) / 1023.0 ) *100 );
    // Calculates resistance on NTC thermistor.
    resistor_ntc = (uint16_t)round(((float)voltage/100.0) * ((float)r_ref / ((float)VCC - ((float)voltage/100.0 ))));
    // Calculates temperature using Formula Beta and constants defined in ntc.h.
    temperature = (uint16_t)round(( ( (float)beta / log( ((float)resistor_ntc) / (float)rx ) ) - 273.15 ) *100 );
    // Returns the temperature value accurately to two decimal places. cd.dc.
    return temperature;
    
    // TODO Take this function to an RTOS system.
    // TODO Enlarge range to mdc.dc (0 to 1000.00).
    // TODO Develop other functions to use with NTC thermistor.
}