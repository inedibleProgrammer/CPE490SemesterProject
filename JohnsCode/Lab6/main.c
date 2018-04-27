/***************************************************************************************************
Notes:
    Name:       John Bugay
    Date:       3/16/2018
    Project:    CPE 490 Lab6
***************************************************************************************************/

/***************************************************************************************************
Includes:
***************************************************************************************************/
#include "Interrupts.h"
#include "Constants.h"
#include "Monitor.h"
#include "Button.h"
#include "Timer.h"
#include "Numbers.h"
#include "JTAG_UART.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
// BUTTON_FLAG set when ButtonISR is called
// TIMER_FLAG set when TimerISR is called

/***************************************************************************************************
Program Start:
***************************************************************************************************/
int main(void)
{
    /************************************************
    * Interrupts:
    ************************************************/
    disable_A9_interrupts ();       // disable interrupts in the A9 processor
    set_A9_IRQ_stack ();            // initialize the stack pointer for IRQ mode
    config_GIC ();                  // configure the general interrupt controller
    ConfigINTs();                   // configure pushbutton KEYs to generate interrupts
    enable_A9_interrupts ();        // enable interrupts in the A9 processor

    /************************************************
    * Background:
    ************************************************/
    struct Coordinates background;
    background.x1 = 0;
    background.x2 = 319;
    background.y1 = 0;
    background.y2 = 239;
    background.color = 0b1111100000000000;     
                    // 11111 000000 00000 Red
    VGA_box(&background);  // fill the screen with red

    /************************************************
    * White edge
    ************************************************/
    struct Coordinates whiteEdge;
    whiteEdge.x1 = 59;
    whiteEdge.x2 = 261;
    whiteEdge.y1 = 111;
    whiteEdge.y2 = 128;
    whiteEdge.color = 0b1111111111111111;     
                    // 11111 000000 00000 Red
    VGA_box(&whiteEdge);  // white border

    /************************************************
    * Blue Bar:
    ************************************************/
    struct Coordinates loadBar;
    loadBar.x1 = 60;
    loadBar.x2 = 260;
    loadBar.y1 = 112;
    loadBar.y2 = 127;
    loadBar.color = 0x187F; // Blue

    VGA_box(&loadBar);

    /************************************************
    * Characters:
    ************************************************/
    struct CoordinatesChar percentString;
    percentString.x = 35;
    percentString.y = 25;

    percentString.string[0] = 'X';
    percentString.string[1] = 'X';
    percentString.string[2] = 'X';
    percentString.string[3] = '.';
    percentString.string[4] = 'X';
    percentString.string[5] = '%';
    percentString.string[6] = '\0';

    VGA_text(&percentString);

    /************************************************
    * Local Variables:
    ************************************************/
    double percentFraction = 0.0;
    int percentInt = 0;

    volatile int* switchPtr = (int*)(SW_BASE);
    int currentSwitch = (*switchPtr) & 0x3FF;
    
    struct Digits percentSeparated;

    // These variables are only used for debugging
    struct Digits switchValue;
    struct Digits loadBarSeparated;

    while(1)
    {
        if(TIMER_FLAG)
        {
            /************************************************
            * White Background
            ************************************************/
            VGA_box(&whiteEdge);

            /************************************************
            Percent Calculations
            ************************************************/
            percentFraction = ( (*switchPtr & 0x03FF) / (float)(1023) ) * 100 + 0.05;
            percentInt = percentFraction; // cast to int

            /************************************************
            * Find loadBar.x2
            * Print the new loadBar box
            ************************************************/
            loadBar.x2 = (percentFraction * 2) + 60; //260 represents a full bar
            VGA_box(&loadBar);

            /************************************************
            * Remove integer part from the fraction
            ************************************************/
            percentFraction = percentFraction - percentInt;

            /************************************************
            * Text management
            ************************************************/
            percentSeparated = DigitSeparator(percentInt);

            if(percentSeparated.hundreds == 1)
            {
                percentString.string[0] = GetDigit(percentSeparated.hundreds);
                percentString.string[1] = GetDigit(percentSeparated.tens);
                percentString.string[2] = GetDigit(percentSeparated.ones);
                percentString.string[4] = GetDigit( (int)(percentFraction * 10) );
            }
            else
            {
                percentString.string[0] = ' ';
                percentString.string[1] = GetDigit(percentSeparated.tens);
                percentString.string[2] = GetDigit(percentSeparated.ones);
                percentString.string[4] = GetDigit( (int)(percentFraction * 10) );
            }

            VGA_text(&percentString);

            /************************************************
            * Reset global Timer flag
            ************************************************/
            TIMER_FLAG = 0;
        }
        
        if(BUTTON_FLAG)
        {
            
            // Test Switch values
            switchValue = DigitSeparator( (*switchPtr) & 0x03FF );
            put_jtag(GetDigit(switchValue.thousands));
            put_jtag(GetDigit(switchValue.hundreds));
            put_jtag(GetDigit(switchValue.tens));
            put_jtag(GetDigit(switchValue.ones));
            put_jtag('\n');

            // Percent values
            percentSeparated = DigitSeparator(percentInt);
            put_jtag(GetDigit(percentSeparated.thousands));
            put_jtag(GetDigit(percentSeparated.hundreds));
            put_jtag(GetDigit(percentSeparated.tens));
            put_jtag(GetDigit(percentSeparated.ones));
            put_jtag('\n');

            // Loadbar values
            loadBarSeparated = DigitSeparator(loadBar.x2);
            put_jtag(GetDigit(loadBarSeparated.thousands));
            put_jtag(GetDigit(loadBarSeparated.hundreds));
            put_jtag(GetDigit(loadBarSeparated.tens));
            put_jtag(GetDigit(loadBarSeparated.ones));
            put_jtag('\n');
            

            BUTTON_FLAG = 0;
        }
    }
}

/***************************************************************************************************
JUNK
{
    

The specifications for this lab included creating a bar graph on a monitor that responds to the input of the 10 - slider switch. 
When every switch is high, the bar is 200 pixels in length and 15 pixels in width; otherwise, the bar’s length is equal to the percent of the high 
switch values to the total 10-bit value of the switch. This percentage must be numerically displayed and accurate to + or - 0.05%. 

}
ENDJUNK
***************************************************************************************************/
