/*
 * VoltDivision.h
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>

class VoltDivision {
public:
	constexpr VoltDivision(const char * name, const char * label1, const char * label2, const char * label3, const char * label4, double min, double max):
	name(name), label1(label1), label2(label2),label3(label3),label4(label4), min(min), max(max), mVmax(max*1000){}

	constexpr VoltDivision(const VoltDivision & vd):
		name(vd.name), label1(vd.label1), label2(vd.label2),label3(vd.label3),label4(vd.label4),min(vd.min), max(vd.max),mVmax(vd.mVmax){}

	const char * getName() const{return name;}
	const char * getLabel1() const{return label1;}
	const char * getLabel2() const{return label2;}
	const char * getLabel3() const{return label3;}
	const char * getLabel4() const{return label4;}

	char * getTriggerValue(uint16_t minPixel, uint16_t maxPixel);

	uint16_t convertToGraph(uint16_t value, uint16_t maxValue);

private:
	const char * name;
	const char * label1;
	const char * label2;
	const char * label3;
	const char * label4;
	double min;
	double max;
	uint32_t mVmax;
};

constexpr VoltDivision vd1("1V/div", "1v", "2v", "3v", "4v", 0.0, 5.0);
