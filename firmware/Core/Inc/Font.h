/*
 * Font.h
 *
 *  Created on: Jan 3, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <Bitmap.h>

class Font {
public:
	constexpr Font(uint8_t width, uint8_t height, uint8_t firstChar, uint8_t numChar, const uint8_t * data):
	data(data),sizeX(width),sizeY(height),offset(firstChar),numchars(numChar){}

	Bitmap getChar(char c,uint16_t color, uint16_t backgroud);
	uint16_t getCharWidth() const {return sizeX;}
	uint16_t getCharHeight() const {return sizeY;}
private:
	const uint8_t* data;
	uint16_t sizeX;
	uint16_t sizeY;
	uint16_t offset;
	uint16_t numchars;
};



extern Font  smallFont;
extern Font  bigFont;
