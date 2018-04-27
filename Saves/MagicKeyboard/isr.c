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

//**End of File**//