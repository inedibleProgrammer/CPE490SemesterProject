/***************************************************************************************************
Notes:
    This file:
        * 1. defines exception vectors for the A9 processor
        * 2. provides code that sets the IRQ mode stack, and that dis/enables interrupts
        * 3. provides code that initializes the generic interrupt controller
***************************************************************************************************/

#include "Interrupts.h"
#include "Constants.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/

// Define the IRQ exception handler
void __attribute__ ((interrupt)) __cs3_isr_irq (void)
{
    // Read the ICCIAR from the CPU interface in the GIC
    int address;
    int interrupt_ID;
    
    address = MPCORE_GIC_CPUIF + ICCIAR;
    interrupt_ID = *(int *)address;
   
     if (interrupt_ID == KEYS_IRQ)       // check if interrupt is from the KEYs
         ButtonsISR ();
    // else if(interrupt_ID == MPCORE_PRIV_TIMER_IRQ)
        // TimerISR();
    // if(interrupt_ID == PS2_IRQ)
        // PS2ISR();
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
    config_interrupt (KEYS_IRQ, CPU0);  // configure the FPGA KEYs interrupt

    // Custom:
    // config_interrupt(MPCORE_PRIV_TIMER_IRQ, CPU0); // Hopefully, this configures the timer interrupts.
    // config_interrupt (PS2_IRQ, CPU0);               // PS2
    
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

void configINTs()
{
    volatile int * KEY_ptr = (int *) KEY_BASE;              // pushbutton KEY base address
    // volatile int* timerPtr = (int*) MPCORE_PRIV_TIMER;      // timer base address
    // volatile int * PS2_ptr = (int *) PS2_BASE;  // PS/2 port address

    // *(PS2_ptr) = 0xFF;              /* reset */
    // *(PS2_ptr + 1) = 0x1;           /* write to the PS/2 Control register to enable interrupts */

    *(KEY_ptr + 2) = 0x01;                                  // enable interrupts for KEY0

/*    *(timerPtr) = 2000;                                     // Interrupt every 0.001s
    *(timerPtr + 2) |= (100 << 8);                          // Prescale 100
    *(timerPtr + 2) |= 0x07;                                // Turn on I, A, and E*/
}







