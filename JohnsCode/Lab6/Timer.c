/***************************************************************************************************
Notes: 
***************************************************************************************************/

#include "Timer.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
unsigned char TIMER_FLAG = 0;

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
void TimerISR(void)
{
    TIMER_FLAG = 1;
}