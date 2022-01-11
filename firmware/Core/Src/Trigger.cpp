/*
 * Trigger.cpp
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#include "Trigger.h"
#include "ADS7841.h"
#include "Graph.h"
#include "Status.h"

extern ADS7841 ads7841;
extern Graph graph;

int16_t Trigger::pixelPos=160;
uint16_t Trigger::adcLimit;
TriggerType Trigger::type;
uint16_t Trigger::prevValue=0xFFFF;

void Trigger::checkTrigger() {
	uint16_t value = ads7841.getLastValue1();
	if (prevValue != 0xFFFF){
		if (type == TriggerType::PositiveSlope){
			if (prevValue < adcLimit && value >= adcLimit){
				graph.startAcquire();
				status = Status::Acquiring;
			}
		} else if (type == TriggerType::NegativeSlope){
			if (prevValue > adcLimit && value <= adcLimit){
				graph.startAcquire();
				status = Status::Acquiring;
			}
		}
	}
	prevValue = value;
}
