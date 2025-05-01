#include "leaManipulation.h"
#include <msp430.h>
#include <stdio.h>


long NewLEA_VAR outputZ[] = {0x00000000};// storing the output of the LEA, being 2^32 bits of data
//input for the LEA
short NewLEA_VAR xValue[]={Q15(1),Q15(1),Q15(-1),Q15(1)};// create a x variable this must have the same size as the yvalue 
short NewLEA_VAR yValue[]={Q15(0.3),Q15(0.2),Q15(-0.3),Q15(-0.2)};// create the y variable 
short NewLEA_VAR *input;
LEA_STATUS status;
//ALL OF THESE VALUES MUST BE Q15'd TO MAKE THEM USABLE FOR LEA AND THESE MOST BE SIGNED SHORTS
//at 430 at night... my serial monitor broke???
//love that
int main(){
    
    WDTCTL = WDTPW + WDTHOLD;//stop the watchdog, as it shouldnt exist in this program
    PM5CTL0 &= ~LOCKLPM5;
    configureClockAndUART();
    initLEA();// initalize lea
    //create an array of data the size being how many data points that are in the x and y values
    status = macBase(xValue,yValue, outputZ, input, 4);
    while(1);
    return -1;
}
