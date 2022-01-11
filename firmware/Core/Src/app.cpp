/*
 * app.cpp
 *
 *  Created on: Dec 8, 2021
 *      Author: paolo
 */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "UI.h"
#include "app.h"
#include "ADS7841.h"
#include "Button.h"
#include "Trigger.h"
#include "Status.h"
#include "Graph.h"
#include "Menu.h"
#include "TimeDivisions.h"

TimeDivisions timeDivisions;
UI ui;
ADS7841 ads7841;
Button button;
Graph graph;
Status status=Status::Idle;
Menu menu;

void userCode2 (void) {
	Trigger::pixelPos=200;
	ui.init();
	ads7841.startContinuos(Channel::CH0,Channel::CH1);
	status = Status::ContinuosTriggerWaiting;
	menu.showMenu();
	timeDivisions.getCurrent().start();
}


void userCodeWhile () {
	char buffer[20];
	button.loop();
	graph.loop();
	auto lastValue1 = ads7841.getLastValue1();
	lastValue1 = lastValue1 >> 3;
	auto lastValue2 = ads7841.getLastValue2();
	lastValue2 = lastValue2 >> 3;
	sprintf(buffer, "%d , %d   ", lastValue1, lastValue2);
	ui.printValue(buffer);
}


void Timer2Event(){
	if (status == Status::ContinuosTriggerWaiting)
		Trigger::checkTrigger();
	else if (status == Status::Acquiring)
		graph.acquireNewSample();
}

void buttonEvent1(){
	if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET){
		button.newIntEvent(ButtonEvent::B1RISE);
	} else {
		button.newIntEvent(ButtonEvent::B1LOWER);
	}
}
void buttonEvent2(){
	if (HAL_GPIO_ReadPin(B1_GPIO_Port, B2_Pin) == GPIO_PIN_SET){
		button.newIntEvent(ButtonEvent::B2RISE);
	} else {
		button.newIntEvent(ButtonEvent::B2LOWER);
	}
}
void buttonEvent3(){
	button.newIntEvent(ButtonEvent::B3RISE);
}
void buttonEvent4(){
	button.newIntEvent(ButtonEvent::B4RISE);
}
void buttonEvent5(){
	button.newIntEvent(ButtonEvent::B5RISE);
}

void buttonEvent6(){
	button.newIntEvent(ButtonEvent::B6RISE);
}



