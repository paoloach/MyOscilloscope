/*
 * Menu.cpp
 *
 *  Created on: Jan 9, 2022
 *      Author: Paolo Achdjian
 */

#include "Menu.h"
#include "Button.h"
#include "UI.h"
#include "Trigger.h"
#include "TimeDivisions.h"

extern TimeDivisions timeDivisions;
extern UI ui;
extern Button button;

Menu::Menu():
		elementChanging(ElementChanging::Trigger){
}

void Menu::showMenu(){
	ui.showTimeDivision(elementChanging == ElementChanging::TimeDivision);
	ui.showVoltDivision(elementChanging == ElementChanging::VoltDivision);
	ui.updateTrigger(elementChanging == ElementChanging::Trigger);
	button.addCallback(ButtonEvent::B3RISE, [this](){menuNext();});
	button.addCallback(ButtonEvent::B4RISE, [this](){menuPrev();});
	setButtonCB();
}

void Menu::menuNext(){
	switch(elementChanging){
		case ElementChanging::Trigger:
			ui.updateTrigger(false);
			elementChanging=ElementChanging::TriggerType;
			ui.showTriggerType(true);
			break;
		case ElementChanging::TimeDivision:
			ui.showTimeDivision(false);
			elementChanging=ElementChanging::VoltDivision;
			ui.showVoltDivision(true);
			break;
		case ElementChanging::VoltDivision:
			ui.showVoltDivision(false);
			elementChanging=ElementChanging::Trigger;
			ui.updateTrigger(true);
			break;
		case ElementChanging::TriggerType:
			ui.showTriggerType(false);
			elementChanging=ElementChanging::TimeDivision;
			ui.showTimeDivision(true);
			break;
	}
	setButtonCB();
}
void Menu::menuPrev(){
	switch(elementChanging){
	case ElementChanging::Trigger:
		ui.updateTrigger(false);
		elementChanging=ElementChanging::VoltDivision;
		ui.showVoltDivision(true);
		break;
	case ElementChanging::TimeDivision:
		ui.showTimeDivision(false);
		elementChanging=ElementChanging::TriggerType;
		ui.showTriggerType(true);
		break;
	case ElementChanging::VoltDivision:
		ui.showVoltDivision(false);
		elementChanging=ElementChanging::TimeDivision;
		ui.showTimeDivision(true);
		break;
	case ElementChanging::TriggerType:
		ui.showTriggerType(false);
		elementChanging=ElementChanging::Trigger;
		ui.updateTrigger(true);
		break;
	}
	setButtonCB();
}


void Menu::setButtonCB() {
	switch(elementChanging){
	case ElementChanging::Trigger:
		button.addCallback(ButtonEvent::B1RISE, triggerUp);
		button.addCallback(ButtonEvent::B2RISE, triggerDown);
		break;
	case ElementChanging::TriggerType:
		button.addCallback(ButtonEvent::B1RISE, triggerTypeUp);
		button.addCallback(ButtonEvent::B2RISE, triggerTypeDown);
		break;
	case ElementChanging::VoltDivision:
		button.addCallback(ButtonEvent::B1RISE, voltDivisionUp);
		button.addCallback(ButtonEvent::B2RISE, voltDivisionDown);
		break;
	case ElementChanging::TimeDivision:
		button.addCallback(ButtonEvent::B1RISE, timeDivisionUp);
		button.addCallback(ButtonEvent::B2RISE, timeDivisionDown);
		break;
	}
}


void Menu::triggerUp(){
	Trigger::pixelPos++;
	if (Trigger::pixelPos >= ui.getMaxTriggerPixel()){
		Trigger::pixelPos = ui.getMaxTriggerPixel()-1;
	}
	ui.updateTrigger(true);
}

void Menu::triggerDown(){
	Trigger::pixelPos--;
	if (Trigger::pixelPos < 0){
		Trigger::pixelPos = 0;
	}
	ui.updateTrigger(true);
}


void Menu::triggerTypeUp(){
	if (Trigger::type == TriggerType::NegativeSlope){
		Trigger::type = TriggerType::PositiveSlope;
	} else {
		Trigger::type = TriggerType::NegativeSlope;
	}
	ui.showTriggerType(true);
}
void Menu::triggerTypeDown(){
	if (Trigger::type == TriggerType::NegativeSlope){
		Trigger::type = TriggerType::PositiveSlope;
	} else {
		Trigger::type = TriggerType::NegativeSlope;
	}
	ui.showTriggerType(true);
}
void Menu::voltDivisionUp(){

}
void Menu::voltDivisionDown(){

}
void Menu::timeDivisionUp(){
	timeDivisions.nextTimeDivision();
	ui.showTimeDivision(true);
}
void Menu::timeDivisionDown(){
	timeDivisions.prevTimeDivision();
	ui.showTimeDivision(true);
}












