/***************************************************************************************************
Notes: 
    This may need to be tailored to fit this lab:
    * Do I need the global, "displays"?
***************************************************************************************************/
#ifndef SEGMENT_DISPLAY_H_
#define SEGMENT_DISPLAY_H_

/***************************************************************************************************
Structures:
***************************************************************************************************/
struct Displays
{
    unsigned char hex5;
    unsigned char hex4;
    unsigned char hex3;
    unsigned char hex2;
    unsigned char hex1;
    unsigned char hex0;

    // short hex54;
    // int hex30;
};

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
// extern struct Displays displays;


/***************************************************************************************************
Function Prototypes:
***************************************************************************************************/

/*
    InitSegments:
        * Sets all segments to 0
*/
void ClearSegments(struct Displays* displays);

/*
    GetSegments:
        * Converts 'number' into respective 7-segment display output
*/
unsigned char GetSegments(unsigned char number);

/*
    PutSegments:
        * Writes 'displays' to 7 Segment displays
*/
void PutSegments(struct Displays* displays);

/*
    ShiftSegments
        * Shifts each segment's value to the left by one
        * Unnecessary for lab7
*/

/*
void ShiftSegments(unsigned char number);
*/


#endif /* SEGMENT_DISPLAY_H_ */