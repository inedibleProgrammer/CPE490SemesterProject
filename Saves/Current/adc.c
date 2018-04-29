/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		John Bugay
	File:		adc.c
	Purpose:	controls the ADC
***********************************************************/    

//**Includes**//
#include "adc.h"
#include "gui.h"
#include "struct.h"
#include "address_map.h"
#include "Numbers.h"
#include "JTAG_UART.h"

//**Funtion Code**//
void ADC_Get(void)
{
	volatile int* ADCptr = (int*)ADC_BASE;
    volatile int* channelTwo = (int*)0xFF204008; // ADC_BASE + 2
    *(ADCptr + 1) |= (1);                        // Set ADC to auto mode

    static int analogCounter;
    static unsigned long analogValue;
    static double currentValue;

	analogCounter++;
    analogValue = analogValue + ( (*channelTwo) & 0xFFF); // sample the adc

    if(analogCounter == 1000)
    {
        analogValue = analogValue / 1000; // average it
        currentValue = ( (analogValue)  / 7.3 );
        PrintADC(currentValue);
		analogValue = 0;
        analogCounter = 0;

//**Debug**//
        struct Digits analogValueSeparated;
    	struct Digits currentValueSeparated;

        currentValueSeparated = DigitSeparator(currentValue);
        analogValueSeparated  = DigitSeparator(analogValue);

        //ADC:
        put_jtag('A');
        put_jtag('D');
        put_jtag('C');
        put_jtag(':');
        put_jtag(' ');

        put_jtag(GetDigit(analogValueSeparated.thousands));
        put_jtag(GetDigit(analogValueSeparated.hundreds));
        put_jtag(GetDigit(analogValueSeparated.tens));
        put_jtag(GetDigit(analogValueSeparated.ones));
        put_jtag('\n');

		//Current:
        put_jtag('I');
        put_jtag(':');
        put_jtag(' ');

        put_jtag(GetDigit(currentValueSeparated.thousands));
        put_jtag(GetDigit(currentValueSeparated.hundreds));
        put_jtag(GetDigit(currentValueSeparated.tens));
        put_jtag(GetDigit(currentValueSeparated.ones));
        put_jtag('\n');

        put_jtag('\n');
    }
}

void PrintADC(long value)
{
	current = ADC_Splitter(value);
	current = ADCCharacters(current);
	if(current.cTotal[0] == '0')
		current.cTotal[0] = ' ';
	Current_Write(current.cTotal);
}

struct Monitor ADC_Splitter(long value)
{
    struct Monitor current;

    current.iHundred  = (value / 100);
    current.iTen      = ((value % 100) / 10);
    current.iOne      = ((value % 100)% 10);

    return current;
}

struct Monitor ADCCharacters (struct Monitor current)
{
	current.cTotal[0] = GetCharacter(current.iHundred);
	current.cTotal[1] = GetCharacter(current.iTen);
	current.cTotal[2] = GetCharacter(current.iOne);
	return current;
}