/*
 * Trigger.h
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>

enum class TriggerType {
	PositiveSlope,
	NegativeSlope

};

class Trigger {
public:
	static int16_t pixelPos;
	static uint16_t adcLimit;
	static TriggerType type;
	static void up();

	static void checkTrigger();
private:
	static uint16_t prevValue;
};

