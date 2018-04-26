/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		main.c
	Purpose:	main program code
***********************************************************/

//**Inlcudes**//
#include "gui.h"
#include "keypad.h"
#include "interrupt.h"

//**Prototype**//
void main(void);

//**Global Variables**//
char ps2interrupt;	//used in isr.c
char enterpress;	//used in keypad.c

//**Program Code**//

void main(void)
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
		if(ps2interrupt == 1)
		{
			ps2interrupt = 0;
			Key();
		}
		if(enterpress == 1)
		{
			enterpress = 0;

		}
	}
}