/***************************************************************************************************
Notes:
    Name:       John Bugay
    Date:       4/13/2018
    Project:    CPE 490 Lab8: PWM
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
#include "PWM.h"
#include "GPIO.h"
#include "Switches.h"

/***************************************************************************************************
Program Start:
***************************************************************************************************/
int main(void)
{
    /************************************************
    Interrupts:
    ************************************************/
    disable_A9_interrupts ();       // disable interrupts in the A9 processor
    set_A9_IRQ_stack ();            // initialize the stack pointer for IRQ mode
    config_GIC ();                  // configure the general interrupt controller
    ConfigINTs();                   // configure pushbutton KEYs to generate interrupts
    enable_A9_interrupts ();        // enable interrupts in the A9 processor



    /************************************************
    Local Variables:
    ************************************************/
    unsigned char direction = 0;
    int period = 1000; // 1000 us
    double switches = 0.0;


    /************************************************
    Setup:
    ************************************************/
    *(GPIOPtr + 1) |= (1 << 0); // Set D0 as output

    while(1)
    {

    }
}

/***************************************************************************************************
JUNK
{
    

}
ENDJUNK
***************************************************************************************************/
