/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>
#include <p33FJ12GP201.h>

#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void) {
    /* Setup analog functionality and port direction */
    // ADC
    TRISAbits.TRISA4=1;
    AD1PCFGLbits.PCFG0=1;
    AD1CON2bits.VCFG=0;
    AD1CON3bits.ADCS=5; // TAD ->> 99 nsec
    AD1CON2bits.CHPS =0; // Only CH0
    AD1CHS0bits.CH0NA=0;  // CH0 neg is VREF-
    AD1CHS0bits.CH0SA=0;  // CH0 pos is AN0
    AD1CON1bits.SSRC=2;  // GP TMR3
    AD1CON1bits.ASAM =1;
    AD1CON1bits.FORM=0;
    
    IFS0bits.AD1IF=0;
    IEC0bits.AD1IE=1;
    
    // Data Ready
    TRISBbits.TRISB7=0;
    /* Initialize peripherals */
    
    // SPI
    TRISBbits.TRISB14=1; // SDI1
//    TRISBbits.TRISB1=0; // SDO1
    TRISBbits.TRISB15=1; // SCK1
    PORTBbits.RB7 = 0;
    LATBbits.LATB7=0;
    RPOR7bits.RP14R=7;
    TRISBbits.TRISB7=0;
    RPINR20bits.SCK1R=15;
    
    SPI1BUF=0;
    IFS0bits.SPI1IF=0;
    IEC0bits.SPI1IE=1;
    SPI1CON1bits.SMP=0;
    SPI1CON1bits.SSEN=0;
    SPI1CON1bits.CKE=0;
    SPI1STATbits.SPIROV=0;
    SPI1CON1bits.MODE16=1;
    SPI1CON1bits.MSTEN=0;
    
    TMR3=0000;
    PR3=300;
    T3CON=0x8000;
}

