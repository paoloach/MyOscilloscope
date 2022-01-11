/*
 * Point.h
 *
 *  Created on: Jan 3, 2022
 *      Author: paolo
 */

#pragma once

#include <stdint.h>

class Point{

public:
	constexpr Point(uint16_t x, uint16_t y):x(x),y(y){}

	Point move(uint16_t dx, uint16_t dy){
		return Point(x+dx, y+dy);
	}
	uint16_t x;
	uint16_t y;
};


