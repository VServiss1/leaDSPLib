// Created by Vanessa Serviss
// Made listening to https://youtu.be/LICi1VaK7Bk?si=ulWkbSiXxWM2Mf9y


#include "leaDSPLib.h"

void intitLEACommandTable(){
    LEACNF0 = 0; //This is intalizing the First configure register, to be in an on state by emptying it 
    LEACNF1 = 0; //This is intalizing the second configure register, to be in an on state by emptying it
    LEACNF2 = leaSP;//This is giving the third configure register the LEA stack point so
                        //that it will be able to manipulate the memory, though do be know once this happens
                        // you shouldnt write into LEA memory without it being for LEA
}
void initLEA(){
    intitLEACommandTable();//this is seperated just incase yknow
    LEAPMCTL |= LEACMDEN;// This enables lea to start working  
    /*
    return statement ends the execution of a function and returns the control to the function from where it was called. 
    The return statement may or may not return a value depending upon the return type of the function. 
    For example, int returns an integer value, void returns nothing, etc
    */
    return;
}

void* leaAllocateMem(unsigned short int size){
    LEACNF2 -= size;
    return (void *)mpsAdrLea(LEACNF2);
}
void leaDeallocateMem(unsigned short int size){
    LEACNF2 += size;
}

void loopStatus(LEA_STATUS status){
    while (status != getStatus());
    return;
}
void loopSuccess(LEA_STATUS status){
    while (status != success){
        status = getStatus();
    }
    return;
}

LEA_STATUS getStatus(){
    //checkStatus();
    long int mask0 = LEACNF1;
    if(mask0 &= LEABUSY__READY != 0) return leaBusy;
    return success;
}

int codeInRam(){
    long int mask0 = LEACAP;
    if(mask0 &= LEAMSIZ_1 != 0){
        return true;
    }
    return false;
}


//This code is basic benchamrking for the DSP lib and starts a clock based USES TIMER A
void benchmarkStart(){
    TA0CTL = TASSEL__SMCLK + MC__UP;//
    TA_CTL |= TACLR;
}
//stops the benchmarking and returns the amount of clock cycles since then USES TIMER A
int benchmarkStop(){
    TA0CTL &= ~MC_3
    return TACTR;
}



LEA_STATUS loadCommand(short int commandNum, const short int *input){
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=commandNum;
    return getStatus();
}
//Group 1
LEA_STATUS addMatrixShort(signed short* x, signed short* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;// This is the start of something terrible
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__ADDMATRIX;
    return getStatus();
}
LEA_STATUS addMatrixLong(signed long* x, signed long* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__ADDLONGMATRIX;
    return getStatus();
}
LEA_STATUS subMatrixShort(signed short* x, signed short* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__SUBMATRIX;
    return getStatus();
}
LEA_STATUS subMatrixLong(signed long* x, signed long* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__SUBLONGMATRIX;
    return getStatus();
}
//They are technically different since one is taking 16 bit while mul is taking Q15/Q31 for some reason
LEA_STATUS mulMatrixShort(signed short* x, signed short* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MPYMATRIX;
    return getStatus();
}
LEA_STATUS mulMatrixLong(signed long* x, signed long* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MPYLONGMATRIX;
    return getStatus();
}
LEA_STATUS mulMatrixComplex(signed long* x, signed long* y, signed long* outputZ,  short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MPYCOMPLEXMATRIX;
    return getStatus();
}


//Group 2
LEA_STATUS macBase(signed short* x, signed short* y, signed long* outputZ, short *input,
    unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAC;
    return getStatus();
}
LEA_STATUS macThree(signed short* x, signed short* y, signed long* outputZ, short *input,
    unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAC3;
    return getStatus();
}
LEA_STATUS macSF(signed short* x, signed short* y, double SF, signed long* outputZ,  
    short *input,unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = Q15(SF);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__SCALEDMAC;
    return getStatus();
}


//group 3
LEA_STATUS macMatrixShort(signed short* x, signed short* y, signed long* outputZ, short *input,
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MACMATRIX;
    return getStatus();
}
LEA_STATUS macMatrixLong(signed long* x, signed long* y, signed long* outputZ, short *input,
    short offsetX,short offsetY, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MACLONGMATRIX;
    return getStatus();
}
LEA_STATUS macMatrixComplex(signed short* x, signed short* y, signed long* outputZ, short *input, 
    short offsetX,short offsetY, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MACCOMPLEXMATRIX;
    return getStatus();
}
LEA_STATUS macMatrixComplexConjugated(signed short* x, signed short* y, signed long* outputZ, short *input,
    short offsetX,short offsetY, unsigned short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MACCOMPLEXCONJUGATEMATRIX;
    return getStatus();
}//Though I understand the redundancy of this, it will create a better user experience


//group 4
LEA_STATUS maxVectorShort(signed short* x, signed long *outputZ, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAX;
    return getStatus();
}
LEA_STATUS unsignedMaxVectorShort(unsigned short* x,signed long *outputZ, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNED;
    return getStatus();
}
LEA_STATUS minVectorShort(signed short* x, signed long *outputZ, short *input, short size){ 
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MIN;
    return getStatus();
}
LEA_STATUS unsignedMinVectorShort(unsigned short* x,
        signed long *outputZ, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNED;
    return getStatus();
}


//group 5
LEA_STATUS maxVectorLong(signed long* x, signed long *outputZ, short *input, 
    signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAXLONGMATRIX;//why have thou add matrix to end of this :(
    return getStatus();
}
LEA_STATUS unsignedMaxVectorLong(unsigned long* x, signed long *outputZ, short *input, 
    signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNEDLONGMATRIX;
    return getStatus();
}
LEA_STATUS minVectorLong(signed long* x, signed long *outputZ, 
        short *input, signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MINLONGMATRIX;
    return getStatus();
}
LEA_STATUS unsignexMinVectorLong(unsigned long* x, signed long *outputZ, short *input,
     signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNEDLONGMATRIX;
    return getStatus();
}


//group 6
LEA_STATUS maxVectorDual(signed short* x, signed long *outputZ, short *input, signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAXMATRIX;//guess we doing matrix now
    return getStatus();
}
LEA_STATUS unsignedMaxVectorDual(unsigned short* x,signed long *outputZ, short *input, 
    signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNEDMATRIX;
    return getStatus();
}
LEA_STATUS minVectorDual(signed short* x, signed long *outputZ, short *input, signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MINMATRIX;
    return getStatus();
}
LEA_STATUS unsignedMinVectorDual(unsigned short* x,signed long *outputZ, 
    short *input, signed short offset, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNEDMATRIX;
    return getStatus();
}


//group 7
LEA_STATUS firShort(signed short* x, signed short* coefs, unsigned short* outputZ,  short *input,
     short filterLength, short mask, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FIR;
    return getStatus();
}
LEA_STATUS firLong(signed long* x, signed long* coefs, unsigned long* outputZ, short *input,
         long filterLength, long mask, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FIRLONG;
    return getStatus();
}
LEA_STATUS firComplexShort(signed short* x, signed short* coefs, unsigned short* outputZ,  short *input,
        short filterLength, short mask, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FIRCOMPLEX;
    return getStatus();
}
LEA_STATUS firComplexLong(signed long* x, signed long* coefs, unsigned long* outputZ,  short *input,
            long filterLength, long mask, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FIRCOMPLEXLONG;
    return getStatus();
}
LEA_STATUS firScaled(signed short* x, signed short* coefs, unsigned short* outputZ, short *input, short filterLength, 
            short mask, short SF, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = SF;//scale factor 
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__SCALEDFIR;
    return getStatus();
}


//Group 8
LEA_STATUS polynomialShort(signed short* x, signed short* coefs,signed short* outputZ, short *input,
     short order, short SF, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*7);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&coefs);
    input[5] = order;
    input[6] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIAL;
    return getStatus();
}
LEA_STATUS polynomialLong(signed long* x, signed long* coefs, signed long* outputZ, short *input,
     long order, long SF, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*7);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&coefs);
    input[5] = order;
    input[6] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIALLONG;
    return getStatus();
}


//group 9
LEA_STATUS fftComplexFSc(signed short* x, short *input, short logNumber, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FFTCOMPLEXAUTOSCALING;
    return getStatus();
}
LEA_STATUS fftComplexASc(signed short* x,  short *input,short logNumber, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FFTCOMPLEXFIXEDSCALING;
    return getStatus();
}
LEA_STATUS fftComplexLong(signed long* x, short *input, long logNumber, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FFTCOMPLEXLONG;
    return getStatus();
}


//group 10 (this is my favourite group)
LEA_STATUS bitReverseShortEven(signed short* x, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;//why are these bits reserved I asked
                //I was then shot 19 times remembering that these need atleast 4
                //the upper section has one without the reserve bit being 7 in length
                //and i cried for this was not designed for the user, 
                //this was designed for the sinner such as I
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXEVEN;
    return getStatus();
}
LEA_STATUS bitReverseShortOdd(signed short* x, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXODD;
    return getStatus();
}
LEA_STATUS bitReverseLongEven(signed long* x, short *input, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXLONGEVEN;
    return getStatus();
}
LEA_STATUS bitReverseLongOdd(signed long* x, short *input, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXLONGODD;
    return getStatus();
}


//Group 11
LEA_STATUS fftShort(signed short* x, short *input, short logNumber, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FFT;
    return getStatus();
}
LEA_STATUS fftLong(signed long* x, short *input, long logNumber, long size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__FFTLONG;
    return getStatus();
}


//group 12
LEA_STATUS deinterleaveEvenEven(signed short* x, short* outputZ, short *input, short interleaveDepth, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;//why is this reserved????????????
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEEVENEVEN;
    return getStatus();
}
LEA_STATUS deinterleaveEvenOdd(signed short* x, short* outputZ, short *input, short interleaveDepth, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEEVENODD;
    return getStatus();
}
LEA_STATUS deinterleaveOddEven(signed short* x,short* outputZ, short *input, short interleaveDepth, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEODDEVEN;
    return getStatus();
}
LEA_STATUS deinterleaveOddOdd(signed short* x, short* outputZ, short *input, short interleaveDepth, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEODDODD;
    return getStatus();
}
LEA_STATUS deinterleaveLong(signed long* x,long* outputZ, short *input, short interleaveDepth, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVELONG;
    return getStatus();
}


//Group A
LEA_STATUS moveLongList(signed short* x, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*2);
    input[0] = adrLea(&x);
    input[1] = size;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[1]); 
    LEAPMCBL=LEACMD__MOVELONGLIST;
    return getStatus();
}
void suspendLEA(){
    LEAPMCBL=LEACMD__SUSPEND;
}
void resumeLEA(){
    LEAPMCBL=LEACMD__RESUME;
}


//Group B
LEA_STATUS mulMatrixRows(signed short* row, signed short* col, short* outputZ,  short *input,
    short rowSize, short colSize){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*7);
    input[0] = adrLea(&row);
    input[1] = RESERVED;// please dont come near me or my reserved bits EVER AGAIN
    input[2] = rowSize;
    input[3] = colSize;
    input[4] = adrLea(&col);
    input[5] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__MPYMATRIXROW;
    return getStatus();
}
LEA_STATUS polynomialScalar(signed short* x, short *input,
    signed short* coeffs,  short order, short SF){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = adrLea(&coeffs);
    input[2] = order;
    input[3] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIALSCALAR;
    return getStatus();
}
LEA_STATUS directFormOneStruct(signed short* x, signed short* state,signed short* coeffs, signed short* outputZ, short *input,
                unsigned short direction, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);//cool outputZ is #4. gotcha, I hope there is no more address after this
    input[4] = adrLea(&state); // OH GOOD HEAVENS :(
    input[5] = adrLea(&coeffs);
    input[6] = direction;
    input[7] = RESERVED;//reserved, why? no clue i didnt design these
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ1;
    return getStatus();
}
LEA_STATUS directFormTwoStruct(signed short* x, signed short* state,
            signed short* coeffs, signed short* outputZ,  short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&state);
    input[5] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ2;
    return getStatus();
}
LEA_STATUS directFormTwoStructExt(signed short* x, signed short* state,
            signed short* coeffs, signed short* outputZ, short *input, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&state);
    input[5] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ2EXTENDED;
    return getStatus();
}
LEA_STATUS windowLea(signed short* x, signed short* coeffs,  short *input, short tapSize, short size){
    LEA_STATUS current = getStatus();
    if (current != success) return current;
    
    input = (short*)malloc(sizeof(short)*5);
    input[0] = adrLea(&x);
    input[1] = RESERVED;// reserved bits my beloved :)
    input[2] = size;
    input[3] = tapSize;
    input[4] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=adrLea(&input[2]); 
    LEAPMCBL=LEACMD__WINDOW;
    return getStatus();
}//This is basically just a lot of weird minotia of text that makes it a bit less of a headache to have them exist,
// just remembering the reserved bits would not be fun

//>:3
