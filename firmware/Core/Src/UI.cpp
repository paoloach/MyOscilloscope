/*
 * UI.cpp
 *
 *  Created on: Jan 2, 2022
 *      Author: paolo
 */

#include <stdio.h>
#include "UI.h"
#include "Trigger.h"
#include "TimeDivisions.h"

extern TimeDivisions timeDivisions;

UI::UI():
	voltDivisions{vd1},
	selectedVoltDivision{0},
	previousTriggerPos{0},
	graphPresent{false}
{}

void UI::init() {

	previousTriggerPos = Trigger::pixelPos;

	lcd.InitLCD(Orientation::LANDSCAPE);

	lcd.setFont(&smallFont);

	drawGraphBackground();
	lcd.setColor(PANEL_COLOR);
	lcd.fillRect(PANEL_X, 0, lcd.getWidth()-1, lcd.getHeight()-1);

	lcd.setColor(PANEL_TEXT_COLOR);
	lcd.setBackColor(PANEL_COLOR);
	lcd.print("Time/div", TIME_LABEL);
	lcd.print("VOLT/div", VOLT_LABEL);
	lcd.print("Trigger", TRIGGER_LABEL);
	lcd.print("Type", TRIGGER_TYPE_LABEL);
	showVoltDivision();
	showTimeDivision();
	updateTrigger();
	showTriggerType(false);
}

void UI::printValue(const char * string) {
	lcd.setColor(PANEL_TEXT_COLOR);
	lcd.setBackColor(PANEL_COLOR);
	lcd.print(string, Point(PANEL_X+3, 300));
}

void UI::drawGraphBackground() {
	lcd.setColor(BACKGROUND);
	lcd.fillRect(0, 0, PANEL_X-1, lcd.getHeight()-1);
	lcd.setColor(LINE_DIVISOR_COLOR);
	drawVerticalDivisor(DIVISORY_1);
	drawVerticalDivisor(DIVISORY_2);
	drawVerticalDivisor(DIVISORY_3);
	drawVerticalDivisor(DIVISORY_4);
	drawVoltDivisor(DIVISOR_VOLT_1);
	drawVoltDivisor(DIVISOR_VOLT_2);
	drawVoltDivisor(DIVISOR_VOLT_3);
	drawVoltDivisor(DIVISOR_VOLT_4);
	updateTrigger();

}

void UI::showVoltDivision(bool selected) {
	if (selected){
		lcd.setColor(PANEL_COLOR);
		lcd.setBackColor(PANEL_TEXT_COLOR);
	} else {
		lcd.setColor(PANEL_TEXT_COLOR);
		lcd.setBackColor(PANEL_COLOR);
	}
	VoltDivision & voltDivision = voltDivisions[selectedVoltDivision];
	lcd.print(voltDivision.getName(), VOLT_VALUE);
	lcd.setBackColor(BACKGROUND);
	lcd.setColor(PANEL_COLOR);
	lcd.print(voltDivision.getLabel1(), VOLT_LABEL1);
	lcd.print(voltDivision.getLabel2(), VOLT_LABEL2);
	lcd.print(voltDivision.getLabel3(), VOLT_LABEL3);
	lcd.print(voltDivision.getLabel4(), VOLT_LABEL4);
}

void UI::showTimeDivision(bool selected) {
	if (selected){
		lcd.setColor(PANEL_COLOR);
		lcd.setBackColor(PANEL_TEXT_COLOR);
	} else {
		lcd.setColor(PANEL_TEXT_COLOR);
		lcd.setBackColor(PANEL_COLOR);
	}


	TimeDivision & timeDivision = timeDivisions.getCurrent();
	lcd.print(timeDivision.getLabel(), TIME_VALUE);
}

void UI::showTriggerType(bool selected){
	if (selected){
		lcd.setColor(PANEL_COLOR);
		lcd.setBackColor(PANEL_TEXT_COLOR);
	} else {
		lcd.setColor(PANEL_TEXT_COLOR);
		lcd.setBackColor(PANEL_COLOR);
	}

	if (Trigger::type == TriggerType::PositiveSlope){
		lcd.print("positive", TRIGGER_TYPE_VALUE);
	} else {
		lcd.print("negative", TRIGGER_TYPE_VALUE);
	}
}

void UI::updateTrigger(bool selected){
	lcd.setColor(PANEL_TEXT_COLOR);
	lcd.setBackColor(PANEL_COLOR);
	removePrevTrigger();
	VoltDivision & voltDivision = voltDivisions[selectedVoltDivision];
	char * triggerValue = voltDivision.getTriggerValue(0, getMaxTriggerPixel());

	if (selected){
		lcd.setColor(PANEL_COLOR);
		lcd.setBackColor(PANEL_TEXT_COLOR);
	} else {
		lcd.setColor(PANEL_TEXT_COLOR);
		lcd.setBackColor(PANEL_COLOR);
	}
	lcd.print(triggerValue, TRIGGER_VALUE);
	delete []triggerValue;
	drawTrigger();
	previousTriggerPos = Trigger::pixelPos;

}

void UI::removePrevTrigger() {
	uint16_t y = getMaxTriggerPixel()-previousTriggerPos;
	VoltDivision & voltDivision = voltDivisions[selectedVoltDivision];
	if (y == DIVISOR_VOLT_1){
		lcd.setColor(LINE_DIVISOR_COLOR);
		drawVoltDivisor(DIVISOR_VOLT_1);
		lcd.setBackColor(BACKGROUND);
		lcd.setColor(PANEL_COLOR);
		lcd.print(voltDivision.getLabel1(), VOLT_LABEL1);
	} else if(y == DIVISOR_VOLT_2){
		lcd.setColor(LINE_DIVISOR_COLOR);
		drawVoltDivisor(DIVISOR_VOLT_2);
		lcd.setBackColor(BACKGROUND);
		lcd.setColor(PANEL_COLOR);
		lcd.print(voltDivision.getLabel2(), VOLT_LABEL2);
	} else if (y == DIVISOR_VOLT_3){
		lcd.setColor(LINE_DIVISOR_COLOR);
		drawVoltDivisor(DIVISOR_VOLT_3);
		lcd.setBackColor(BACKGROUND);
		lcd.setColor(PANEL_COLOR);
		lcd.print(voltDivision.getLabel3(), VOLT_LABEL3);
	} else if(y == DIVISOR_VOLT_4){
		lcd.setColor(LINE_DIVISOR_COLOR);
		drawVoltDivisor(DIVISOR_VOLT_4);
		lcd.setBackColor(BACKGROUND);
		lcd.setColor(PANEL_COLOR);
		lcd.print(voltDivision.getLabel4(), VOLT_LABEL4);
	} else {
		uint8_t fontHeight = smallFont.getCharHeight();
		lcd.setColor(BACKGROUND);
		lcd.drawLine(0, y, PANEL_X-1, y);
		lcd.setColor(LINE_DIVISOR_COLOR);
		lcd.drawPixel(DIVISORY_1, y);
		lcd.drawPixel(DIVISORY_2, y);
		lcd.drawPixel(DIVISORY_3, y);
		lcd.drawPixel(DIVISORY_4, y);
		lcd.setBackColor(BACKGROUND);
		lcd.setColor(PANEL_COLOR);
		if (y >= VOLT_LABEL1.y && y <= VOLT_LABEL1.y+fontHeight){
			lcd.print(voltDivision.getLabel1(), VOLT_LABEL1);
		} else if (y >= VOLT_LABEL2.y && y <= VOLT_LABEL2.y+fontHeight){
			lcd.print(voltDivision.getLabel2(), VOLT_LABEL2);
		} else if (y >= VOLT_LABEL3.y && y <= VOLT_LABEL3.y+fontHeight){
			lcd.print(voltDivision.getLabel3(), VOLT_LABEL3);
		} else if (y >= VOLT_LABEL4.y && y <= VOLT_LABEL4.y+fontHeight){
			lcd.print(voltDivision.getLabel4(), VOLT_LABEL4);
		}
	}
}

void UI::drawTrigger() {
	lcd.setColor(TRIGGER_COLOR);
	lcd.drawLine(0, getMaxTriggerPixel()-Trigger::pixelPos, PANEL_X-1, getMaxTriggerPixel()-Trigger::pixelPos);
}



uint16_t UI::getClearColor(uint16_t x, uint16_t y){
	if (y == DIVISOR_VOLT_1 ||
			y == DIVISOR_VOLT_2 ||
			y == DIVISOR_VOLT_3 ||
			y == DIVISOR_VOLT_4){
		return LINE_DIVISOR_COLOR;

	} else if (x == DIVISORY_1 ||
			x == DIVISORY_2 ||
			x == DIVISORY_3 ||
			x == DIVISORY_4){
		return LINE_DIVISOR_COLOR;
	} else {
		return BACKGROUND;
	}
}

void UI::drawLine(uint16_t x, VertLine line1, VertLine line2, VertLine clearLine) {

	uint16_t minY = std::min( std::min(line1.minY,line2.minY ), clearLine.minY);
	uint16_t maxY= std::max( std::max(line1.maxY,line2.maxY ), clearLine.maxY);

	Bitmap bitmap(1, (maxY-minY));
	for(uint16_t y=minY; y < maxY; y++){
		if (y >= line1.minY && y <= line1.maxY){
			bitmap.put(Point(0, y-minY) , GRAPH_COLOR1);
		} else if (y >= line2.minY && y <= line2.maxY){
			bitmap.put(Point(0, y-minY) , GRAPH_COLOR2);
		} else {
			bitmap.put(Point(0, y-minY), getClearColor(x, y));
		}
	}
	lcd.drawBitmap(Point(x, minY), bitmap);
}

void UI::drawGraph(std::array<uint16_t, PANEL_X> * data1, std::array<uint16_t, PANEL_X> * data2){
	uint16_t x=0;
	uint16_t prevY1=lcd.getHeight();
	uint16_t prevY2=lcd.getHeight();
	VoltDivision voltDivision = voltDivisions[selectedVoltDivision];
	auto deleteGraphIter = graph.begin();
	auto data2Iter = data2->begin();
	for(auto iter = data1->begin(); iter != data1->end(); iter++){
		uint16_t y1 = voltDivision.convertToGraph(*iter, lcd.getHeight());
		if (y1 >=lcd.getHeight())
			y1 = lcd.getHeight()-1;
		y1 = lcd.getHeight()-y1;
		uint16_t y2 = voltDivision.convertToGraph(*data2Iter, lcd.getHeight());
		if (y2 >=lcd.getHeight())
			y2 = lcd.getHeight()-1;
		y2 = lcd.getHeight()-y2;

		VertLine line1(y1, prevY1);
		VertLine line2( y2, prevY2);
		drawLine(x, line1, line2, *deleteGraphIter);

		prevY1=y1;
		prevY2=y2;

		uint16_t minGraph = std::min( line1.minY, line2.minY);
		uint16_t maxGraph = std::max( line1.maxY, line2.maxY);
		*deleteGraphIter = VertLine(minGraph, maxGraph);
		data2Iter++;
		deleteGraphIter++;
		x++;
	}
	graphPresent=true;
}

