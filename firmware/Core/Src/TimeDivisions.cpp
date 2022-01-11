/*
 * TimeDivisions.cpp
 *
 *  Created on: Jan 9, 2022
 *      Author: Paolo Achdjian
 */

#include "TimeDivisions.h"


void TimeDivisions::nextTimeDivision(){
	currentTimeDivision++;
	if (currentTimeDivision >= MAX_TIME_DIVISIONS){
		currentTimeDivision=0;
	}
	timeDivisions[currentTimeDivision].update();
}
void TimeDivisions::prevTimeDivision(){
	if (currentTimeDivision == 0){
		currentTimeDivision = MAX_TIME_DIVISIONS-1;
	}else {
		currentTimeDivision--;
	}
	timeDivisions[currentTimeDivision].update();
}
