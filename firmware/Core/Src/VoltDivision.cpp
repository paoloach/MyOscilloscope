/*
 * VoltDivision.cpp
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#include <stdio.h>
#include "VoltDivision.h"
#include "Trigger.h"


uint16_t VoltDivision::convertToGraph(uint16_t value, uint16_t maxValue){
	value = value >> 3;

	uint32_t volt = (value*3300)/4096;

	uint16_t y= (maxValue*volt)/mVmax;

	if (y >= maxValue){
		y = maxValue-1;
	}
	return y;
}

char * VoltDivision::getTriggerValue(uint16_t minPixel, uint16_t maxPixel) {
	char * buffer = new char[10];
	int16_t pixel = Trigger::pixelPos;
	if (pixel < minPixel )
		pixel=minPixel;
	if (pixel >= maxPixel){
		pixel = maxPixel-1;
	}

	uint16_t val = 1000*(min + ((pixel - minPixel)*(max-min))/(maxPixel-minPixel));

	Trigger::adcLimit = (4096*val*8)/3300;

	sprintf(buffer, "%4d mv", val);

	return buffer;
}

