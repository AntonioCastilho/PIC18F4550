/* ****************************************************************************
 * Project: Control Functions                      File project_constants.c                          March/2022
 * ****************************************************************************
 * File description: Constant definitions and hardware mapping.
 *      
 * ****************************************************************************
 * Program environment for validation:
 *   MPLAB X IDE v6.0, XC8 v2.36, C std C90;
 *   PIC18F4550 mounted on FATEC development board (FATEC board) - 20 MHz crystal;
 *   Can Bus Module MCP2515 x TJA1050.
 * ****************************************************************************
 * MIT License  (see: LICENSE em github)
 *   Copyright (c) 2022 Antonio Aparecido Ariza Castilho <https://github.com/AntonioCastilho>
 * ****************************************************************************
 * Reference:
 *   Microchip PIC18F4550 Datasheet;
 *   Microchip MCP2515 Datasheet;
 *   MCP2515 Code examples: <https://microchipdeveloper.com/faq:2720>.
 * ****************************************************************************
 * Date           | Author                | Description
 * **********|************* *|***************************************************
 * 03/12/2022 | Antonio Castilho  | Function has been created
 ******************************************************************************/ 
#ifndef PROJECT_CONSTANTS_H
#define	PROJECT_CONSTANTS_H

/******************************************************************************/
// Include header files.
/******************************************************************************/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdlib.h> // Basic functions and constants. Type conversion etc.
/******************************************************************************/

/******************************************************************************/
// Project constants.
/******************************************************************************/
#define INPUT               1
#define OUTPUT            0
#define HIGH                1
#define LOW                 0
#define YES                  1
#define NO                    0
#define ON                    1
#define OFF                   0
#define ENABLE             1
#define DISABLE           0
#define TRUE                1
#define FALSE               0
#define not                 !=
#define and                 &&
#define or                    ||

#define FOSC                48000000 // USB and CPU core clock source
#define CLOCK_INSTRUCTION   (FOSC/4) // Instruction clock and peripheral clock
#define TCY                 (4 * 1/FOSC) // CPU time to execute an instruction.

#define _XTAL_FREQ         48000000  // used for delay functions of XC8.



/******************************************************************************/

/******************************************************************************/
// PORT A - Analog Pins & SPI in RA5
/******************************************************************************/
#define CH00           PORTAbits.AN0
#define CH01           PORTAbits.AN1
#define CH02           PORTAbits.AN2
#define CH03           PORTAbits.AN3
// PORTAbits.AN4 free to use
#define CS              PORTAbits.RA5
// PORTAbits.AN6 free to use
// PORTAbits.AN7 free to use
// PORTAbits.AN8 free to use
/******************************************************************************/
// PORT B - LEDS & SPI
/******************************************************************************/
#define SDI            PORTBbits.RB0 // & LED1. Equivalent to the LD2 of the IC.
#define SCK           PORTBbits.RB1 // & LED2. Equivalent to the LD3 of the IC.
#define MCP_INT     PORTBbits.RB2 // & LED3. Equivalent to the LD4 of the IC.
#define LED4          PORTBbits.RB3 // Equivalent to the LD5 of the IC.
#define LED5          PORTBbits.RB4 // Equivalent to the LD6 of the IC.
#define LED6          PORTBbits.RB5 // Equivalent to the LD7 of the IC.
#define LED7          PORTBbits.RB6 // Equivalent to the LD8 of the IC.
#define LED8          PORTBbits.RB7 // Equivalent to the LD9 of the IC.
/******************************************************************************/
// PORT C - Output PWM & USB & SPI in RC7
/******************************************************************************/
//                                PORTCbits.RC0
#define PWM2_OUT      PORTCbits.RC1
#define PWM1_OUT      PORTCbits.RC2
// the RC3 pin is not implemented in PIC18F4550.
#define USB2              PORTCbits.RC4
#define USB3              PORTCbits.RC5
// PORTCbits.RC6 free to use
#define SDO               PORTCbits.RC7

/******************************************************************************/
// PORT D - 4-bit interface with LCD Display.
/******************************************************************************/
#define LCD_E            PORTDbits.RD0 
#define LCD_RS          PORTDbits.RD1
#define LCD_RW         PORTDbits.RD2
// PORTDbits.RD3 free to use
#define LCD_D4         PORTDbits.RD4
#define LCD_D5         PORTDbits.RD5
#define LCD_D6         PORTDbits.RD6
#define LCD_D7         PORTDbits.RD4
/******************************************************************************/
// PORT E - Switch Pins 
/******************************************************************************/
#define BTN_1             PORTEbits.RE0
#define BTN_2             PORTEbits.RE1
#define BTN_3             PORTEbits.RE2
#define BTN_RESET     PORTEbits.RE3
/******************************************************************************/

/******************************************************************************/
// Function prototypes
/******************************************************************************/
void delay_rms(uint16_t value); // Delay calibrated with timer1
uint8_t digit_counter(const int32_t number);
/******************************************************************************/
#endif	/* PROJECT_CONSTANTS_H */


/* Summary of used pins
 * *****************************************************************************
 * Analog channels
 * *****************************************************************************
 * #define CH00               PORTAbits.AN0
 * #define CH01               PORTAbits.AN1
 * #define CH02               PORTAbits.AN2
 * #define CH03               PORTAbits.AN3
 * *****************************************************************************
 * SPI Pins
 * *****************************************************************************
 * #define CS                  PORTAbits.RA5
 * #define SCK                PORTBbits.RB1 
 * #define SDO                PORTCbits.RC7
 * #define SDI                 PORTBbits.RB0
 * #define MCP_INT         PORTBbits.RB2
 * *****************************************************************************
 * USB pins
 * *****************************************************************************
 * #define PWM1_OUT           PORTCbits.RC1
 * #define PWM2_OUT           PORTCbits.RC2
 * *****************************************************************************
 *  Display
 * *****************************************************************************
 * #define LCD_E                 PORTDbits.RD0 
 * #define LCD_RS               PORTDbits.RD1
 * #define LCD_RW              PORTDbits.RD2
*  #define LCD_D4              PORTDbits.RD4
*  #define LCD_D5              PORTDbits.RD5
*  #define LCD_D6              PORTDbits.RD6
*  #define LCD_D7              PORTDbits.RD4
*  *****************************************************************************
*/