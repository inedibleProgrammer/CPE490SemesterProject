/***************************************************************************************************
Notes: 
***************************************************************************************************/
#ifndef NUMBERS_H_
#define NUMBERS_H_

/***************************************************************************************************
Global Variables:
***************************************************************************************************/

/***************************************************************************************************
Structures:
***************************************************************************************************/
struct FractionalNumber
{
    int quotient;
    int remainder;
    int divisor;
};

struct Digits
{
    unsigned char thousands;
    unsigned char hundreds;
    unsigned char tens;
    unsigned char ones;
};

/***************************************************************************************************
Function Prototpes:
***************************************************************************************************/
/*
    DigitSeparator:
        * Converts any number into a struct Digits. This separates each digit into
          separate characters that can easily be printed to the screen.
*/
struct Digits DigitSeparator(int number);


#endif /* NUMBERS_H_ */