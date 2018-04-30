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

    if(analogCounter == 200)
    {
        analogValue = analogValue / 200; // average it
        analogValue = analogValue - 90;  // error correction

        currentValue = ( (analogValue)  / 7.3 );
        PrintADC(currentValue);

        analogValue = 0;
        analogCounter = 0;
    }
}

void PrintADC(long value)
{
	current = RPM_Splitter(value);
	current = RPM_Characters(current);
	if(current.cTotal[0] == '0')
		current.cTotal[0] = ' ';
	Current_Write(current.cTotal);
}