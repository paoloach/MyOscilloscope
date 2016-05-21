
#include <xc.h>
#include <stdint.h>
#include "ADCRead.h"

void Mps3ReadADC(void);
void Mps1ReadADC(void);
void Kps100ReadADC(void);

uint8_t triggerValue;
uint8_t triggerPos;
uint32_t samplesAvailables[] = {3000000,1000000};

void readADC(){
    Kps100ReadADC();
}
