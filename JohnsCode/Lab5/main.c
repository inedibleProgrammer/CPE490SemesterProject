/***************************************************************************************************
Notes:
    Name:       John Bugay
    Date:       3/2/2018
    Project:    CPE 490 Lab5
***************************************************************************************************/
#include "JTAG_UART.h"
#include "Interrupts.h"
#include "Keyboard.h"
#include "SegmentDisplay.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/


/***************************************************************************************************
Program Start:
***************************************************************************************************/
int main(void)
{
    disable_A9_interrupts ();       // disable interrupts in the A9 processor
    set_A9_IRQ_stack ();            // initialize the stack pointer for IRQ mode
    config_GIC ();                  // configure the general interrupt controller
    configINTs();                   // configure interrupts
    enable_A9_interrupts ();        // enable interrupts in the A9 processor

    unsigned char codeIndex = 100;
    unsigned char enter = 0;

    InitSegments();
    PutSegments();
    while(1)
    {
        codeIndex = CodeLookup();
        if( codeIndex == 100 )      // If CodeLookup returns 100, then no match was found
        {
            // Do nothing
        }
        else
        {
            put_jtag( GetDigit(codeIndex) );
            put_jtag('\n');
            if(enter)
            {
                InitSegments();
                enter = 0;
            }
            switch(codeIndex)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    ShiftSegments(GetSegments(codeIndex));
                    PutSegments();
                    break;
                case 10:
                case 11:
                    enter = 1;
            }
        }
    }
}

/***************************************************************************************************
JUNK
{
    

}
ENDJUNK
***************************************************************************************************/