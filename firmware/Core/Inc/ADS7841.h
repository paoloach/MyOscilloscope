/*
 * ADC.h
 *
 *  Created on: Jan 5, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <stdint.h>

enum class Channel {
	CH0,
	CH1,
	CH2,
	CH3
};

constexpr uint8_t CONTROL_ADC=0x87;

class ADS7841 {
public:
	void startContinuos(Channel ch1, Channel ch2);
	void endContinuos(){stop=true;}
	void endConversion();
	uint16_t getValue(Channel ch);
	bool error;
	uint16_t getLastValue1() const {return lastValues1;}
	uint16_t getLastValue2() const {return lastValues2;}

private:
	bool stop;
	uint8_t toSend[6];
	uint8_t received[6];
	uint16_t lastValues1;
	uint16_t lastValues2;

	uint8_t createControlCode(Channel ch);
};

