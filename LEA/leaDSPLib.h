/*
Lea library header file
Created: Vanessa Serviss
Made so far:
Initialization for lea
enabling low powermode
status
allocation 
commands
some flag stuff 
Work left to do:
allocation of the variables 
*/

#ifndef LEAMANIPULATION_H
#define LEAMANIPULATION_H

#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>


//memory addressomg
#define mpsAdrLea(x)   ((uintptr_t)(((uint32_t)(x) << 2))) // turns a lea address into something useable by the average person 
#define adrLea(x) ((unsigned short)((unsigned long)(x) & 0xffff) >> 2) // turns a regualar address in memory to something the LEA can use
//#define LEA_EPRG(x) _Pragma(#x) // auxiliary definition for NewLEA

#define NewLEA_VAR __attribute__((section(".leaRAM")))// This sets a new lea variable this is meant for GCC MSP430 Compiler

//useful
#define Q15(x) short((x)<1.0? ((x)>-1.0? (x)*0x8000:0x8000):0x7FFF) //Mathematical correct version of q15
#define Q15c(x) short((((x)<1? ((x)>=-1 ? (x)*0x8000:0x8000):0x7FFF))) //Ceiling rounded version
#define Q15f(x) short((x)>=0? ((x)>=1 ? 0x7FFF:(x)*0x7FFF):((x)<=-1? 0x8000:(x)*0x8000)) //Floor rounded
#define Q31(x) long ((x) < 1.0 ? ((x) > -1.0 ? (x) * 0x80000000 : 0x80000000) : 0x7FFFFFFF) // This makes a decimal into a long interger which is more workable for LEA
#define Q31c(x) (((x)<1? ((x)>=-1 ? (x)*0x80000000:0x80000000):0x7FFFFFFF))) //Ceiling rounded
#define Q31f(x) long((x)>=0? ((x)>=1.0? 0x7FFFFFFF:(x)*0x7FFFFFFF):((x)<=-1.0? 0x80000000:(x)*0x80000000))
#define IQ16_15(x) (x)<32768? ((x)>=-32768 ? (x)*0x8000:0x80000000):0x7FFFFFFF
#define leaSP 0x3C00 / 4 // This is the top memory address of the LEA
#define leaBottomMem (*((const uint16_t *)(&LEAMB))) //checks lea top#define Q15(x) short ((x)<1.0? ((x)>-1.0? (x)*0x8000:0x8000):0x7FFF) // This is soley to turn decimal numbers into actual usable varaible for LEA
#define leaTopMem (*((const uint16_t *)(&LEAMT))) // checks ;ea npttp,
#define inRangeLeaMem(x) (((uintptr_t)(x) >= leaBottom) && ((uintptr_t)(x) < leaTop)) // Checks whether it is in range for LEA 
#define leaAlignment(x, allign)   (!((uint32_t)(x) & ((allign)-1)))//This take the address and check if it has proper allignment based on n where n is the allignment 
#define validAddress(x, allign)   (inRangeLeaMem(x) & leaAlignment(x,allign)) //This checks whether or not that this could be a valid address
#define saturate(x, min, max)   (((x)>(max))?(max):(((x)<(min))?(min):(x)))

//deallocate and allocate memory onto the lea stack
void* leaAllocateMem(unsigned short int size);
void leaDeallocateMem(unsigned short int size);

// initalizes LEA command table making you use the table
void intiLeaCommandTable();
// initalizes LEA this should be the first thing you do before interacting with the rest of the code base
void initLEA();

// These turn on or off whether lea will work in Low power mode, either in interupts only or always _INT being interupts only
// There is also the ability to turn them off which I dont know why youd do it but i give the option
// do note I'm evil, you have to put a ; after calling these
#define enableLPMLEA LEAITFLG |= LEALPR
#define enableLPMLEA_INT LEAITFLG |= LEAILPM
#define disableLMPLEA LEAITFLG &= ~LEALPR
#define disableLMPLEA_INT LEAITFLG &= ~LEAILPM

/*
status checking for LEA so we can know whats happening
*/
// status of lea
typedef enum{
    /*
    implemented
    */
    success = 0,
    leaBusy = 1,
    /*
    unimplemented
    */
    shiftSizeError = 2,
    tableSizeError = 3,
    sizeError = 4,
    leaInvalidAddress = 5,
    leaOutOfRange = 6,
    leaScalarInconsistency = 7,
    leaCommandOverflow = 8,
    /*
    i dont think this one matters\
    */
    leaIncorrectRevision = 9
}LEA_STATUS;

/*
a while loop until we hit the status is true
this should mainly be used to loop for success while lea busy, though can be used to loop for error testing
*/
void loopStatus( LEA_STATUS status); // LEACMDSTAT
// This is a status check until lea is done
void loopSuccess(LEA_STATUS status);
// This just gets lea status
LEA_STATUS getStatus();
int codeInRam();


//This code is basic benchamrking for the DSP lib and starts a clock based
void benchmarkStart();
//stops the benchmarking 
int benchmarkStop();




// generic code loader
// This generic will work for all but moveLongList though that would be possible if this used a struct system
// which might come eventually
LEA_STATUS loadCommand(short int commandNum, const short int *input);


// Basic Vector and Matrix math
//  group 1 as explained
LEA_STATUS addMatrixShort(signed short *x, signed short *y, signed long *outputZ,  short *input,
                     short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS addMatrixLong(signed long *x, signed long *y, signed long *outputZ,  short *input,
                         short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS subMatrix(signed short *x, signed short *y, signed long *outputZ,  short *input,
                     short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS subMatrixLong(signed long *x, signed long *y, signed long *outputZ,  short *input,
                         short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS mulMatrixShort(signed short *x, signed short *y, signed long *outputZ,  short *input,
                     short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS mulMatrixLong(signed long *x, signed long *y, signed long *outputZ,  short *input,
                         short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS mulMatrixComplex(signed long *x, signed long *y, signed long *outputZ,  short *input,
                            short offsetX, short offsetY, short offsetZ, unsigned short size);

// MAC
//  group 2 which focus on MAC math with vectors
LEA_STATUS macBase(signed short *x, signed short *y, signed long *outputZ, short *input, unsigned short size); // this creates an array of memory addresses and reserved bits to help
LEA_STATUS macThree(signed short *x, signed short *y, signed long *outputZ, short *input, unsigned short size);
LEA_STATUS macSF(signed short *x, signed short *y, double SF, signed long *outputZ,  short *input, unsigned short size); // MAC 3 with a scale factor

// MAC Matrix
//  group 3 which focuses on MAC math for vectors
LEA_STATUS macMatrixShort(signed short *x, signed short *y, signed long *outputZ, short *input,
                          short offsetX, short offsetY, short offsetZ, unsigned short size);
LEA_STATUS macMatrixLong(signed long *x, signed long *y, signed long *outputZ, short *input,
                         short offsetX, short offsetY, unsigned short size);
LEA_STATUS macMatrixComplex(signed short *x, signed short *y, signed long *outputZ, short *input,
                            short offsetX, short offsetY, unsigned short size);
LEA_STATUS macMatrixComplexConjugated(signed short *x, signed short *y, signed long *outputZ, short *input,
                                      short offsetX, short offsetY, unsigned short size);

// Max and Mins group
//  this is group 4 - 6 which focuses on finding different assortment of maximums and minimums each function can be used for either min or max functions
//  like I get this is meant to break down but why did they get 3 groups
LEA_STATUS maxVectorShort(signed short *x, signed long *outputZ, short *input, short size);
LEA_STATUS unsignedMaxVectorShort(unsigned short *x, signed long *outputZ, short *input, short size);
LEA_STATUS minVectorShort(signed short *x, signed long *outputZ, short *input, short size);
LEA_STATUS unsignedMinVectorShort(unsigned short *x, signed long *outputZ, short *input, short size);
// seperator for group
LEA_STATUS maxVectorLong(signed long *x, signed long *outputZ, short *input, signed short offset, short size);
LEA_STATUS unsignedMaxVectorLong(unsigned long *x, signed long *outputZ, short *input, signed short offset, short size);
LEA_STATUS minVectorLong(signed long *x, signed long *outputZ, short *input, signed short offset, short size);
LEA_STATUS unsignedMinVectorLong(unsigned long *x, signed long outputZ, short *input, signed short offset, short size);
// seperator for group
LEA_STATUS maxVectorDual(signed short *x, signed long *outputZ, short *input, signed short offset, short size);           // HATE HATE HATE
LEA_STATUS unsignedMaxVectorDual(unsigned short *x, signed long *outputZ, short *input, signed short offset, short size); // HATE HATE HATE
LEA_STATUS minVectorDual(signed short *x, signed long *outputZ, short *input, signed short offset, short size);           // HATE HATE HAT*E
LEA_STATUS unsignedMinVectorDual(unsigned short *x, signed long outputZ, short *input, signed short offset, short size); // HATE HATE HATE

// FIR and not the tree kind, its more the finite impulse response kind
//  this is for group 7 for smoothing out things
LEA_STATUS firShort(signed short *x, signed short *coefs, unsigned short *outputZ, short *input, short filterLength, short mask, short size);
LEA_STATUS firLong(signed long *x, signed long *coefs, unsigned long *outputZ, short *input, long filterLength, long mask, long size);
LEA_STATUS firComplexShort(signed short *x, signed short *coefs, unsigned short *outputZ, short *input, short filterLength, short mask, short size);
LEA_STATUS firComplexLong(signed long *x, signed long *coefs, unsigned long *outputZ, short *input, long filterLength, long mask, long size);
LEA_STATUS firScaled(signed short *x, signed short *coefs, unsigned short *outputZ, short *input, short filterLength, short mask, short SF, short size);

// polynomial math for Taylor Math on vector and matries
//  I can only spell polynomeel once in the a millenium
// group 8
LEA_STATUS polynomialShort(signed short *x, signed short *coefs, signed short *outputZ, short *input, short order, short SF, short size);
LEA_STATUS polynomialLong(signed long *x, signed long *coefs, signed long *outputZ, short *input, long order, long SF, short size);

// FFT math initialization
// Group 9 :)
// FFT complex Auto scaling
LEA_STATUS fftComplexASc(signed short *x, short *input, short logNumber, short size);
// FFT complex Fixed scaling
LEA_STATUS fftComplexFSc(signed short *x, short *input, short logNumber, short size);
LEA_STATUS fftComplexLong(signed long *x, short *input, long logNumber, long size);

// Bit Reversed Pre-Sort Functions for FFTs
// group 10
LEA_STATUS bitReverseShortEven(signed short *x, short *input, short size);
LEA_STATUS bitReverseShortOdd(signed short *x, short *input, short size);
LEA_STATUS bitReverseLongEven(signed long *x, short *input, long size);
LEA_STATUS bitReverseLongOdd(signed long *x, short *input, long size);
/*
Group 11
This is the primary and normal FFT input and FFT long, as it doesnt use scaling factors
*/
LEA_STATUS fftShort(signed short *x, short *input, short logNumber, short size);
LEA_STATUS fftLong(signed long *x, short *input, long logNumber, long size);

// group 12 AKA De-Interleave and Sort Functions ... why would anyone use de interleaving????????
// Me :)
LEA_STATUS deinterleaveEvenEven(signed short *x, short *outputZ, short *input, short interleaveDepth, short size);
LEA_STATUS deinterleaveEvenOdd(signed short *x, short *outputZ, short *input, short interleaveDepth, short size);
LEA_STATUS deinterleaveOddEven(signed short *x, short *outputZ, short *input, short interleaveDepth, short size);
LEA_STATUS deinterleaveOddOdd(signed short *x, short *outputZ, short *input, short interleaveDepth, short size);
LEA_STATUS deinterleaveLong(signed long *x, long *outputZ, short *input, short interleaveDepth, short size);

// group A: Programming Structure Functions
/*
moving long lists
suppend is the big one since it just stops LEA operations and saves values to memory
resume resumes LEA from suspend
*/
LEA_STATUS moveLongList(signed short *x, short *input, short size);
void suspendLEA(); // amazing
void resumeLEA();  // massive

// This is kinda just random stuff that gives me a headache aka group B
/*
This is primarily an assortment of math functions that can make the upper functions more percise
or stuff not includable in the other groups
*/
// This is mainly if there is a different number of rows to the amount of collomns there is
LEA_STATUS mulMatrixRows(signed short *row, signed short *col, short *outputZ, short *input, short rowSize, short colSize);
/*
This "Polynomial result of vector X and Vector C are written to vector register LEAPMDST using a 32-bit signed
fractional multiplication of powers of X and pointwise values of C followed by a 32-bit accumulation and a scaling
multiplication" whatever that means
aka this just takes a long poly----- and a coefs vector and writes it to LEAPMDST(this is the vector write register),
with an order and scalefactor
*/
LEA_STATUS polynomialScalar(signed short *x, signed short *coeffs, short *input, short order, short SF);
// This is just for Direct form 1 processing in the LEA
LEA_STATUS directFormOneStruct(signed short *x, signed short *state, signed short *coeffs, signed short *outputZ, short *input, unsigned short direction, short size);
// Direct form 2 processing functions in the LEA
LEA_STATUS directFormTwoStruct(signed short *x, signed short *state, signed short *coeffs, signed short *outputZ, short *input, short size);
// Direct Form 2 structure processing extended
LEA_STATUS directFormTwoStructExt(signed short *x, signed short *state, signed short *coeffs, signed short *outputZ, short *input, short size);
// This is for a tappering function in a pointwise form
LEA_STATUS windowLea(signed short *x, signed short *coeffs, short *input, short tapSize, short size);

/*
This is the end of the initalization of section of the Library
The next section will be dedicated to the utilization of all of the functions
this will be incredibly long though
so this is the longer portion
*/

// define random constants that will be helpful while programming with LEA
#define RESERVED 0           // This is primarily for the functions
#define sInt16Max 0x7FFF     // signed int 16 max
#define sInt16Min 0x8000     // signed int 16 min
#define sInt32Max 0x7FFFFFFF // signed int 32 max
#define sInt32Min 0x80000000 // signed int 32 min
#define pi 3.1415926536      // if you need it I guess
#define q15 short int
#define uq15 unsigned short int
#define q31 long int
#define uq31 unsigned long int
#define q15NegOne 0xB000
#define q31NegOne 0xE000
#define addressZeroLea 0xA000
#define addressOneLea 0xAC00
#define leaInUse 1 //idk I just want this
#define true 1
#define false 0


#endif

/*
The registers explained (text of the gods)
https://www.ti.com/lit/ug/slau853/slau853.pdf?ts=1742975720264&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FMSP430FR6047%253Futm_source%253Dgoogle%2526utm_medium%253Dcpc%2526utm_campaign%253Depd-null-null-gpn_en-cpc-pf-google-soas%2526utm_content%253Dmsp430fr6047%2526ds_k%253D%257B_dssearchterm%257D%2526DCM%253Dyes
The functions explained
https://www.ti.com/lit/ug/slau850/slau850.pdf?ts=1741370207534
*/