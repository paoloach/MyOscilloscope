/*
 * Menu.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Paolo Achdjian
 */

#pragma once



enum class ElementChanging {
	Trigger,
	TriggerType,
	TimeDivision,
	VoltDivision
};

class Menu {
public:
	Menu();
	void showMenu();

private:
	ElementChanging elementChanging;

	void setButtonCB();
	void menuNext();
	void menuPrev();
	static void triggerUp();
	static void triggerDown();
	static void triggerTypeUp();
	static void triggerTypeDown();
	static void voltDivisionUp();
	static void voltDivisionDown();
	static void timeDivisionUp();
	static void timeDivisionDown();
};

