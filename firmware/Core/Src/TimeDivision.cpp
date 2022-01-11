/*
 * TimeDivision.cpp
 *
 *  Created on: Jan 7, 2022
 *      Author: Paolo Achdjian
 */

#include "tim.h"
#include "TimeDivision.h"


void TimeDivision::start(){
	htim2.Instance->ARR=timerEnd;
	HAL_TIM_Base_Start_IT(&htim2);
}

void TimeDivision::stop(){
	HAL_TIM_Base_Stop_IT(&htim2);
}

void TimeDivision::update(){
	htim2.Instance->CNT=0;
	htim2.Instance->ARR=timerEnd;
}
