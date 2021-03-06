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

//**Prototype**//

//**Global Variables**//
int ps2Interrupt;		//used in isr.c
int encoderInterrupt;	//used in isr.c
int monitorInterrupt;	//used in isr.c
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
	//**Initialize Structs**//
	InitializeStructs();
	while(1)
	{
		if(ps2Interrupt == 1)
		{
			ps2Interrupt = 0;
          	PS2_Read();
          	put_jtag('A');
			Key();
		}
		if(monitorInterrupt == 1)
		{
			put_jtag('B');
			monitorInterrupt = 0;
		}
		if(encoderInterrupt == 1)
		{
			put_jtag('C');
			encoderInterrupt = 0;
		}
		if(enterPress == 1)
		{
			enterPress = 0;

		}
	}
  int _end_ = 0;
  return _end_;
}
