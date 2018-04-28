/***************************************************************************************************
Notes: 
***************************************************************************************************/
#include "Numbers.h"


/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
struct Digits DigitSeparator(int number)
{
    struct Digits numberSeparated;

    numberSeparated.thousands = number / 1000;
    numberSeparated.hundreds  = (number % 1000) / 100;
    numberSeparated.tens      = ((number % 1000) % 100) / 10;
    numberSeparated.ones      = (((number % 1000) % 100) % 10);

    return numberSeparated;
}