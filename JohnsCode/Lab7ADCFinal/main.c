/***************************************************************************************************
Notes:
    Name:       John Bugay
    Date:       3/27/2018
    Project:    CPE 490 Lab7: Analog to Digital Converter
***************************************************************************************************/

/***************************************************************************************************
Includes:
***************************************************************************************************/
#include "Interrupts.h"
#include "Constants.h"
#include "Button.h"
#include "Timer.h"
#include "Numbers.h"
#include "JTAG_UART.h"
#include "SegmentDisplay.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
/*
    BUTTON_FLAG
        * Button.h
        * Set when KEY0 is pressed

    TIMER_FLAG
        * Timer.h
        * Set every millisecond when timer interrupt is signaled
*/

/***************************************************************************************************
Program Start:
***************************************************************************************************/
int main(void)
{
    /************************************************
    Interrupts:
    ************************************************/
    disable_A9_interrupts ();   // disable interrupts in the A9 processor
    set_A9_IRQ_stack ();            // initialize the stack pointer for IRQ mode
    config_GIC ();                  // configure the general interrupt controller
    ConfigINTs();             // configure pushbutton KEYs to generate interrupts
    enable_A9_interrupts ();    // enable interrupts in the A9 processor

    /************************************************
    Local Variables:
    ************************************************/
    volatile int* ADCptr = (int*)ADC_BASE;
    volatile int* channelTwo = (int*)0xFF204008; // ADC_BASE + 2

    struct Displays displays;
    displays.hex4 = GetSegments(255);
    displays.hex5 = GetSegments(255);

    struct Digits analogValueSeparated;

    int analogCounter = 0; 
    int analogValue   = 0;



    /************************************************
    Setup:
    ************************************************/
    *(ADCptr + 1) |= (1);    // Set ADC to auto mode

    while(1)
    {
        if(TIMER_FLAG)
        {
            analogCounter++;
            analogValue = analogValue + ( (*channelTwo) & 0xFFF);

            if(analogCounter >= 1000)
            {
                analogValue = analogValue / 1000;
                analogValueSeparated = DigitSeparator(analogValue);

                if(analogValueSeparated.hundreds == 0)
                {
                    displays.hex3 = GetSegments(255);
                    displays.hex2 = GetSegments(255);
                    displays.hex1 = GetSegments(analogValueSeparated.tens);
                    displays.hex0 = GetSegments(analogValueSeparated.ones);
                }
                else if(analogValueSeparated.thousands == 0)
                {
                    displays.hex3 = GetSegments(255);
                    displays.hex2 = GetSegments(analogValueSeparated.hundreds);
                    displays.hex1 = GetSegments(analogValueSeparated.tens);
                    displays.hex0 = GetSegments(analogValueSeparated.ones);
                }
                else
                {
                    displays.hex3 = GetSegments(analogValueSeparated.thousands);
                    displays.hex2 = GetSegments(analogValueSeparated.hundreds);
                    displays.hex1 = GetSegments(analogValueSeparated.tens);
                    displays.hex0 = GetSegments(analogValueSeparated.ones);
                }
                
                
                analogValue = 0;
                analogCounter = 0;
            }
            PutSegments(&displays);
            TIMER_FLAG = 0;
        }
        
        if(BUTTON_FLAG)
        {

            put_jtag(GetDigit(analogValueSeparated.thousands));
            put_jtag(GetDigit(analogValueSeparated.hundreds));
            put_jtag(GetDigit(analogValueSeparated.tens));
            put_jtag(GetDigit(analogValueSeparated.ones));
            put_jtag('\n');


            BUTTON_FLAG = 0;
        }
    }
}

/***************************************************************************************************
JUNK
{
    

}
ENDJUNK
***************************************************************************************************/
