#include "UTFT.h"

#include "hardware.h"
#include "memorysaver.h"

UTFT::UTFT() {
	disp_x_size = 319;
	disp_y_size = 479;

}
void UTFT::LCD_Write_COM(uint8_t value) {
	selCmd();
	LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin << 16U;
	LCD_D0_GPIO_Port->ODR = value;
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
	// 30ns
	LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin;
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
	// 30ns
	selData();
}

//Write 16Bit add for ILI9486_8 ,ILI9488_8
void UTFT::LCD_Write_DATA(uint16_t value) {
	// 1 cpu cycle: 5.9593 ns
	// write cycle requested: 66 ns -> 12 cpu
	LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin << 16U;
	LCD_D0_GPIO_Port->ODR = value;
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
	// 30ns
	LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin;
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
	// 30ns
}

void UTFT::LCD_Write_DATA(uint16_t *values, uint16_t len) {
	for (uint16_t i = 0; i < len; i++) {
		LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin << 16U;
		LCD_D0_GPIO_Port->ODR = *values;
		__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
		// 30ns
		LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin;
		__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
		values++;
	}
}

void UTFT::LCD_Write_COM_DATA(char com1, int dat1) {

	LCD_Write_COM(com1);
	LCD_Write_DATA(dat1);
}

void UTFT::InitLCD(Orientation orientation) {

	orient = orientation;
	if (orient == Orientation::PORTRAIT) {
		width = disp_x_size + 1;
		height = disp_y_size + 1;
	} else {
		width = disp_y_size + 1;
		height = disp_x_size + 1;
	}

	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	delay(50);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	delay(150);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	delay(150);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	LCD_Write_COM(ILI9486_SWRESET);
	delay(100);

	LCD_Write_COM(ILI9486_RGB_INTERFACE);
	LCD_Write_DATA(0);
	LCD_Write_COM(ILI9486_SLPOUT);    // Exit Sleep (0x11)
	delay(10);

	LCD_Write_COM(ILI9486_PIXFMT);
	LCD_Write_DATA(0x55);

	LCD_Write_COM(ILI9486_MADCTL);
	LCD_Write_DATA(ILI9486_MAD_DATA_LEFT_THEN_DOWN | ILI9486_MAD_VERTICAL);

	LCD_Write_COM(ILI9486_PWCTR3);
	LCD_Write_DATA(0x44);

	LCD_Write_COM(ILI9486_VMCTR1);
	LCD_Write_DATA(0);
	LCD_Write_DATA(0);
	LCD_Write_DATA(0);
	LCD_Write_DATA(0);

	LCD_Write_COM(ILI9486_GMCTRP1);		// PGAMCTRL (Positive Gamma Control)
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x24);
	LCD_Write_DATA(0x1c);
	LCD_Write_DATA(0x0a);
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x08);
	LCD_Write_DATA(0x43);
	LCD_Write_DATA(0x88);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x06);
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x07);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(ILI9486_GMCTRN1);		// NGAMCTRL (Negative Gamma Control)
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x38);
	LCD_Write_DATA(0x30);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x0f);
	LCD_Write_DATA(0x4e);
	LCD_Write_DATA(0x77);
	LCD_Write_DATA(0x3c);
	LCD_Write_DATA(0x07);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x23);
	LCD_Write_DATA(0x1b);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(ILI9486_DGCTR1);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x2E);
	LCD_Write_DATA(0x0B);
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x47);
	LCD_Write_DATA(0x75);
	LCD_Write_DATA(0x37);
	LCD_Write_DATA(0x06);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x03);
	LCD_Write_DATA(0x24);
	LCD_Write_DATA(0x20);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(ILI9486_NORON);     // Normal display on (0x13)
	LCD_Write_COM(ILI9486_INVON);    // Display inversion off (0x20)
	LCD_Write_COM(ILI9486_SLPOUT);    // Exit Sleep (0x11)
	delay(200);
	LCD_Write_COM(ILI9486_DISPON);    // Display on (0x29)
	delay(10);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

	setColor(VGA_WHITE);
	setBackColor(VGA_BLACK);
	_transparent = false;

}

void UTFT::clrXY() {
	if (orient == Orientation::PORTRAIT)
		setXY(0, 0, disp_x_size, disp_y_size);
	else
		setXY(0, 0, disp_y_size, disp_x_size);
}

void UTFT::drawRect(int x1, int y1, int x2, int y2) {
	if (x1 > x2) {
		swap(x1, x2);
	}
	if (y1 > y2) {
		swap(y1, y2);
	}

	drawHLine(x1, y1, x2 - x1);
	drawHLine(x1, y2, x2 - x1);
	drawVLine(x1, y1, y2 - y1);
	drawVLine(x2, y1, y2 - y1);
}

void UTFT::drawRoundRect(int x1, int y1, int x2, int y2) {
	if (x1 > x2) {
		swap(x1, x2);
	}
	if (y1 > y2) {
		swap(y1, y2);
	}
	if ((x2 - x1) > 4 && (y2 - y1) > 4) {
		drawPixel(x1 + 1, y1 + 1);
		drawPixel(x2 - 1, y1 + 1);
		drawPixel(x1 + 1, y2 - 1);
		drawPixel(x2 - 1, y2 - 1);
		drawHLine(x1 + 2, y1, x2 - x1 - 4);
		drawHLine(x1 + 2, y2, x2 - x1 - 4);
		drawVLine(x1, y1 + 2, y2 - y1 - 4);
		drawVLine(x2, y1 + 2, y2 - y1 - 4);
	}
}

void UTFT::fillRect(int x1, int y1, int x2, int y2) {
	if (x1 > x2) {
		swap(x1, x2);
	}
	if (y1 > y2) {
		swap(y1, y2);
	}
	csEnable();
	setXY(x1, y1, x2, y2);
	sbi(P_RS, B_RS);
	_fast_fill_16(color, ((long(x2 - x1) + 1) * (long(y2 - y1) + 1)));
	csDisable();
}

void UTFT::fillRoundRect(int x1, int y1, int x2, int y2) {
	if (x1 > x2) {
		swap(x1, x2);
	}
	if (y1 > y2) {
		swap(y1, y2);
	}

	if ((x2 - x1) > 4 && (y2 - y1) > 4) {
		for (int i = 0; i < ((y2 - y1) / 2) + 1; i++) {
			switch (i) {
			case 0:
				drawHLine(x1 + 2, y1 + i, x2 - x1 - 4);
				drawHLine(x1 + 2, y2 - i, x2 - x1 - 4);
				break;
			case 1:
				drawHLine(x1 + 1, y1 + i, x2 - x1 - 2);
				drawHLine(x1 + 1, y2 - i, x2 - x1 - 2);
				break;
			default:
				drawHLine(x1, y1 + i, x2 - x1);
				drawHLine(x1, y2 - i, x2 - x1);
			}
		}
	}
}

void UTFT::drawCircle(int x, int y, int radius) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;

	csEnable();
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(color);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(color);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(color);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(color);

	while (x1 < y1) {
		if (f >= 0) {
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(color);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(color);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(color);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(color);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(color);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(color);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(color);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(color);
	}
	csDisable();
	clrXY();
}

void UTFT::fillCircle(int x, int y, int radius) {
	for (int y1 = -radius; y1 <= 0; y1++)
		for (int x1 = -radius; x1 <= 0; x1++)
			if (x1 * x1 + y1 * y1 <= radius * radius) {
				drawHLine(x + x1, y + y1, 2 * (-x1));
				drawHLine(x + x1, y - y1, 2 * (-x1));
				break;
			}
}

void UTFT::drawBitmap(Point pos, Bitmap &bitmap) {
	csEnable();
	setXY(pos.x, pos.y, pos.x + bitmap.getWidth()-1, pos.y + bitmap.getHeight()-1);
	LCD_Write_DATA(bitmap.getData(), bitmap.getSize());
	csDisable();
}

void UTFT::clrScr() {
	csEnable();
	clrXY();
	_fast_fill_16(background, ((disp_x_size + 1) * (disp_y_size + 1)));
	csDisable();
}

void UTFT::fillScr(byte r, byte g, byte b) {
	word color = ((r & 248) << 8 | (g & 252) << 3 | (b & 248) >> 3);
	fillScr(color);
}

void UTFT::fillScr(word colorScr) {

	csEnable();
	clrXY();
	_fast_fill_16(colorScr, ((disp_x_size + 1) * (disp_y_size + 1)));
	csDisable();
}

void UTFT::setBackColor(uint32_t color) {
	if (color == VGA_TRANSPARENT)
		_transparent = true;
	else {
		background = color;
		_transparent = false;
	}
}

void UTFT::setPixel(word color) {
	LCD_Write_DATA(color);	// rrrrrggggggbbbbb
}

void UTFT::drawPixel(int x, int y) {
	csEnable();
	setXY(x, y, x, y);
	setPixel(color);
	csDisable();
	clrXY();
}

void UTFT::drawLine(int x1, int y1, int x2, int y2) {
	if (y1 == y2)
		drawHLine(x1, y1, x2 - x1);
	else if (x1 == x2)
		drawVLine(x1, y1, y2 - y1);
	else {
		unsigned int dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		short xstep = x2 > x1 ? 1 : -1;
		unsigned int dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		short ystep = y2 > y1 ? 1 : -1;
		int col = x1, row = y1;

		csEnable();
		if (dx < dy) {
			int t = -(dy >> 1);
			while (true) {
				setXY(col, row, col, row);
				LCD_Write_DATA(color);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0) {
					col += xstep;
					t -= dy;
				}
			}
		} else {
			int t = -(dx >> 1);
			while (true) {
				setXY(col, row, col, row);
				LCD_Write_DATA(color);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0) {
					row += ystep;
					t -= dx;
				}
			}
		}
		csDisable();
	}
	clrXY();
}

void UTFT::drawHLine(int x, int y, int l) {
	if (l < 0) {
		l = -l;
		x -= l;
	}
	csEnable();
	setXY(x, y, x + l, y);
	sbi(P_RS, B_RS);
	_fast_fill_16(color, l);
	csDisable();
	clrXY();
}

void UTFT::drawVLine(int x, int y, int l) {
	if (l < 0) {
		l = -l;
		y -= l;
	}
	csEnable();
	setXY(x, y, x, y + l);
	sbi(P_RS, B_RS);
	_fast_fill_16(color, l);
	csDisable();
	clrXY();
}


void UTFT::print(const char *st, Point p) {
	char c = *st;
	while (c != 0) {
		Bitmap bitmap = font->getChar(c,  color,  background);
		drawBitmap(p, bitmap);
		st++;
		c = *st;
		p = p.move(font->getCharWidth(), 0);
	}
}

void UTFT::printNumI(long num, Point p, int length, char filler) {
	char buf[25];
	char st[27];
	bool neg = false;
	int c = 0, f = 0;

	if (num == 0) {
		if (length != 0) {
			for (c = 0; c < (length - 1); c++)
				st[c] = filler;
			st[c] = 48;
			st[c + 1] = 0;
		} else {
			st[0] = 48;
			st[1] = 0;
		}
	} else {
		if (num < 0) {
			neg = true;
			num = -num;
		}

		while (num > 0) {
			buf[c] = 48 + (num % 10);
			c++;
			num = (num - (num % 10)) / 10;
		}
		buf[c] = 0;

		if (neg) {
			st[0] = 45;
		}

		if (length > (c + neg)) {
			for (int i = 0; i < (length - c - neg); i++) {
				st[i + neg] = filler;
				f++;
			}
		}

		for (int i = 0; i < c; i++) {
			st[i + neg + f] = buf[c - i - 1];
		}
		st[c + neg + f] = 0;

	}

	print(st, p);
}

void UTFT::printNumF(double num, byte dec, Point p, char divider, int length,
		char filler) {
	char st[27];
	bool neg = false;

	if (dec < 1)
		dec = 1;
	else if (dec > 5)
		dec = 5;

	if (num < 0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.') {
		for (uint8_t i = 0; i < sizeof(st); i++)
			if (st[i] == '.')
				st[i] = divider;
	}

	if (filler != ' ') {
		if (neg) {
			st[0] = '-';
			for (uint8_t i = 1; i < sizeof(st); i++)
				if ((st[i] == ' ') || (st[i] == '-'))
					st[i] = filler;
		} else {
			for (uint8_t i = 0; i < sizeof(st); i++)
				if (st[i] == ' ')
					st[i] = filler;
		}
	}

	print(st, p);
}

void UTFT::lcdOff() {
	csEnable();
	LCD_Write_COM(0x28);
	csDisable();
}

void UTFT::lcdOn() {
	csEnable();
	LCD_Write_COM(0x29);
	csDisable();
}

void UTFT::setContrast(char c) {
	csEnable();
	if (c > 64)
		c = 64;
	LCD_Write_COM(0x25);
	LCD_Write_DATA(c);
	csDisable();
}

void UTFT::_fast_fill_16(uint16_t color, long pix) {
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	LCD_Write_COM(ILI9486_RAMWR);

	LCD_D0_GPIO_Port->ODR = color;
	for (long i = 0; i < pix; i++) {
		LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin << 16U;
		__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
		// 30ns
		LCD_WR_GPIO_Port->BSRR = (uint32_t) LCD_WR_Pin;
		__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");
		// 30ns
	}
}

void UTFT::setXY(word x1, word y1, word x2, word y2) {
	LCD_Write_COM(ILI9486_CASET);
	LCD_Write_DATA(x1 >> 8);
	LCD_Write_DATA(x1);
	LCD_Write_DATA(x2 >> 8);
	LCD_Write_DATA(x2);

	LCD_Write_COM(ILI9486_PASET);
	LCD_Write_DATA(y1 >> 8);
	LCD_Write_DATA(y1);
	LCD_Write_DATA(y2 >> 8);
	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c);

}
