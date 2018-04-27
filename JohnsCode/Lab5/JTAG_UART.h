/***************************************************************************************************
Notes: 
    Interface to JTAG_UART.c
***************************************************************************************************/
#ifndef JTAG_UART_H_
#define JTAG_UART_H_

/*
    print_jtag:
        Undefined use
*/
void print_jtag(const char * str);

/*
    put_jtag:
        prints a character to the screen.
*/
void put_jtag(char);

/*
    get_jtag:
        Subroutine to read a character from the JTAG UART
        Returns \0 if no character, otherwise returns the character
*/
char get_jtag(void);

/*
    GetDigit:
        * Converts a decimal number into an ascii character
*/
char GetDigit(unsigned char value);

#endif /* JTAG_UART_H_ */