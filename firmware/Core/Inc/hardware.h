/*
 * hardware.h
 *
 *  Created on: Jan 1, 2022
 *      Author: paolo
 */

#ifdef __cplusplus

#pragma once

#include "main.h"
#include <string.h>
#include <math.h>

enum PORT {
	P_RS, P_RST, P_CS
};

enum PIN {
	B_RS, B_RST,B_CS
};


constexpr void setPort(PORT port, PIN pin, GPIO_PinState pinState) {
	if (port == P_RS && pin == B_RS) {
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, pinState);
	}
	if (port == P_RST && pin == B_RST) {
		HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, pinState);
	}
	if (port == P_CS && pin == B_CS) {
		HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, pinState);
	}
}

constexpr void cbi(PORT port, PIN pin) {
	setPort(port, pin, GPIO_PIN_RESET);
}

constexpr void sbi(PORT port, PIN pin) {
	setPort(port, pin, GPIO_PIN_SET);
}
constexpr void selCmd() {
	LCD_RS_GPIO_Port->BSRR = (uint32_t)LCD_RS_Pin << 16U;
}

constexpr void selData() {
	LCD_RS_GPIO_Port->BSRR = (uint32_t)LCD_RS_Pin;
}

constexpr void writeLcdDataBus(uint16_t value){
	LCD_D0_GPIO_Port->ODR = value;
}


inline void wrCycle() {
	// 1 cpu cycle: 5.9593 ns
	// write cycle requested: 66 ns -> 12 cpu


}



inline void delay(uint32_t ms){ HAL_Delay(ms);}


constexpr void swap(uint16_t i, uint16_t j){
	uint16_t t=i;
	i=j;
	j=t;
}

constexpr void swap(int i, int j){
	int t=i;
	i=j;
	j=t;
}


#define  pulseLow()  \
	LCD_WR_GPIO_Port->BSRR = (uint32_t)LCD_WR_Pin << 16U; \
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n"); \
	LCD_WR_GPIO_Port->BSRR = (uint32_t)LCD_WR_Pin; \
	__asm("NOP\nNOP\nNOP\nNOP\nNOP\n");




#endif

