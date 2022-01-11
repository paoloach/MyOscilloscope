/*
 * Graph.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>
#include <array>
#include "constants.h"

class Graph {
public:
	Graph();
	void startAcquire();
	void acquireNewSample();
	void loop();
private:
	std::array<uint16_t,PANEL_X> buffer1A;
	std::array<uint16_t,PANEL_X> buffer1B;
	std::array<uint16_t,PANEL_X> buffer2A;
	std::array<uint16_t,PANEL_X> buffer2B;
	uint16_t * buffer1Iter;
	uint16_t * buffer2Iter;
	uint8_t fillBufferA;
	uint16_t bufferSize;
	bool updateUI;

};

