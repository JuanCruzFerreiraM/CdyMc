#ifndef LCD_H
#define LCD_H

#include <stdint.h>


//Uncomment this if LCD 4 bit interface is used
//******************************************
#define LCD_4bit
//***********************************************



#define LCD_RS	1 	//define MCU pin connected to LCD RS
#define LCD_RW	1 	//define MCU pin connected to LCD R/W
#define LCD_E	0	//define MCU pin connected to LCD E
#define LCD_D0	0	//define MCU pin connected to LCD D0
#define LCD_D1	1	//define MCU pin connected to LCD D1
#define LCD_D2	2	//define MCU pin connected to LCD D1
#define LCD_D3	3	//define MCU pin connected to LCD D2
#define LCD_D4	1	//define MCU pin connected to LCD D3
#define LCD_D5	2	//define MCU pin connected to LCD D4
#define LCD_D6	2	//define MCU pin connected to LCD D5
#define LCD_D7	1	//define MCU pin connected to LCD D6
#define LDP1 PORTB	//define MCU port connected to LCD data pins
#define LDP2 PORTC	//define MCU port connected to LCD data pins
#define LCP PORTD	//define MCU port connected to LCD control pins
#define LDDR1 DDRB	//define MCU direction register for port connected to LCD data pins
#define LDDR2 DDRC	//define MCU direction register for port connected to LCD data pins
#define LCDR DDRD	//define MCU direction register for port connected to LCD control pins

//--------------------------------------------------------------------------------------------------
/*Macro para escribir en los puertos conectados al LCD.
Data es el dato de 8 bits a escribir.
"PORTX=...((Data & (1<<Y)) >> Z) |..." Escribe el bit Y de Data en el bit Y-Z del puerto X
*/

#define LCD_DATAWR(Data) PORTB = (PORTB & 0xF9) | ((Data & (1<<6)) >> 4) | ((Data & (1<<7)) >> 6);\
	                     PORTC = (PORTC & 0xF9) | ((Data & (1<<4)) >> 3) | ((Data & (1<<5)) >> 3);
//----------------------------------------------------------------------------------------------------

#define LCD_CLR             0	//DB0: clear display
#define LCD_HOME            1	//DB1: return to home position
#define LCD_ENTRY_MODE      2	//DB2: set entry mode
#define LCD_ENTRY_INC       1	//DB1: increment
#define LCD_ENTRY_SHIFT     0	//DB2: shift
#define LCD_ON_CTRL         3	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2	//DB2: turn display on
#define LCD_ON_CURSOR       1	//DB1: turn cursor on
#define LCD_ON_BLINK        0	//DB0: blinking cursor
#define LCD_MOVE            4	//DB4: move cursor/display
#define LCD_MOVE_DISP       3	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address
// reading:
#define LCD_BUSY            7	//DB7: LCD is busy
#define LCD_LINES			2	//visible lines
#define LCD_LINE_LENGTH		16	//line length (in characters)
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54
// progress bar defines
#define PROGRESSPIXELS_PER_CHAR	6


void LCDescribeDato(int val,unsigned int field_length); // Agrego Funcion para escribir Enteros
void LCDsendChar(uint8_t);		//forms data ready to send to 74HC164
void LCDsendCommand(uint8_t);	//forms data ready to send to 74HC164
void LCDinit(void);			//Initializes LCD
void LCDclr(void);				//Clears LCD
void LCDhome(void);			//LCD cursor home
void LCDstring(uint8_t*, uint8_t);	//Outputs string to LCD
void LCDGotoXY(uint8_t, uint8_t);	//Cursor to X Y position
void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM 
void LCDshiftRight(uint8_t);	//shift by n characters Right
void LCDshiftLeft(uint8_t);	//shift by n characters Left
void LCDcursorOn(void);		//Underline cursor ON
void LCDcursorOnBlink(void);	//Underline blinking cursor ON
void LCDcursorOFF(void);		//Cursor OFF
void LCDblank(void);			//LCD blank but not cleared
void LCDvisible(void);			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n
// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);
void LCD_Init();
void LCD_Update();




#endif

