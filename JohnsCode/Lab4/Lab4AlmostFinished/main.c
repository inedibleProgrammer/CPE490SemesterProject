/***************************************************************************************************
Notes:
    Name:       John Bugay
    Date:       2/16/2018
    Project:    CPE 490 Lab4
***************************************************************************************************/
#include "Interrupts.h"
#include "RTClock.h"

/***************************************************************************************************
Program Start:
***************************************************************************************************/
int main(void)
{
    disable_A9_interrupts ();   // disable interrupts in the A9 processor
    set_A9_IRQ_stack ();            // initialize the stack pointer for IRQ mode
    config_GIC ();                  // configure the general interrupt controller
    config_KEYs ();             // configure pushbutton KEYs to generate interrupts
    enable_A9_interrupts ();    // enable interrupts in the A9 processor

    ClockInit();
    while(1)
    {
        /* 
            Idle Loop:
                * Nothing to do here. TimerISR is called every millisecond.
        */
    }
}

/***************************************************************************************************
JUNK
{

    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    void pushbutton_ISR( void )
    {
        volatile int * KEY_ptr = (int *) KEY_BASE;
        volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE;
        int press, HEX_bits;

        press = *(KEY_ptr + 3);                 // read the pushbutton interrupt register
        *(KEY_ptr + 3) = press;                 // Clear the interrupt

        put_jtag('A');

        if (press & 0x1)                            // KEY0
            HEX_bits = 0b00111111;
        else if (press & 0x2)                   // KEY1
            HEX_bits = 0b00000110;
        else if (press & 0x4)                   // KEY2
            HEX_bits = 0b01011011;
        else                                            // press & 0x8, which is KEY3
            HEX_bits = 0b01001111;

        *HEX3_HEX0_ptr = HEX_bits;
    }

    ***************************************************************************************************
    Global Variables:
    ***************************************************************************************************
    unsigned char buttonPressed;
    Time clock;

    The clock started at 1:08 P.M. 2/17, matching the actual time of day.
    On 2/19/2018 @ 8:19 A.M., the clock read 19:52. In 12-hour time, it is 7:52. 
    

} ENDJUNK
***************************************************************************************************/