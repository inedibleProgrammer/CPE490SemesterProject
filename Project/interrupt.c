/***********************************************************
    Project:    Semester Project
    Company:    CPE 490 Embedded Systems
    Author:     Andrew Davies & John Bugay
    File:       interrupt.c
    Purpose:
        defines exception vectors for the A9 processor
        provides code that sets the IRQ mode stack, and that dis/enables interrupts
        provides code that initializes the generic interrupt controller
***********************************************************/

//**Includes**//
#include "interrupt.h"
#include "isr.h"
#include "interrupt_id.h"
#include "address_map.h"

// Define the IRQ exception handler
void __attribute__ ((interrupt)) __cs3_isr_irq (void)
{
    // Read the ICCIAR from the CPU interface in the GIC
    int address;
    int interrupt_ID;
    
    address = MPCORE_GIC_CPUIF + ICCIAR;
    interrupt_ID = *(int *)address;
/*
    if (interrupt_ID == KEYS_IRQ)
        ButtonsISR ();
*/

    //if(interrupt_ID == MPCORE_PRIV_TIMER_IRQ)
       // TimerISR();

    if(interrupt_ID == HPS_TIMER0_IRQ)
        HPSTimer0ISR();  
    else if(interrupt_ID == HPS_TIMER1_IRQ)
        HPSTimer1ISR();
    else
        while (1);                          // if unexpected, then stay here

    // Write to the End of Interrupt Register (ICCEOIR)
    address = MPCORE_GIC_CPUIF + ICCEOIR;
    *(int *)address = interrupt_ID;

    return;
} 

// Define the remaining exception handlers
void __attribute__ ((interrupt)) __cs3_reset (void)
{
    while(1);
}

void __attribute__ ((interrupt)) __cs3_isr_undef (void)
{
    while(1);
}

void __attribute__ ((interrupt)) __cs3_isr_swi (void)
{
    while(1);
}

void __attribute__ ((interrupt)) __cs3_isr_pabort (void)
{
    while(1);
}

void __attribute__ ((interrupt)) __cs3_isr_dabort (void)
{
    while(1);
}

void __attribute__ ((interrupt)) __cs3_isr_fiq (void)
{
    while(1);
}

void disable_A9_interrupts(void)
{
    int status = 0b11010011;
    asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

void set_A9_IRQ_stack(void)
{
    int stack, mode;
    stack = A9_ONCHIP_END - 7;      // top of A9 onchip memory, aligned to 8 bytes
    /* change processor to IRQ mode with interrupts disabled */
    mode = INT_DISABLE | IRQ_MODE;
    asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
    /* set banked stack pointer */
    asm("mov sp, %[ps]" : : [ps] "r" (stack));

    /* go back to SVC mode before executing subroutine return! */
    mode = INT_DISABLE | SVC_MODE;
    asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
}

void enable_A9_interrupts(void)
{
    int status = SVC_MODE | INT_ENABLE;
    asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

void config_GIC(void) // STEP 3 IN SECTION 3.1 OF USING THE ARM GENERIC INTERRUPT CONTROLLER
{
    int address;
    // config_interrupt (KEYS_IRQ, CPU0);
    // config_interrupt(MPCORE_PRIV_TIMER_IRQ, CPU0);
    config_interrupt (PS2_IRQ, CPU0);
    config_interrupt (HPS_TIMER0_IRQ, CPU0);
    config_interrupt (HPS_TIMER1_IRQ, CPU0);
    
    // Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all priorities 
    address = MPCORE_GIC_CPUIF + ICCPMR;
    *(int *) address = 0xFFFF;       

    // Set CPU Interface Control Register (ICCICR). Enable signaling of interrupts
    address = MPCORE_GIC_CPUIF + ICCICR;
    *(int *) address = 1;       

    // Configure the Distributor Control Register (ICDDCR) to send pending interrupts to CPUs 
    address = MPCORE_GIC_DIST + ICDDCR;
    *(int *) address = 1;          
}

void config_interrupt (int N, int CPU_target)
{
    int reg_offset, index, value, address;
    
    /* Configure the Interrupt Set-Enable Registers (ICDISERn). 
     * reg_offset = (integer_div(N / 32) * 4
     * value = 1 << (N mod 32) */
    reg_offset = (N >> 3) & 0xFFFFFFFC; 
    index = N & 0x1F;
    value = 0x1 << index;
    address = MPCORE_GIC_DIST + ICDISER + reg_offset;
    /* Now that we know the register address and value, set the appropriate bit */
   *(int *)address |= value;

    /* Configure the Interrupt Processor Targets Register (ICDIPTRn)
     * reg_offset = integer_div(N / 4) * 4
     * index = N mod 4 */
    reg_offset = (N & 0xFFFFFFFC);
    index = N & 0x3;
    address = MPCORE_GIC_DIST + ICDIPTR + reg_offset + index;
    /* Now that we know the register address and value, write to (only) the appropriate byte */
    *(char *)address = (char) CPU_target;
}

void configInterupt()
{
    volatile int* timerPtr = (int*) MPCORE_PRIV_TIMER;      // timer base address

    volatile int* HPSTimer0Ptr = (int*) HPS_TIMER0_BASE;

    volatile int* HPSTimer1Ptr = (int*) HPS_TIMER1_BASE;

    // Private Timer
    *(timerPtr) = 2000;             // Interrupt every 0.001s
    *(timerPtr + 2) |= (100 << 8);  // Prescale 100
    *(timerPtr + 2) |= 0x07;        // Turn on I, A, and E

    // HPS0
    *(HPSTimer0Ptr + 2) &= ~(1 << 0);    // E = 0
    *(HPSTimer0Ptr) = 25000000;         // load value
    *(HPSTimer0Ptr + 2) |= (1 << 1);     // M = 1
    *(HPSTimer0Ptr + 2) |= (1 << 0);     // E = 1
    *(HPSTimer0Ptr + 2) &= ~(1 << 2);    // I = 0 Active low

    // HPS1
    *(HPSTimer1Ptr + 2) &= ~(1 << 0); // E = 0
    *(HPSTimer1Ptr) = 1000000; // load value
    *(HPSTimer1Ptr + 2) |= (1 << 1); // M = 1
    *(HPSTimer1Ptr + 2) |= (1 << 0); // E = 1
    *(HPSTimer1Ptr + 2) &= ~(1 << 3); // I = 0

//  *(KEY_ptr + 2) = 0x01;       // enable interrupts for KEY0
}
