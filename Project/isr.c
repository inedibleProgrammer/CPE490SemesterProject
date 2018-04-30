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
extern int adcInterrupt;      //declared in main.c
extern int encoderValue;      //declared in main.c

extern float percent;         //delcared in keypad.c

static unsigned char END = 0; // Used to read the End-Of-Interrupt register to reset timer values

//**Interrupt Service Routines**//
void HPSTimer0ISR()   //half second period
{
    volatile int* HPSTimer0Ptr = (int*) HPS_TIMER0_BASE;
    static char flag; //toggle flag
  
    ps2Interrupt = 1;
    flag ++;
    if(flag == 2)
    {
        monitorInterrupt = 1;
    }
    if(flag == 4)
    {
        encoderInterrupt = 1;
        flag = 0;
    }
  
    END = *(HPSTimer0Ptr + 3);  //resets HPSTimer0
}

void HPSTimer1ISR()
{
    volatile int* HPSTimer1Ptr = (int*) HPS_TIMER1_BASE;
    volatile int* GPIOPtr = (int*)JP1_BASE;

    static int pwmToggle = 0;

    if(percent == 0)
    {
        *(GPIOPtr) &= ~(1 << 0);
        // *(GPIOPtr) &= 0xFFFFFFFD; // 1101
    }
    else if(percent == 1.0)
    {
        *(GPIOPtr) |= (1 << 0);
        // *(GPIOPtr) |= 0x2; // 0010
    }
    else
    {
        if(pwmToggle == 1)
        {
            *(GPIOPtr) |= (1 << 0); // D0 = low
            // *(GPIOPtr) |= 0x2;
            SetPWM(1000, percent);

            pwmToggle = 0;
        }
        else // pwmToggle == 0
        {
            *(GPIOPtr) &= ~(1 << 0); // D0 = high
            // *(GPIOPtr) &= 0xFFFFFFFD;
            SetPWM( 1000, (1.0 - percent) );

            pwmToggle = 1;
        }
    }

    END = *(HPSTimer1Ptr + 3);
}

void HPSTimer2ISR()
{
    volatile int* HPSTimer2Ptr = (int*) HPS_TIMER2_BASE;
    
    adcInterrupt = 1;

    END = *(HPSTimer2Ptr + 3);
}

void JP1ISR()
{
    volatile int* GPIOPtr = (int*)JP1_BASE;
    encoderValue++;

    *(GPIOPtr + 3) |= (1 << 3);
}

//**End of File**//
