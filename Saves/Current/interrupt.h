/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		struct.h
	Purpose:	prototypes for interrupt.c
***********************************************************/

void disable_A9_interrupts (void);  //Turn off interrupts in the ARM processor
void set_A9_IRQ_stack (void);       //Initialize the banked stack pointer register for IRQ mode
void config_GIC (void);             //Configure the Generic Interrupt Controller (GIC)
void enable_A9_interrupts (void);   //Turn on interrupts in the ARM processor
void config_interrupt (int, int);/*
        * Configure registers in the GIC for an individual interrupt ID
        * We configure only the Interrupt Set Enable Registers (ICDISERn) and Interrupt 
        * Processor Target Registers (ICDIPTRn). The default (reset) values are used for 
        * other registers in the GIC*/
void configInterupt(void);/*
        * Configure pushbutton keys to generate interrupts
        * Added functionality for timer overflow interrupt
        * (Example - Given)*/

//**End of File**//