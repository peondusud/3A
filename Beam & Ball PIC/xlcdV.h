/*This file is to be #included in each source using xlcd200.lib */
#ifndef __XLCD_H
#define __XLCD_H

/* PIC18 XLCD peripheral routines.
 * 10/07 Arlotto : Add compatibility with PICDEM2+ 2006 version
 *                  #define GREEN_PICDEM or
 *                  #define RED_PICDEM to use GREEN (>2006) or RED (<2006) PICDEM2+
 *                 To be sure of what you actualy need, check board schematic for lcd wiring. 
 * 03/06 Arlotto : Add possibility to replace busy lcd bit testing
 *                 by a busy delay loop by definig BUSY_LCD_IS_A_DELAY
 * 01/05 Arlotto : Modified for PICDEM2 lcd module
 *
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */
/* comment out this define if you don't use PICDEM */
#define PICDEM_LCD 
#define BUSY_LCD_IS_A_DELAY  // comment out this define to use busy bit tesing
/* comment out this define if you don't want the XLCD to be used as _H_USER */
#define _H_USER_IS_XLCD
// comment out this define if you don't use "green" PICDEM */
#define GREEN_PICDEM 
// comment out this define if you don't use "red" PICDEM */
//#define RED_PICDEM
/* Interface type 8-bit or 4-bit
 * For 8-bit operation uncomment the #define BIT8
 */
/* #define BIT8 */

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, comment the #define UPPER
 */
/* #define UPPER */

/* DATA_PORT defines the port to which the LCD data lines are connected */
/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#ifdef RED_PICDEM

#define DATA_PORT      PORTD
#define TRIS_DATA_PORT TRISD

#define RW_PIN   PORTAbits.RA2   /* PORT for RW */
#define TRIS_RW  DDRAbits.RA2    /* TRIS for RW */
#define RS_PIN   PORTAbits.RA3   /* PORT for RS */
#define TRIS_RS  DDRAbits.RA3    /* TRIS for RS */
#define E_PIN    PORTAbits.RA1   /* PORT for E  */
#define TRIS_E   DDRAbits.RA1   /* TRIS for E  */

#endif

#ifdef GREEN_PICDEM

#define DATA_PORT      PORTD
#define TRIS_DATA_PORT TRISD
#define POWER_PIN PORTDbits.RD7  /* Power on lcd module */ 
#define RW_PIN   PORTDbits.RD5   /* PORT for RW */
#define TRIS_RW  DDRDbits.RD5    /* TRIS for RW */
#define RS_PIN   PORTDbits.RD4   /* PORT for RS */
#define TRIS_RS  DDRDbits.RD4    /* TRIS for RS */
#define E_PIN    PORTDbits.RD6   /* PORT for E  */
#define TRIS_E   DDRDbits.RD6   /* TRIS for E  */

#endif

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010011  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010111  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011011  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011111  /* Display shifts to the right */

/* goto cmd defines for use with WriteCmdXLCD */
#define GOTO_CMD 0x80
#define GOTO_LINE_ONE GOTO_CMD+0x00
#define GOTO_LINE_TWO GOTO_CMD+0x40

/* goto cmd defines for use with gotoXLCD */
#define LCD_LINE_ONE 0x00
#define LCD_LINE_TWO 0x40
 
/* Function Set defines */
#define FOUR_BIT   0b00101111  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111111  /* 8-bit Interface               */
#define LINE_5X7   0b00110011  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110111  /* 5x10 characters               */
#define LINES_5X7  0b00111011  /* 5x7 characters, multiple line */
#define OPEN_PICDEM_LCD 0x28   /*Arlotto : the right value for picdem2+ lcd module ! */

#define PARAM_SCLASS auto
#define MEM_MODEL far  /* Change this to near for small memory model */

/* OpenXLCD
 * Configures I/O pins for external LCD
 */
void OpenXLCD(PARAM_SCLASS unsigned char);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(PARAM_SCLASS unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(PARAM_SCLASS unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(PARAM_SCLASS unsigned char);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(PARAM_SCLASS char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */
void putsXLCD(PARAM_SCLASS char *);

/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */
void putrsXLCD(PARAM_SCLASS const MEM_MODEL rom char *);
/* gotoXLCD set cursor position (add 0x40 for line2)
*/
void gotoXLCD(unsigned char pos);

void clearXLCD(void );

/* User defines these routines according to the oscillator frequency */
extern void DelayFor18TCY(void);  // 18 Tcy
extern void DelayPORXLCD(void);   // 15 ms
extern void DelayXLCD(void);      // At least 4.1ms



#endif
