// Basic LEA manipulation Library... LEA is not directly supported in this house :(
// also turns out macOs doesnt support the DSP library whyyyyyy 
// Created by Vanessa Serviss
// Me when I lose executive function: https://youtu.be/LICi1VaK7Bk?si=ulWkbSiXxWM2Mf9y


#include "leaManipulation.h"


void initLEA(){
    LEACNF0 = 0; //This is intalizing the First configure register, to be in an on state by emptying it 
    LEACNF1 = 0; //This is intalizing the second configure register, to be in an on state by emptying it
    LEACNF2 = leaSP;//This is giving the third configure register the LEA stack point so
                        //that it will be able to manipulate the memory, though do be know once this happens you shouldnt write into LEA memory without it being for LEA
    LEAPMCTL |= LEACMDEN;// This enables lea to start working  
    /*
    return statement ends the execution of a function and returns the control to the function from where it was called. 
    The return statement may or may not return a value depending upon the return type of the function. 
    For example, int returns an integer value, void returns nothing, etc
    */
    return;
}

void loopStatus(LEA_STATUS status){
    while (status != getStatus());
    return status;
}
void loopSuccess(LEA_STATUS status){
    status = getStatus();
    while (status != success){
        status = getStatus();
    }
    return status;
}

LEA_STATUS getStatus(){
    LEA_STATUS retr = *leaStatusPTR;
    return retr;
}

//Group 1
LEA_STATUS addMatrixShort(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__ADDMATRIX;
    
}
LEA_STATUS addMatrixLong(signed long* x, signed long* y, long* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__ADDLONGMATRIX;
}
LEA_STATUS subMatrixShort(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__SUBMATRIX;
}
LEA_STATUS subMatrixLong(signed long* x, signed long* y, long* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__SUBLONGMATRIX;
}
//They are technically different since one is taking 16 bit while mul is taking Q15/Q31 for some reason
LEA_STATUS mulMatrixShort(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MPYMATRIX;
}
LEA_STATUS mulMatrixLong(signed long* x, signed long* y, long* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MPYLONGMATRIX;
}
LEA_STATUS mulMatrixComplex(signed long* x, signed long* y, long* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = offsetZ;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MPYCOMPLEXMATRIX
}


//Group 2
LEA_STATUS macBase(signed short* x, signed short* y, short* input, signed long* outputZ,unsigned short size){
    // memory adrress of x, reserved bit, the amount of arguements in each vector, memory address of y, memory address of outputZ, scale factor
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAC;
}
LEA_STATUS macThree(signed short* x, signed short* y, short* input, signed long* outputZ,unsigned short size){
    // memory adrress of x, reserved bit, the amount of arguements in each vector, memory address of y, memory address of outputZ, scale factor
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAC3;
}
LEA_STATUS macSF(signed short* x, signed short* y, double SF, short* input, signed long* outputZ, unsigned short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = Q15(SF);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__SCALEDMAC;
}


//group 3
LEA_STATUS macMatrixShort(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY,short offsetZ, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MACMATRIX;
}


LEA_STATUS macMatrixLong(signed long* x, signed long* y, long* input, signed long* outputZ, 
    short offsetX,short offsetY, unsigned short size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&y);
    input[4] = adrLea(&outputZ);
    input[5] = offsetX;
    input[6] = offsetY;
    input[7] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MACLONGMATRIX;
}


LEA_STATUS macMatrixComplex(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MACCOMPLEXMATRIX;
}
LEA_STATUS macMatrixComplexConjugated(signed short* x, signed short* y, short* input, signed long* outputZ, 
    short offsetX,short offsetY, unsigned short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MACCOMPLEXCONJUGATEMATRIX;
}//Though I understand the redundancy of this, it will create a better user experience


//group 4
LEA_STATUS maxVectorShort(signed short* x, short* input,signed long outputZ, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAX;
}

LEA_STATUS unsignedMaxVectorShort(unsigned short* x,short* input, signed long outputZ, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNED;
}
LEA_STATUS minVectorShort(signed short* x, short* input,signed long outputZ, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MIN;
}

LEA_STATUS unsignedMinVectorShort(unsigned short* x,short* input, signed long outputZ, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNED;
}
//group 5
LEA_STATUS maxVectorLong(signed long* x, long* input, signed long outputZ,signed short offset, short size){
    input = (long*)malloc(sizeof(long)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAXLONGMATRIX;//why have thou add matrix to end of this :(
}

LEA_STATUS unsignedMaxVectorLong(unsigned long* x,long* input, signed long outputZ,signed short offset, short size){
    input = (long*)malloc(sizeof(long)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNEDLONGMATRIX;
}
LEA_STATUS minVectorLong(signed long* x, long* input, signed long outputZ,signed short offset, short size){
    input = (long*)malloc(sizeof(long)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MINLONGMATRIX;
}

LEA_STATUS unsignexMinVectorLong(unsigned long* x,long* input, signed long outputZ,signed short offset, short size){
    input = (long*)malloc(sizeof(long)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = offset;
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNEDLONGMATRIX;
}
//group 6
LEA_STATUS maxVectorDual(signed short* x, short* input, signed long outputZ,signed short offset, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAXMATRIX;//guess we doing matrix now
}

LEA_STATUS unsignedMaxVectorDual(unsigned short* x,short* input, signed long outputZ,signed short offset, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MAXUNSIGNEDMATRIX;
}
LEA_STATUS minVectorDual(signed short* x, short* input, signed long outputZ,signed short offset, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MINMATRIX;
}

LEA_STATUS unsignedMinVectorDual(unsigned short* x,short* input, signed long outputZ,signed short offset, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = offset;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MINUNSIGNEDMATRIX;
}


//group 7
LEA_STATUS firShort(signed short* x, signed short* coefs, short* input, unsigned short* outputZ, short filterLength, short mask, short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FIR;
}

LEA_STATUS firLong(signed long* x, signed long* coefs, long* input, unsigned long* outputZ, long filterLength, long mask, long size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FIRLONG;
}
LEA_STATUS firComplex(signed short* x, signed short* coefs, short* input, unsigned short* outputZ, short filterLength, short mask, short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FIRCOMPLEX;
}

LEA_STATUS firComplexLong(signed long* x, signed long* coefs, long* input, unsigned long* outputZ, long filterLength, long mask, long size){
    input = (long*)malloc(sizeof(long)*8);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&coefs);
    input[4] = adrLea(&outputZ);
    input[5] = filterLength;
    input[6] = mask;
    input[7] = RESERVED; //reserved
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FIRCOMPLEXLONG;
}
LEA_STATUS firScaled(signed short* x, signed short* coefs, short* input, unsigned short* outputZ, short filterLength, short mask, short SF, short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__SCALEDFIR;
}
//Group 8
LEA_STATUS polynomialShort(signed short* x, signed short* coefs,short* input, signed short* outputZ, short order, short SF, short size){
    input = (short*)malloc(sizeof(short)*7);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&coefs);
    input[5] = order;
    input[6] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIAL;
}
LEA_STATUS polynomialLong(signed long* x, signed long* coefs, long *input, signed long* outputZ, long order, long SF, short size){
    input = (long*)malloc(sizeof(long)*7);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&coefs);
    input[5] = order;
    input[6] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIALLONG;
}
//group 9
LEA_STATUS fftComplexFSc(signed short* x, short* input, short logNumber, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FFTCOMPLEXAUTOSCALING;
}
LEA_STATUS fftComplexASc(signed short* x, short* input, short logNumber, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__LEACMD__FFTCOMPLEXFIXEDSCALING;
}
LEA_STATUS fftComplexLong(signed long* x, long* input, long logNumber, long size){
    input = (long*)malloc(sizeof(long)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FFTCOMPLEXLONG;
}
//group 10 (this is my favourite group)
LEA_STATUS bitReverseShortEven(signed short* x,short *input, short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXEVEN;
}
LEA_STATUS bitReverseShortOdd(signed short* x,short *input, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXODD;
}
LEA_STATUS bitReverseLongEven(signed long* x,long *input, long size){
    input = (long*)malloc(sizeof(long)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXLONGEVEN;
}
LEA_STATUS bitReverseLongOdd(signed long* x,long *input, long size){
    input = (long*)malloc(sizeof(long)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__BITREVERSECOMPLEXLONGODD;
}
//Group 11
LEA_STATUS fftShort(signed short* x, short* input, short logNumber, short size){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FFT;
}
LEA_STATUS fftLong(signed long* x, long* input, long logNumber, long size){
    input = (long*)malloc(sizeof(long)*4);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = logNumber;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__FFTLONG;
}
//group 12
LEA_STATUS deinterleaveEvenEven(signed short* x,short *input, short* outputZ, short interleaveDepth, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;//why is this reserved????????????
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEEVENEVEN;
}
LEA_STATUS deinterleaveEvenOdd(signed short* x,short *input, short* outputZ, short interleaveDepth, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEEVENODD;
}
LEA_STATUS deinterleaveOddEven(signed short* x,short *input, short* outputZ, short interleaveDepth, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEODDEVEN;
}
LEA_STATUS deinterleaveOddOdd(signed short* x,short *input, short* outputZ, short interleaveDepth, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVEODDODD;
}

LEA_STATUS deinterleaveLong(signed long* x,long* outputZ, long *input,short interleaveDepth, short size){
    input = (long*)malloc(sizeof(long)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = interleaveDepth;
    input[4] = adrLea(&outputZ);
    input[5] = RESERVED;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__DEINTERLEAVELONG;
}
//Group A
LEA_STATUS LEA_STATUS moveLongList(signed short* x,short *input, short size){
    (signed short* x,short *input, short size){
    input = (short*)malloc(sizeof(short)*2);
    input[0] = adrLea(&x);
    input[1] = size;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[1]); 
    LEAPMCBL=LEACMD__MOVELONGLIST;
}
LEA_STATUS suspendLEA(){
    LEAPMCBL=LEACMD__SUSPEND;
}
LEA_STATUS resumeLEA(){
    LEAPMCBL=LEACMD__RESUME;
}
//Group B
LEA_STATUS mulMatrixRows(signed short* row, signed short* col, short* input, short* outputZ, short rowSize, short colSize){
    input = (short*)malloc(sizeof(short)*7);
    input[0] = adrLea(&row);
    input[1] = RESERVED;// please dont come near me or my reserved bits EVER AGAIN
    input[2] = rowSize;
    input[3] = colSize;
    input[4] = adrLea(&col);
    input[5] = adrLea(&outputZ);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__MPYMATRIXROW;
}
LEA_STATUS polynomialScalar(signed short* x,signed short* coeffs, short *input, short order, short SF){
    input = (short*)malloc(sizeof(short)*4);
    input[0] = adrLea(&x);
    input[1] = adrLea(&coeffs);
    input[2] = order;
    input[3] = SF;
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__POLYNOMIALSCALAR;
}
LEA_STATUS directFormOneStruct(signed short* x, signed short* state,signed short* coeffs,short *input ,signed short* outputZ, unsigned short direction, short size){
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
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ1;
}
LEA_STATUS directFormTwoStruct(signed short* x, signed short* state,signed short* coeffs,short *input ,signed short* outputZ, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&state);
    input[5] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ2;
}
LEA_STATUS directFormTwoStructExt(signed short* x, signed short* state,signed short* coeffs,short *input ,signed short* outputZ, short size){
    input = (short*)malloc(sizeof(short)*6);
    input[0] = adrLea(&x);
    input[1] = RESERVED;
    input[2] = size;
    input[3] = adrLea(&outputZ);
    input[4] = adrLea(&state);
    input[5] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__IIRBQ2EXTENDED;
}
LEA_STATUS windowLea(signed short* x, signed short* coeffs, short* input, short tapSize, short size){
    input = (short*)malloc(sizeof(short)*5);
    input[0] = adrLea(&x);
    input[1] = RESERVED;// reserved bits my beloved :)
    input[2] = size;
    input[3] = tapSize;
    input[4] = adrLea(&coeffs);
    LEAPMS0L=input[0];
    LEAPMS1L=Ladr(&input[2]); 
    LEAPMCBL=LEACMD__WINDOW;
}//This is basically just a lot of weird minotia of text that makes it a bit less of a headache to have them exist, just remembering the reserved bits would not be fun



/*
>:3
*/