/* ****************************************************************************
 * Project: Basic control functions       File main.c                March/2022
 * ****************************************************************************
 * Description:  
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
#include "main.h"

void main(void) 
{
    pwm1_ini();
    __delay_ms(1000);
    
    while(1)
    {

    }
}
