/*
 * Graph.cpp
 *
 *  Created on: Jan 7, 2022
 *      Author: Paolo Achdjian
 */

#include "Graph.h"
#include "ADS7841.h"
#include "Status.h"
#include "UI.h"

extern ADS7841 ads7841;
extern UI ui;
uint32_t counterG;

Graph::Graph():
	buffer1Iter{buffer1A.begin()},
	buffer2Iter{buffer2A.begin()},
	fillBufferA{true},
	bufferSize{0},
	updateUI{false}{

}

void Graph::loop() {
	if (updateUI){
		ui.drawGraph(fillBufferA ? &buffer1B: &buffer1A, fillBufferA ? &buffer2B: &buffer2A);
		updateUI=false;
	}
}

void Graph::startAcquire(){
	if (fillBufferA){
		buffer1Iter = buffer1A.begin();
		buffer2Iter = buffer2A.begin();
	} else {
		buffer1Iter = buffer1B.begin();
		buffer2Iter = buffer2B.begin();
	}
	*buffer1Iter = ads7841.getLastValue1();
	*buffer2Iter = ads7841.getLastValue2();
	buffer1Iter++;
	buffer2Iter++;
	bufferSize=1;
}
void Graph::acquireNewSample(){
	counterG++;
	if (bufferSize < PANEL_X){
		*buffer1Iter = ads7841.getLastValue1();
		*buffer2Iter = ads7841.getLastValue2();
		buffer1Iter++;
		buffer2Iter++;
		bufferSize++;
	}
	if (bufferSize >= PANEL_X){
		if (!updateUI){
			fillBufferA = !fillBufferA;
		}
		status = Status::ContinuosTriggerWaiting;
		updateUI=true;
	}

}
