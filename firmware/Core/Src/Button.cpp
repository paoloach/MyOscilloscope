/*
 * Button.cpp
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#include "main.h"
#include "Button.h"

constexpr uint32_t MIN_EVENT_REPETITION_TIME=2;

void Button::loop(){
	uint32_t now = HAL_GetTick ();
	while(!events.empty()){
		auto event = events.front();
		events.pop();
		auto found = lastEventTime.find(event);
		if (found != lastEventTime.end()){
			if(found->second - now <= 10 ){

				continue;
			}
		}
		lastEventTime[event] = now;
		auto cbFound = callbacks.find(event);
		if (cbFound != callbacks.end()){
			cbFound->second();
		}
	}
}
