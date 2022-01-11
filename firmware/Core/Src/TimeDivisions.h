/*
 * TimeDivisions.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include "TimeDivision.h"

constexpr uint8_t MAX_TIME_DIVISIONS=3;

class TimeDivisions {
public:
	TimeDivisions():
		timeDivisions{ms_10, ms_5, ms_1},
		currentTimeDivision{0}{}
	TimeDivision & getCurrent(){return timeDivisions[currentTimeDivision];}
	void nextTimeDivision();
	void prevTimeDivision();
private:
	TimeDivision timeDivisions[MAX_TIME_DIVISIONS];
	uint8_t currentTimeDivision;
};

