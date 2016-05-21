/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    // Init PWML1 to half the clock
    PDC1=2;
    PTPER=1;
    OVDCONbits.POVD1L=1;
    PWMCON1bits.PEN1L=1;
    PTCONbits.PTEN=1;
    
    TRISB=0xFFFF;
    ADPCFG=0x1FF;
}

