/*
 * ADC.cpp
 *
 *  Created on: Jan 5, 2022
 *      Author: Paolo Achdjian
 */

#include "spi.h"

#include "ADS7841.h"


extern ADS7841 ads7841;

static uint8_t nullData[2]={0,0};

uint32_t counterS;

extern "C"{
	void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
}

void ADS7841::startContinuos(Channel ch1, Channel ch2) {
	stop=false;
	HAL_GPIO_WritePin(ADC_CS_GPIO_Port, ADC_CS_Pin, GPIO_PIN_RESET);

	toSend[0] = createControlCode(ch1);
	toSend[1]=0;
	toSend[2]=0;
	toSend[3] = createControlCode(ch2);
	toSend[4]=0;
	toSend[5]=0;
	counterS++;
	HAL_DMA_Init(hspi1.hdmatx);
	HAL_DMA_Init(hspi1.hdmarx);
	HAL_SPI_TransmitReceive_DMA(&hspi1, toSend, received, 6);
}

uint8_t ADS7841::createControlCode(Channel ch){
	uint8_t controlCode = CONTROL_ADC;
	switch(ch){
		case Channel::CH0:
			controlCode |= 0x10;
			break;
		case Channel::CH1:
			controlCode |= 0x50;
			break;
		case Channel::CH2:
			controlCode |= 0x20;
			break;
		case Channel::CH3:
			controlCode |= 0x60;
			break;
	}
	return controlCode;
}

void ADS7841::endConversion(){
	lastValues1 = ( ((uint16_t)received[1]) << 8) + received[2];
	lastValues2 = ( ((uint16_t)received[4]) << 8) + received[5];
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	ads7841.endConversion();
}

// Prescalarer = 32
//  CLK=191ns up and 191ns down
// cycle (from CS down to CS up) = 9.125us -> 109kHz conversion rate
uint16_t ADS7841::getValue(Channel ch) {
	HAL_GPIO_WritePin(ADC_CS_GPIO_Port, ADC_CS_Pin, GPIO_PIN_RESET);
	error=false;
	uint8_t controlCode = CONTROL_ADC;
	switch(ch){
	case Channel::CH0:
		controlCode |= 0x10;
		break;
	case Channel::CH1:
		controlCode |= 0x50;
		break;
	case Channel::CH2:
		controlCode |= 0x20;
		break;
	case Channel::CH3:
		controlCode |= 0x60;
		break;
	}

	HAL_SPI_Transmit(&hspi1, &controlCode, 1, HAL_MAX_DELAY);

	uint8_t data[2];
	HAL_SPI_TransmitReceive(&hspi1, nullData, (uint8_t *)data, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(ADC_CS_GPIO_Port, ADC_CS_Pin, GPIO_PIN_SET);
	return ( ((uint16_t)data[0]) << 8) + data[1];

}
