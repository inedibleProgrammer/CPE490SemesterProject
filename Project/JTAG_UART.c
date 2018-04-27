/***************************************************************************************************
Notes:
***************************************************************************************************/

#include "JTAG_UART.h"
#include "address_map.h"


void put_jtag( char c )
{
    volatile int * JTAG_UART_ptr    = (int *) JTAG_UART_BASE;   // JTAG UART address

    int control;
    control = *(JTAG_UART_ptr + 1);     // read the JTAG_UART control register
    if (control & 0xFFFF0000)               // if space, echo character, else ignore 
        *(JTAG_UART_ptr) = c;
}

char get_jtag( void )
{
    volatile int * JTAG_UART_ptr    = (int *) JTAG_UART_BASE;   // JTAG UART address

    int data;
    data = *(JTAG_UART_ptr);                // read the JTAG_UART data register
    if (data & 0x00008000)                  // check RVALID to see if there is new data
        return ((char) data & 0xFF);
    else
        return ('\0');
}

char GetDigit(unsigned char value)
{
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    return digits[value];
}
