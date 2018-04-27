/***********************************************************
    Project:    Semester Project
    Company:    CPE 490 Embedded Systems
    Author:     Andrew Davies & John Bugay
    File:       isr.c
    Purpose:    holds interrupt service routines
***********************************************************/
//**Includes**//
#include "isr.h"
#include "address_map.h"
#include "pwm.h"

//**Global Valiables**//
extern int ps2Interrupt;      //declared in main.c
extern int encoderInterrupt;  //declared in main.c
extern int monitorInterrupt;  //declared in main.c

static unsigned char END = 0; // Used to read the End-Of-Interrupt register to reset timer values

//**Interrupt Service Routines**//
void HPSTimer0ISR()   //half second period
{
    volatile int* HPSTimer0Ptr = (int*) HPS_TIMER0_BASE;
  static char flag; //toggle flag
  
    ps2Interrupt = 1;
    flag ++;
    if(flag == 1)
    {
        encoderInterrupt = 1;
    }
    if(flag == 2)
    {
        monitorInterrupt = 1;
        flag = 0;
    }
  
    END = *(HPSTimer0Ptr + 3);  //resets HPSTimer0
}

void HPSTimer1ISR()
{
    volatile int* HPSTimer1Ptr = (int*) HPS_TIMER1_BASE;
    volatile int* SwitchesPtr = (int*) SW_BASE;


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

    END = *(HPSTimer1Ptr + 3);
}

//**End of File**//