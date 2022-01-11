/*
 * Font.cpp
 *
 *  Created on: Jan 3, 2022
 *      Author: Paolo Achdjian
 */

#include <Font.h>

Bitmap Font::getChar(char c, uint16_t color, uint16_t backgroud){
	Bitmap bitmap(sizeX, sizeY );

	uint16_t firstData = (c-offset)*sizeY*sizeX/8;
	const uint8_t * charData = data+firstData;
	uint8_t ch;
	for(uint8_t y=0; y < sizeY; y++){
		for(uint8_t x=0; x < sizeX; x++){
			if ( (x % 8) == 0){
				ch = *charData;
				charData++;
			}
			if (ch & 0x80){
				bitmap.put(Point(x,y),color );
			} else {
				bitmap.put(Point(x,y),backgroud );
			}
			ch = ch << 1;
		}
	}

	return bitmap;

}
