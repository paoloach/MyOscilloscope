/*
 * Bitmap.h
 *
 *  Created on: Jan 3, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>
#include "Point.h"

class Bitmap{
public:
	Bitmap(uint16_t width, uint16_t height):width(width), height(height), data(new uint16_t[width*height]){}
	Bitmap(Bitmap && other):width(other.width), height(other.height), data(other.data){other.data=nullptr;}
	~Bitmap(){delete []data;}
	void put(Point pos, uint16_t color){
		data[pos.x+pos.y*width] = color;
	}
	uint16_t getSize(){return width*height;}
	uint16_t getWidth() {return width;}
	uint16_t getHeight() {return height;}
	uint16_t * getData() {return data;}
private:
	uint16_t width;
	uint16_t height;
	uint16_t * data;
};

