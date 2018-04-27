/***************************************************************************************************
Notes: 
    Interrupts
***************************************************************************************************/
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/***************************************************************************************************
Function Prototypes: "interrupt_example.c" and "exceptions.c"
***************************************************************************************************/

/* 
    disable_A9_interrupts:
        * Turn off interrupts in the ARM processor
*/
void disable_A9_interrupts (void);

/* 
    set_A9_IRQ_stack:
        * Initialize the banked stack pointer register for IRQ mode
        * Given
*/
void set_A9_IRQ_stack (void);
/*
    config_GIC:
        * Configure the Generic Interrupt Controller (GIC)
        * Given
*/
void config_GIC (void);

/* 
    enable_A9_interrupts:
        * Turn on interrupts in the ARM processor
        * Given
*/
void enable_A9_interrupts (void);

/*
    config_interrupt:
        * Configure registers in the GIC for an individual interrupt ID
        * We configure only the Interrupt Set Enable Registers (ICDISERn) and Interrupt 
        * Processor Target Registers (ICDIPTRn). The default (reset) values are used for 
        * other registers in the GIC
        * Given
*/
void config_interrupt (int, int);

/*
    ConfigINTs:
        * Configure pushbutton keys to generate interrupts
        * Configure timer interrupt
        * Configure PS/2 interrupt
*/
void ConfigINTs (void);

#endif /* INTERRUPTS_H_ */