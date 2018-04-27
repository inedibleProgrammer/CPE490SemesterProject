/***************************************************************************************************
Notes: 
***************************************************************************************************/

#include "SegmentDisplay.h"
#include "Constants.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
// struct Displays displays;

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
void ClearSegments(struct Displays* displays)
{
    displays->hex5 = GetSegments(0);
    displays->hex4 = GetSegments(0);
    displays->hex3 = GetSegments(0);
    displays->hex2 = GetSegments(0);
    displays->hex1 = GetSegments(0);
    displays->hex0 = GetSegments(0);
}

unsigned char GetSegments(unsigned char number)
{
    unsigned char segments;

    switch(number)
    {
        case 255: // clear a segment
            segments = 0b00000000;
            break;
        case 0:
            segments = 0b00111111;
            break;
        case 1:
            segments = 0b00000110;
            break;
        case 2:
            segments = 0b01011011;
            break;
        case 3:
            segments = 0b01001111;
            break;
        case 4:
            segments = 0b01100110;
            break;
        case 5:
            segments = 0b01101101;
            break;
        case 6:
            segments = 0b01111101;
            break;
        case 7:
            segments = 0b00000111;
            break;
        case 8:
            segments = 0b01111111;
            break;
        case 9:
            segments = 0b01101111;
            break;
    }
    return segments;
}

void PutSegments(struct Displays* displays)
{
    volatile int* hex5Ptr = (int*)HEX5_HEX4_BASE;
    volatile int* hex3Ptr = (int*)HEX3_HEX0_BASE;

    *(hex5Ptr) = ( (displays->hex5 << 8) | (displays->hex4) );
    *(hex3Ptr) = ( (displays->hex3 << 24) | (displays->hex2 << 16) | (displays->hex1 << 8) | (displays->hex0) );
}

/*
void ShiftSegments(unsigned char number)
{
    displays.hex5 = displays.hex4;
    displays.hex4 = displays.hex3;
    displays.hex3 = displays.hex2;
    displays.hex2 = displays.hex1;
    displays.hex1 = displays.hex0;
    displays.hex0 = number;
}

*/

