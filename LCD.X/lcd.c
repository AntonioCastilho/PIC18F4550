/* ****************************************************************************
 * Project: Control Functions             File lcd.c                 March/2022
 * ****************************************************************************
 * File description: Functions for 16x2 LCD display control, with PIC18F4550.      
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

/******************************************************************************/
// Includes
/******************************************************************************/
#include <xc.h>
#include "lcd.h"
/******************************************************************************/

/******************************************************************************
 * Function: void lcd_com(uint8_t cmd);
 * Description: Sends a command to the LCD display.
 * Example: lcd_com(0x01);
 * Input: Command in 8 bits, conforme LCD datasheet.
 * Output: void
 * ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 03/23/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/
void lcd_com(uint8_t cmd)
{
    LCD_PORT = 0xF0;
    __delay_us(5);
  
    LCD_PORT = (uint8_t)(LCD_PORT & (cmd & 0xF0)); // Send high nibble.
    __delay_us(5);
    
    LCD_RW = 0;     
    LCD_RS = 0;     
    LCD_E = 1;     
    __delay_us(5);

    LCD_E = 0;      
    __delay_us(5);

    LCD_PORT = 0xF0;
    LCD_PORT = (uint8_t)(LCD_PORT & ((cmd << 4) & 0xF0)); // Send low nibble.
   
    LCD_RW = 0;     
    LCD_RS = 0;     
    LCD_E = 1;     
    __delay_us(5);

    LCD_E = 0;      
    __delay_us(5);

    if(cmd == 0x01)
       __delay_ms(15);
       
}
/* end of function
 * void lcd_com(uint8_t cmd)
*******************************************************************************/

/******************************************************************************
 * Function: void lcd_ini(void);
 * Description: Initializes the LCD display and configures it to suit the 
 *              project: data in 4 bits, 2 lines, 5x10 dots, 
 *              cursor on and blinking.
 * Input: void
 * Output: void
 * Created in: 03/23/2022 by Antonio Aparecido Ariza Castilho
 ******************************************************************************/
void lcd_ini(void)
{
    LCD_TRIS = 0x00;  // Port D to LCD as output.
    LCD_PORT = 0x80;  // Power lcd display.

    // LCD display boot synchronization.
    lcd_com(0x30);  // Step 1.
    __delay_us(100);
    lcd_com(0x30);  // Step 2.
    __delay_us(100);
    
    lcd_com(0x32);  // step 3 and 4.
    __delay_us(100);
    
    lcd_com(0x2C); // Function set. 4 bits, 2 rows, 5x10 dots.
    __delay_us(100); 
    lcd_com(0x06); // Entry mode set. Increment. No shift.
    __delay_us(100); 
    lcd_com(0x0F); //Display on/off control. Display on, cursor on, cursor blink.
    __delay_us(100);
    lcd_com(0x01); // Clear display.
    __delay_us(100);
    
}
/* end of function
 * void lcd_ini(void)
*******************************************************************************/

/******************************************************************************
 * Function: void lcd_prtChar(uint8_t data)
 * Description: Writes a byte, ie a character on the display. 
 *              It is a helper function, for lcd_printString. 
 * Input: Byte representing an ASCII value, valid for the lcd.
 * Output: void
 * Created in: 03/26/2022 by Antonio Aparecido Ariza Castilho
 ******************************************************************************/
void lcd_prtChar(uint8_t dat)
{
    LCD_PORT = 0xF0;
    //__delay_us(5);
    __delay_ms(20);
    LCD_PORT = (uint8_t)(LCD_PORT & (dat & 0xF0)); // Send high nibble.
    //__delay_us(5);
    __delay_ms(20);
    
    LCD_RW = 0;     
    LCD_RS = 1;     
    LCD_E = 1;     
    //__delay_us(5);
    __delay_ms(20);
    LCD_E = 0;      
    //__delay_us(5);
    __delay_ms(20);
    
    LCD_PORT = 0xF0;
    LCD_PORT = (uint8_t)(LCD_PORT & ((dat << 4) & 0xF0)); // Send low nibble.
   
    LCD_RW = 0;     
    LCD_RS = 1;     
    LCD_E = 1;     
    //__delay_us(5);
    __delay_ms(20);
    LCD_E = 0;      
    //__delay_us(5);
    __delay_ms(20);
}
/* end of function 
 * void lcd_prtChar(uint8_t dat)
*******************************************************************************/

/******************************************************************************
 * Function: void lcd_prtStr(int8_t row, int8_t col, uint8_t data)
 * Description: Writes a string to the display starting at the indicated row
 *              and column, until it finds a null character, which is the end 
 *              of the string.
 * Example: lcd_printString(0,0,("Seja Bem Vindo!!"));
 * Input: Row and column and the string.
 * Output: void
 * Created in: 03/26/2022 by Antonio Aparecido Ariza Castilho
 ******************************************************************************/
void lcd_prtStr(const uint8_t row, const uint8_t col, const uint8_t *str)
{
    __delay_us(100);
    // Calculates the address where the string will start.
    if(row == 2)
    {
        lcd_com(192 + col);
    }
    else if(row == 1)
    {
        lcd_com(128 + col);
    }
    else
    {
        lcd_com(0x80);
    }
    
    while(*str)
    {
        __delay_us(100);
        lcd_prtChar(*str);
        str++;
    }
      
    // TODO : Generate a code that scrolls the message when it has more 
    //        than 16 characters.
}
/* end of function
 * lcd_prtStr(int8_t row, int8_t col, const uint8_t *str)
*******************************************************************************/

/******************************************************************************
 * Function: void lcd_prtInt(const uint8_t row, const uint8_t col,
 *           const uint16_t str);
 * Description: Write integer number on LCD display.
 * Example: lcd_prtInt(0, 0, value); where value is a variable that contains 
 *          an integer and must be of the required size.
 * Input: Row and column and the integer number.
 * Output: void
* ****************************************************************************
 * Date      | Author            | Description
 * **********|*******************|*********************************************
 * 04/02/2022| Antonio Castilho  | Function has been created
 ******************************************************************************/
void lcd_prtInt(const uint8_t row, const uint8_t col, const int32_t value)
{
    uint8_t str[((sizeof(value))+1)];
    itoa(str, value, 10);
    
    lcd_prtStr(row,col,str);
}
/* end of function
 * void lcd_prtInt(const uint8_t row, const uint8_t col, const uint16_t str);
*******************************************************************************/