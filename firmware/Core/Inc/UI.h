/*
 * UI.h
 *
 *  Created on: Jan 2, 2022
 *      Author: paolo
 */

#pragma once
#include <array>
#include "UTFT.h"
#include "VoltDivision.h"
#include "TimeDivision.h"
#include "constants.h"

constexpr uint16_t BACKGROUND = color(192,192,192);
constexpr uint16_t PANEL_COLOR = color(0,0,255);
constexpr uint16_t PANEL_TEXT_COLOR= color(255,255,0);
constexpr uint16_t LINE_DIVISOR_COLOR = color(255,255,255);
constexpr uint16_t TRIGGER_COLOR = color(128,128,128);
constexpr uint16_t GRAPH_COLOR1=color(32,32,255);
constexpr uint16_t GRAPH_COLOR2=color(255,32,32);


constexpr Point VOLT_LABEL1=Point(0, DIVISOR_VOLT_1-6);
constexpr Point VOLT_LABEL2=Point(0, DIVISOR_VOLT_2-6);
constexpr Point VOLT_LABEL3=Point(0, DIVISOR_VOLT_3-6);
constexpr Point VOLT_LABEL4=Point(0, DIVISOR_VOLT_4-6);

constexpr Point TIME_LABEL = Point(PANEL_X+3, 20);
constexpr Point TIME_VALUE = Point(PANEL_X+3, 32);

constexpr Point VOLT_LABEL = Point(PANEL_X+3, 50);
constexpr Point VOLT_VALUE = Point(PANEL_X+3, 62);

constexpr Point TRIGGER_LABEL = Point(PANEL_X+3, 80);
constexpr Point TRIGGER_VALUE = Point(PANEL_X+3, 92);

constexpr Point TRIGGER_TYPE_LABEL = Point(PANEL_X+3, 110);
constexpr Point TRIGGER_TYPE_VALUE = Point(PANEL_X+3, 122);
class UI {
public:
	UI();
	void init();
	void updateTrigger(bool selected=false);
	void showVoltDivision(bool selected=false);
	void showTimeDivision(bool selected=false);
	void showTriggerType(bool selected=false);

	void printValue(const char * string);
	uint16_t getMaxTriggerPixel(){
		return lcd.getHeight();
	}
	void drawGraph(std::array<uint16_t, PANEL_X> * data1, std::array<uint16_t, PANEL_X> * data2);
private:
	struct VertLine {
		constexpr VertLine():minY(0),maxY(0){}
		constexpr VertLine(uint16_t y1, uint16_t y2):minY{std::min(y1,y2) },maxY{std::max(y1,y2)}{}
		uint16_t minY;
		uint16_t maxY;
	};

	UTFT lcd;
	VoltDivision voltDivisions[1];
	uint8_t selectedVoltDivision;
	int16_t previousTriggerPos;
	std::array<VertLine, PANEL_X> graph;
	bool graphPresent;

	void drawLine(uint16_t x, VertLine line1, VertLine line2, VertLine clearLine );
	uint16_t getClearColor(uint16_t x, uint16_t y);
	void drawVerticalDivisor(uint16_t x){
		lcd.drawLine(x, 0, x, lcd.getHeight()-1);
	}
	void drawVoltDivisor(uint16_t y){
		lcd.drawLine(0, y, PANEL_X-1,y);
	}

	void removePrevTrigger();
	void drawTrigger();
	void drawGraphBackground();
};

