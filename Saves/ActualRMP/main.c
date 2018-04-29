/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies & John Bugay
	File:		main.c
	Purpose:	main program code
***********************************************************/

//**Inlcudes**//
#include "gui.h"
#include "keypad.h"
#include "interrupt.h"
#include "JTAG_UART.h"
#include "ps2.h"
#include "isr.h"
#include "pwm.h"
#include "adc.h"
#include "encoder.h"
#include "struct.h"

//**Prototype**//

//**Global Variables**//
int ps2Interrupt;		//used in isr.c
int encoderInterrupt;	//used in isr.c
int monitorInterrupt;	//used in isr.c
int adcInterrupt;       //used in isr.c

int goodKey;			//used in ps2.c
char enterPress;		//used in keypad.c

//**Program Code**//

int main(void)
{
	//**Initialize Interrupts**//
	disable_A9_interrupts();
	set_A9_IRQ_stack();
	config_GIC();
	configInterupt();
	enable_A9_interrupts();

	//**Initialize GUI**//
	GUI_Setup();

    //GPIO
    volatile int* GPIOPtr = (int*)0xFF200060;
    *(GPIOPtr + 1) |= (1 << 0); // Set D0 as output


	
	while(1)
	{
        /*******************************************************************************************
        KEYBOARD:
        *******************************************************************************************/
		if(ps2Interrupt == 1)
		{
			ps2Interrupt = 0;
          	PS2_Read();

          	if(goodKey == 1)
            {
              	Key();
                goodKey = 0;
            }
		}

        /*******************************************************************************************
        MONITOR:
        *******************************************************************************************/
		if(monitorInterrupt == 1)
		{
			monitorInterrupt = 0;
			//Print_Bars(actrpm.iTotal);
		}

        /*******************************************************************************************
        ENCODER:
        *******************************************************************************************/
		if(encoderInterrupt == 1)
		{
			encoderInterrupt = 0;
			GetActualRpm();
			PrintActualRpm();
		}

        /*******************************************************************************************
        ADC:
        *******************************************************************************************/
        if(adcInterrupt == 1)
        {
            adcInterrupt = 0; // disable flag
            ADC_Get();
        }
	}

	int _end_ = 0;
  	return _end_;
}

//**End of File**//