#include "leaManipulation.h"
#include <msp430.h>
#include <stdio.h>


long NewLEA_VAR outputZ[] = {0x00000000};// storing the output of the LEA, being 2^32 bits of data
short NewLEA_VAR xValue[]={Q15(1),Q15(1),Q15(-1),Q15(1)};// create a x variable this must have the same size as the yvalue 
short NewLEA_VAR yValue[]={Q15(0.3),Q15(0.2),Q15(-0.3),Q15(-0.2)};// create the y variable 
short NewLEA_VAR *input;//input for the LEA
LEA_STATUS status;// status variable to see if things are working
int main(){  
    WDTCTL = WDTPW + WDTHOLD;//stop the watchdog, as it shouldnt exist in this program
    PM5CTL0 &= ~LOCKLPM5;
    initLEA();// initalize lea
   // runt the numbers
    status = macBase(xValue,yValue, outputZ, input, 4);
    while(1);//while loop for fun
    return -1;
}
