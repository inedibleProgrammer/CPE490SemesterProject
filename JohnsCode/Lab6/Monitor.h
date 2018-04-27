/***************************************************************************************************
Notes: Used for graphics with the monitor through VGA
***************************************************************************************************/
#ifndef MONITOR_H_
#define MONITOR_H_

/***************************************************************************************************
Structures:
***************************************************************************************************/
struct Coordinates
{
    int x1;
    int x2;
    int y1;
    int y2;
    short color;
};

struct CoordinatesChar
{
    int x;
    int y;
    char string[20];
};

/***************************************************************************************************
Global Variables:
***************************************************************************************************/


/***************************************************************************************************
Function Prototypes:
***************************************************************************************************/

/*
    VGA_text:
        Writes text to the monitor
*/
void VGA_text (struct CoordinatesChar* coordinatesChar);

/*
    VGA_box:
        Draws a box on the monitor
*/
void VGA_box (struct Coordinates* coordinates);

#endif /* MONITOR_H_ */
