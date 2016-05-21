/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>
#define FCY 40000000ULL //Fcy = (Fosc/2) Fosc = 80MHz
#include <libpic30.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

uint8_t bufferData[512];
uint8_t * bufferEnd;
uint8_t * writeBuffer;
uint8_t * readBuffer;
uint16_t bufferLen;

void configureOscillator(void) {
    PLLFBD = 30; // M = 32
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2

    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);
}

void Delay1Second(void);
void SetupClock(void);

int16_t main(void) {
 //   configureOscillator();
    /* Initialize IO ports and peripherals */
    
    TRISBbits.TRISB7 = 0;
     while(1)
    {
        LATBbits.LATB7 = 1;
        Delay1Second();
        LATBbits.LATB7 = 0;
        Delay1Second();
    }
    return 0;
  
    InitApp();
    bufferEnd = bufferData + 512;
    writeBuffer = bufferData;
    readBuffer = bufferData;
    bufferLen = 0;

    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;

    while (1) {
        /*
        if (bufferLen > 10 && LATBbits.LATB7 == 0) {
            __builtin_disi(20);
            PORTBbits.RB7 = 1;
            SPI1BUF = *((uint16_t *) readBuffer);
            SPI1STATbits.SPIEN = 1;
            readBuffer++;
            readBuffer++;
            bufferLen--;
            bufferLen--;
        }
        */
    }
}

void Delay1Second()
{
    int i;
    for(i=0;i<100;i++)
    {
        __delay_ms(10);
    }
}