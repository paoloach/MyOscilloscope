/*
 * Point.h
 *
 *  Created on: Jan 3, 2022
 *      Author: paolo
 */
#pragma once

#include <stdint.h>
#include "Point.h"
#include "Bitmap.h"
#include "Font.h"

constexpr uint16_t color(uint8_t red, uint8_t green, uint8_t blue){
	uint16_t r = (red & 0xF8) >> 3;
	uint16_t g = (green & 0xFC) >> 2;
	uint16_t b =  (blue & 0xF8) >> 3;
	return (r << 11) | (g << 5) | b;
}

enum class Orientation {
	PORTRAIT,
	LANDSCAPE
};

#define ILI9486_NOP            0x00
#define ILI9486_SWRESET        0x01

#define ILI9486_RDDID          0x04
#define ILI9486_RDDST          0x09
#define ILI9486_RDMODE         0x0A
#define ILI9486_RDMADCTL       0x0B
#define ILI9486_RDPIXFMT       0x0C
#define ILI9486_RDIMGFMT       0x0D
#define ILI9486_RDSELFDIAG     0x0F

#define ILI9486_SLPIN          0x10
#define ILI9486_SLPOUT         0x11
#define ILI9486_PTLON          0x12
#define ILI9486_NORON          0x13

#define ILI9486_INVOFF         0x20
#define ILI9486_INVON          0x21
#define ILI9486_GAMMASET       0x26
#define ILI9486_DISPOFF        0x28
#define ILI9486_DISPON         0x29

#define ILI9486_CASET          0x2A
#define ILI9486_PASET          0x2B
#define ILI9486_RAMWR          0x2C
#define ILI9486_RAMRD          0x2E

#define ILI9486_PTLAR          0x30
#define ILI9486_VSCRDEF        0x33
#define ILI9486_MADCTL         0x36
#define ILI9486_VSCRSADD       0x37     /* Vertical Scrolling Start Address */
#define ILI9486_PIXFMT         0x3A     /* COLMOD: Pixel Format Set */

#define ILI9486_RGB_INTERFACE  0xB0     /* RGB Interface Signal Control */
#define ILI9486_FRMCTR1        0xB1
#define ILI9486_FRMCTR2        0xB2
#define ILI9486_FRMCTR3        0xB3
#define ILI9486_INVCTR         0xB4
#define ILI9486_DFUNCTR        0xB6     /* Display Function Control */

#define ILI9486_PWCTR1         0xC0
#define ILI9486_PWCTR2         0xC1
#define ILI9486_PWCTR3         0xC2
#define ILI9486_PWCTR4         0xC3
#define ILI9486_PWCTR5         0xC4
#define ILI9486_VMCTR1         0xC5
#define ILI9486_VMCTR2         0xC7

#define ILI9486_RDID1          0xDA
#define ILI9486_RDID2          0xDB
#define ILI9486_RDID3          0xDC
#define ILI9486_RDID4          0xDD

#define ILI9486_GMCTRP1        0xE0
#define ILI9486_GMCTRN1        0xE1
#define ILI9486_DGCTR1         0xE2
#define ILI9486_DGCTR2         0xE3

//-----------------------------------------------------------------------------
#define ILI9486_MAD_RGB        0x08
#define ILI9486_MAD_BGR        0x00

#define ILI9486_SIZE_X                     320
#define ILI9486_SIZE_Y                     480
#define ILI9486_MAD_RGB        0x08
#define ILI9486_MAD_BGR        0x00

constexpr uint8_t ILI9486_MAD_VERTICAL=0x20;
constexpr uint8_t ILI9486_MAD_X_LEFT=0;
constexpr uint8_t ILI9486_MAD_X_RIGHT=0x40;
constexpr uint8_t ILI9486_MAD_Y_DOWN=0x0;
constexpr uint8_t ILI9486_MAD_Y_UP=0x80;

#define ILI9486_MAD_COLORMODE  ILI9486_MAD_RGB
#define ILI9486_MAD_DATA_RIGHT_THEN_UP     ILI9486_MAD_COLORMODE | ILI9486_MAD_X_RIGHT | ILI9486_MAD_Y_UP
#define ILI9486_MAD_DATA_RIGHT_THEN_DOWN   ILI9486_MAD_COLORMODE | ILI9486_MAD_X_RIGHT | ILI9486_MAD_Y_DOWN
#define ILI9486_MAD_DATA_LEFT_THEN_UP     ILI9486_MAD_COLORMODE | ILI9486_MAD_X_LEFT | ILI9486_MAD_Y_UP
#define ILI9486_MAD_DATA_LEFT_THEN_DOWN   ILI9486_MAD_COLORMODE | ILI9486_MAD_X_LEFT | ILI9486_MAD_Y_DOWN


#define ILI9486_MAD_DATA_RGBMODE           ILI9486_MAD_COLORMODE | ILI9486_MAD_X_LEFT  | ILI9486_MAD_Y_DOWN



//*********************************
// COLORS
//*********************************
// VGA color palette
constexpr uint16_t VGA_BLACK=color(0,0,0);
constexpr uint16_t VGA_WHITE=color(255,255,255);
constexpr uint16_t VGA_RED=color(255,0,0);
constexpr uint16_t VGA_GREEN=color(0,255,0);
constexpr uint16_t VGA_BLUE=color(0,0,255);
constexpr uint32_t VGA_TRANSPARENT=0xFFFFFFFF;


#include "hardware.h"


typedef unsigned char byte;
typedef uint16_t word;

class UTFT
{
	public:
		UTFT();
		void	InitLCD(Orientation orientation=Orientation::LANDSCAPE);
		void	clrScr();
		void	drawPixel(int x, int y);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	fillScr(byte r, byte g, byte b);
		void	fillScr(word color);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	fillRect(int x1, int y1, int x2, int y2);
		void	fillRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	fillCircle(int x, int y, int radius);
		void    drawBitmap(Point pos, Bitmap & bitmap);
		void	setColor(word color){this->color=color;}
		word	getColor()const{return color;}
		void	setBackColor(uint32_t color);
		word	getBackColor()const{return background;}
		void	print(const char *st, Point point);
		void	printNumI(long num, Point p, int length=0, char filler=' ');
		void	printNumF(double num, byte dec, Point p, char divider='.', int length=0, char filler=' ');
		void	setFont(Font * currentFont){font =currentFont;}
		void	lcdOff();
		void	lcdOn();
		void	setContrast(char c);
		int		getWidth() {return width;}
		int		getHeight() {return height;}
		void    drawHLine(int x, int y, int l);
		void    drawVLine(int x, int y, int l);
private:
		uint16_t	   color;
		uint16_t		background;
		Orientation		orient;
		uint16_t		width;
		uint16_t		height;
		long			disp_x_size, disp_y_size;
		Font			* font;
		bool			_transparent;

		void LCD_Writ_Bus(char VH,char VL, byte mode);
		//void LCD_Write_COM(char VL);
		void LCD_Write_COM(uint8_t value);
		void LCD_Write_DATA(uint16_t value);
		void LCD_Write_DATA(uint16_t * values, uint16_t len);
		void LCD_Write_DATA(uint8_t vh, uint8_t vl){
			LCD_Write_DATA( ((uint16_t)vh << 8) + vl);}
		//void LCD_Write_DATA(char VL);
		void LCD_Write_COM_DATA(char com1,int dat1);
		void _hw_special_init();
		void setPixel(word color);

		void printChar(byte c, Point p);
		void setXY(word x1, word y1, word x2, word y2);
		void clrXY();
		void _set_direction_registers(byte mode);
		void _fast_fill_16(uint16_t color, long pix);
		void _fast_fill_8(int ch, long pix);
		void _convert_float(char *buf, double num, int width, byte prec);
		void csEnable() {
			HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
		}

		void csDisable() {
			HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
		}
};
