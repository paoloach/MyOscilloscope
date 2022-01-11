/*
 * TimeDivision.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>
#include "constants.h"

constexpr uint32_t CLK_EVERY_US =  168;

class TimeDivision {
public:
	constexpr TimeDivision(const char * label, uint32_t valueUs):
	label{label}, timerEnd{valueUs*CLK_EVERY_US/DIVISORY}{
	}

	void start();
	void stop();
	void update();

	const char * getLabel() const {return label;}
private:
	const char * label;
	uint32_t timerEnd;
};

constexpr TimeDivision ms_10 = TimeDivision("10 ms", 10000);
constexpr TimeDivision ms_5 = TimeDivision("5 ms", 5000);
constexpr TimeDivision ms_1 = TimeDivision("1 ms", 1000);
