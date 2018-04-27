/***************************************************************************************************
Notes: 
***************************************************************************************************/

#include "Timer.h"
#include "GPIO.h"
#include "Switches.h"

/***************************************************************************************************
Peripherals:
***************************************************************************************************/
volatile int* HPSTimerPtr = (int*)0xFFC08000; // HPS_TIMER0_BASE

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
unsigned char TIMER_FLAG = 0;
unsigned char HPS_TIMER_FLAG = 0;
static unsigned char END = 0; // Used to read the End-Of-Interrupt register to reset timer values

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
void PrivTimerISR(void)
{

}

void HPSTimerISR(void)
{
    double switches = ( ( *(SwitchesPtr) & 0x3FF) / 1023.0 );
    static direction = 0;

    if(switches == 0)
    {
        // *(GPIOPtr) &= ~(1 << 0);
        *(GPIOPtr) = 0;
    }
    else if(switches == 1.0)
    {
        // *(GPIOPtr) |= (1 << 0);
        *(GPIOPtr) = 1;
    }
    else
    {
        if(direction == 1)
        {
            // *(GPIOPtr) &= ~(1 << 0); // D0 = low
            *(GPIOPtr) = 1;
            SetPWM(1000, switches);

            direction = 0;
        }
        else // direction == 0
        {
            // *(GPIOPtr) |= (1 << 0); // D0 = high
            *(GPIOPtr) = 0;
            SetPWM( 1000, (1.0 - switches) );

            direction = 1;
        }
    }

    END = *(HPSTimerPtr + 3);
}
